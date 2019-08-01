#pragma once

#include "..\\framework\manager.h"

template <typename T, size_t N = 65536>
class ResourceManager : public Manager<T, N>
{
public:
	ResourceManager(Renderer* renderer) : m_renderer(renderer) {}
	~ResourceManager();

	T* Get(const Name& name) override;
	void Remove(const Name& name) override;
	void RemoveAll() override;

private:
	Renderer* m_renderer;
};

template<typename T, size_t N>
inline ResourceManager<T, N>::~ResourceManager()
{
	RemoveAll();
}

template<typename T, size_t N>
T* ResourceManager<T, N>::Get(const Name& name)
{
	u32 index = name.GetID() % N;
	T* element = Manager<T, N>::m_elements[index];

	if (element == nullptr)
	{
		element = new T(m_renderer);
		element->Create(name);
		Manager<T, N>::m_elements[index] = element;
	}

	return element;
}

template<typename T, size_t N>
void ResourceManager<T, N>::Remove(const Name& name)
{
	u32 index = name.GetID() % N;
	T* element = Manager<T, N>::m_elements[index];
	if (element)
	{
		element->Destroy();
		delete element;
		Manager<T, N>::m_elements[index] = nullptr;
	}
}

template<typename T, size_t N>
void ResourceManager<T, N>::RemoveAll()
{
	for (size_t i = 0; i < N; i++)
	{
		T* element = Manager<T, N>::m_elements[i];
		if (element)
		{
			element->Destroy();
			delete element;
			Manager<T, N>::m_elements[i] = nullptr;
		}
	}
}
