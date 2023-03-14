#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <SDL.h>

#include "event_system.h"

namespace rhythm_typer {
	namespace event {
		void EventSystem::Update(std::uint64_t delta_time)
		{
			SDL_Event evt;
			while (SDL_PollEvent(&evt) > 0) {
				event_cancelled_ = false;
				auto it = handlers_.find(evt.type);
				if (it == handlers_.end()) {
					return;
				}
				std::vector<EventHandler> evt_handlers = it->second;
				std::vector<bool> once_list = handlers_once_[evt.type];
				for (std::size_t i = 0; i < evt_handlers.size(); i++) {
					if (!event_cancelled_) {
						evt_handlers[i](*this, evt);
					}
					if (once_list[i]) {
						evt_handlers.erase(evt_handlers.begin() + i);
						once_list.erase(once_list.begin() + i);
						i--;
					}
				}
			}
		}

		std::uint32_t EventSystem::RegisterHandler(SDL_EventType type, EventHandler handler, bool once)
		{
			if (handlers_.count(type) == 0) {
				handlers_[type] = std::vector<EventHandler>();
				handlers_once_[type] = std::vector<bool>();
			}
			handlers_[type].push_back(handler);
			handlers_once_[type].push_back(once);
			return handlers_[type].size() - 1;
		}

		template <typename T>
		std::uint32_t EventSystem::RegisterHandler(EventHandler handler, bool once) {
			std::uint32_t type = GetCustomEventId<T>();
			if (handlers_.count(type) == 0) {
				handlers_[type] = std::vector<EventHandler>();
				handlers_once_[type] = std::vector<bool>();
			}
			handlers_[type].push_back(handler);
			handlers_once_[type].push_back(once);
			return handlers_[type].size() - 1;
		}

		template<typename T>
		void EventSystem::PushCustomEvent(T& t)
		{
			std::uint32_t type = GetCustomEventId<T>();
			SDL_Event evt;
			SDL_zero(evt);
			evt.type = type;
			evt.user.data1 = &t;
			SDL_PushEvent(evt);
		}

		void EventSystem::RemoveEventHandler(std::uint32_t type, std::uint32_t id)
		{
			if (handlers_.count(type) > 0) {
				std::vector<EventHandler> evt_handlers = handlers_[type];
				std::vector<bool> onces = handlers_once_[type];

				evt_handlers.erase(evt_handlers.begin() + id);
				onces.erase(onces.begin() + id);
			}
		}
	}
}