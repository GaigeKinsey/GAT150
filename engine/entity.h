#pragma once
#include "object.h"
#include "..\\math\transform.h"
#include "..\\core\core.h"

class Scene;
class Component;

class Entity : public Object
{
public:
	enum eState : u8 {
		ACTIVE,
		VISIBLE,
		DESTROY,
		TRANSIENT
	};

public:
	Entity() : m_scene(nullptr), m_spawner(false) {}
	Entity(Scene* owner) : m_scene(owner), m_spawner(false) {}
	Entity(const Entity& entity);

	bool Create(const Name& name, Scene* scene);
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Entity* Clone() override { return new Entity(*this); }

	void Initialize() override;

	void Update();
	void Draw();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	template <typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* _component : m_components)
		{
			component = dynamic_cast<T*>(_component);
			if (component != nullptr) break;
		}

		return component;
	}

	void SetTag(Name& tag) { m_tag = tag; }
	const Name& GetTag() { return m_tag; }

	transform& GetTransform() { return m_transform; }

	Scene* GetScene() { return m_scene; }
	void SetScene(Scene* scene) { m_scene = scene; }

	bool IsSpawner() { return m_spawner; }

protected:
	bool LoadComponents(const rapidjson::Value& value);

public:
	transform m_transform;
	std::bitset<8> m_state = BIT(ACTIVE) | BIT(VISIBLE);

protected:
	Name m_tag;
	Scene* m_scene;
	bool m_spawner;
	float m_lifetime;

	std::vector<Component*> m_components;
};
