#pragma once
#include "event.h"
#include "..\\engine\system.h"
#include "..\\core\core.h"

#include <list>
#include <map>
#include <functional>

template<typename TEvent>
class EventDispatcher : public System {
public:
	struct listener_t {
		Handle handle;
		std::function<bool(const TEvent&)> fp;

		bool operator == (const listener_t& other) const {
			return handle == other.handle;
		}
	};


	using listeners_t = std::list<listener_t>;

public:
	EventDispatcher(Engine* engine) : System(engine) {}

	Handle Subscribe(const Name& name, std::function<bool(const TEvent&)> fp) {
		listener_t listener;
		listener.fp = fp;
		listener.handle = ms_handle_id;
		ms_handle_id++;

		m_subscribers[name].push_back(listener);

		return listener.handle;
	}

	void Unsubscribe(const Name& name, const Handle& handle) {
		auto iter = m_subscribers.find(name);
		if (iter != m_subscribers.end()) {
			listeners_t listeners = iter->second;
			for (auto listener : listeners) {
				if (listener.handle == handle) {
					iter->second.remove(listener);
					break;
				}
			}
		}
	}

	void Notify(const TEvent& event) {
		auto iter = m_subscribers.find(event.name);
		if (iter != m_subscribers.end()) {
			listeners_t listeners = iter->second;
			for (auto listener : listeners) {
				listener.fp(event);
			}
		}
	}

protected:
	std::map<Name, listeners_t> m_subscribers;
	static Handle ms_handle_id;
};

template <typename TEvent>
Handle EventDispatcher<TEvent>::ms_handle_id = 0;