#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <SDL.h>

#include <event/event_system.h>

namespace rhythm_typer {
	namespace event {
		void EventSystem::Update(float delta_time)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event) > 0) {
				event_cancelled_ = false;
				auto it = handlers_.find(event.type);
				if (it == handlers_.end()) {
					continue;
				}
				std::vector<EventHandler>& event_handlers = it->second;
				std::vector<bool>& once_list = handlers_once_[event.type];
				for (std::size_t i = 0; i < event_handlers.size(); i++) {
					if (!event_cancelled_) {
						event_handlers[i](*this, event);
						if (once_list[i]) {
							event_handlers.erase(event_handlers.begin() + i);
							once_list.erase(once_list.begin() + i);
							i--;
						}
					}
				}
				if (event.type >= SDL_USEREVENT && event.type < SDL_LASTEVENT) {
					delete event.user.data1;
				}
			}
		}

		void EventSystem::RegisterHandler(SDL_EventType event_type, EventHandler handler, bool once)
		{
			if (handlers_.count(event_type) == 0) {
				handlers_[event_type] = std::vector<EventHandler>();
				handlers_once_[event_type] = std::vector<bool>();
			}
			handlers_[event_type].push_back(handler);
			handlers_once_[event_type].push_back(once);
		}

		void EventSystem::RemoveEventHandler(SDL_EventType event_type, EventHandler handler)
		{
			if (handlers_.count(event_type) > 0) {
				std::vector<EventHandler>& event_handlers = handlers_[event_type];
				std::vector<bool>& onces = handlers_once_[event_type];

				auto it = std::find(event_handlers.begin(), event_handlers.end(), handler);
				if (it != event_handlers.end()) {
					event_handlers.erase(it);
					onces.erase(onces.begin() + (it - event_handlers.begin()));
				}
			}
		}
	}
}