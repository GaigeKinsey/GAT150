#include "scene.h"
#include "entity.h"

#include "sprite_component.h"
#include "sprite_animation_component.h"
#include "controller_component.h"
#include "physics_component.h"
#include "asteroid_component.h"
#include "weapon_component.h"
#include "player_component.h"
#include "circle_collision_component.h"
#include "text_component.h"
#include "emitter_component.h"
#include "..\\renderer\text.h"

void Scene::Initialize()
{
}

bool Scene::Create(const Name& name, Engine* engine)
{
	m_name = name;
	m_engine = engine;

	m_object_factory = new ObjectFactory;
	m_object_factory->Register("sprite_component", new Creator<SpriteComponent, Object>());
	m_object_factory->Register("sprite_animation_component", new Creator<SpriteAnimationComponent, Object>());
	m_object_factory->Register("controller_component", new Creator<ControllerComponent, Object>());
	m_object_factory->Register("physics_component", new Creator<PhysicsComponent, Object>());
	m_object_factory->Register("asteroid_component", new Creator<AsteroidComponent, Object>());
	m_object_factory->Register("weapon_component", new Creator<WeaponComponent, Object>());
	m_object_factory->Register("player_component", new Creator<PlayerComponent, Object>());
	m_object_factory->Register("circle_collision_component", new Creator<CircleCollisionComponent, Object>());
	m_object_factory->Register("text_component", new Creator<TextComponent, Object>());
	m_object_factory->Register("emitter_component", new Creator<EmitterComponent, Object>());
	m_object_factory->Register("entity", new Creator<Entity, Object>());

	return true;
}

void Scene::Destroy()
{
	for (Entity* entity : m_entities) {
		entity->Destroy();
		delete entity;
	}

	m_entities.clear();

	delete m_object_factory;
}

bool Scene::Load(const rapidjson::Value& value)
{
	const rapidjson::Value& entities_value = value["entities"];
	if (entities_value.IsArray()) {
		LoadEntities(entities_value);
	}

	return true;
}

void Scene::Update()
{
	for (Entity* entity : m_entities) {
		if (entity->m_state.test(Entity::eState::ACTIVE)) {
			entity->Update();
		}

		if (entity->m_transform.translation.x < 0.0f) entity->m_transform.translation.x = 800.0f;
		if (entity->m_transform.translation.x > 800.0f) entity->m_transform.translation.x = 0.0f;
		if (entity->m_transform.translation.y > 600.0f) entity->m_transform.translation.y = 0.0f;
		if (entity->m_transform.translation.y < 0.0f) entity->m_transform.translation.y = 600.0f;
	}

	auto iter = m_entities.begin();
	while (iter != m_entities.end()) {
		if ((*iter)->m_state.test(Entity::eState::DESTROY)) {
			(*iter)->Destroy();
			delete* iter;
			iter = m_entities.erase(iter);
		}
		else {
			iter++;
		}
	}

	std::vector<CollisionComponent*> collision_components;
	for (Entity* entity : m_entities)
	{
		CollisionComponent* component = entity->GetComponent<CollisionComponent>();
		if (component)
		{
			collision_components.push_back(component);
		}
	}

	for (size_t i = 0; i < collision_components.size(); i++)
	{
		for (size_t j = i + 1; j < collision_components.size(); j++)
		{
			if (collision_components[i]->GetOwner()->m_state.test(Entity::eState::DESTROY) ||
				collision_components[j]->GetOwner()->m_state.test(Entity::eState::DESTROY))
			{
				continue;
			}

			if (collision_components[i]->Intersects(collision_components[j])) {
				Event<Entity> event;
				event.name = "collision";
				event.sender = collision_components[i]->GetOwner();
				event.receiver = collision_components[j]->GetOwner();

				m_engine->GetSystem<EntityEventDispatcher>()->Notify(event);
			}
		}
	}
}

void Scene::Draw()
{
	std::vector<RenderComponent*> render_components;

	for (Entity* entity : m_entities) {
		if (entity->m_state.test(Entity::eState::VISIBLE)) {
			RenderComponent* render_component = entity->GetComponent<RenderComponent>();
			if (render_component) {
				render_components.push_back(render_component);
			}
		}
	}

	std::sort(render_components.begin(), render_components.end(), RenderComponent::SortZ);
	for (RenderComponent* render_component : render_components) {
		render_component->Draw();
	}

}

void Scene::Add(Entity* entity)
{
	ASSERT(entity);
	ASSERT(std::find(m_entities.begin(), m_entities.end(), entity) == m_entities.end());

	entity->Initialize();
	m_entities.push_back(entity);
}

std::list<Entity*>::iterator Scene::Remove(Entity* entity, bool destroy)
{
	ASSERT(entity);

	auto next_iter = m_entities.end();

	auto iter = std::find(m_entities.begin(), m_entities.end(), entity);
	if (iter != m_entities.end()) {
		if (destroy) {
			(*iter)->Destroy();
			delete* iter;
			next_iter = m_entities.erase(iter);
		}
	}

	return next_iter;
}

Entity* Scene::GetEntityWithName(const Name& name)
{
	Entity* entity = nullptr;

	for (Entity* _entity : m_entities) {
		if (_entity->GetName() == name) {
			entity = _entity;
			break;
		}
	}

	return entity;
}

std::vector<Entity*> Scene::GetEntitiesWithTag(const Name& tag)
{
	std::vector<Entity*> entities;
	for (Entity* entity : m_entities) {
		if (entity->GetTag() == tag) {
			entities.push_back(entity);
		}
	}

	return entities;
}

bool Scene::LoadEntities(const rapidjson::Value& value)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& entity_value = value[i];
		if (entity_value.IsObject()) {
			Entity* entity = m_object_factory->Create<Entity>("entity");
			entity->SetScene(this);
			if (entity->Load(entity_value)) {
				if (entity->IsSpawner()) {
					m_object_factory->Register(entity->GetName(), new Spawner<Object>(entity));
				}
				else {
					Add(entity);
				}
			}
			else {
				delete entity;
				return false;
			}
		}
	}

	return true;
}
