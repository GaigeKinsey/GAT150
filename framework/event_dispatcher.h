#pragma once
#include "event.h"
#include "..\\engine\system.h"

#include <list>
#include <map>
#include <functional>

template<typename TEvent>
class EventDispatcher : public System {
public:
	using listeners_t = std::list<std::function<bool(const TEvent&)>>;

public:
	EventDispatcher(Engine* engine) : System(engine) {}

	void Subscribe(const Name& name, std::function<bool(const TEvent&)> listener) {
		m_subscribers[name].push_back(listener);
	}

	void Notify(const TEvent& event) {
		auto iter = m_subscribers.find(event.name);
		if (iter != m_subscribers.end()) {
			listeners_t listeners = iter->second;
			for (auto listener : listeners) {
				listener(event);
			}
		}
	}

protected:
	std::map<Name, listeners_t> m_subscribers;
};