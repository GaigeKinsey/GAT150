#pragma once
#include "object.h"
#include "..\\math\transform.h"

class Scene;
class Component;

class Entity : public Object
{
public:
	Entity(const Name& name, Scene* scene) : Object(name), m_scene(scene) {}

	bool Create() override;
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;

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

protected:
	Name m_tag;
	transform m_transform;
	Scene* m_scene;

	std::vector<Component*> m_components;
};
