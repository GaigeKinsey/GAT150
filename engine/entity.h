#pragma once
#include "object.h"
#include "..\\math\transform.h"

class Scene;
class Component;

class Entity : public Object
{
public:
	Entity() : m_scene(nullptr), m_spawner(false) {}
	Entity(Scene* owner) : m_scene(owner), m_spawner(false) {}
	Entity(const Entity& entity);

	bool Create(const Name& name, Scene* scene);
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Entity* Clone() override { return new Entity(*this); }

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

	void SetTag(const Name& tag) { m_tag = tag; }
	const Name& GetTag() const { return m_tag; }

	transform& GetTransform() { return m_transform; }

	Scene* GetScene() { return m_scene; }
	void SetScene(Scene* scene) { m_scene = scene; }

	bool IsSpawner() { return m_spawner; }

protected:
	bool LoadComponents(const rapidjson::Value& value);

public:
	transform m_transform;

protected:
	Name m_tag;
	Scene* m_scene;
	bool m_spawner;

	std::vector<Component*> m_components;
};
