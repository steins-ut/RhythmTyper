#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <event/event_handler.h>

#include <event/event_system.h>

namespace rhythm_typer {
	namespace event {
		EventSystem::EventSystem(std::uint32_t max_events) :
			max_events_{ max_events }
		{}

		void EventSystem::Update(float delta_time)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event) > 0) {
				EventInfo event_info{};
				auto it = handlers_.find(event.type);
				if (it == handlers_.end()) {
					continue;
				}
				std::vector<std::pair<EventHandler, EventHandlerId>>& event_handlers = it->second;
				std::vector<bool>& once_list = handlers_once_[event.type];
				for (std::size_t i = 0; i < event_handlers.size(); i++) {
					if (event_info.GetCancelled()) {
						event_handlers[event_handlers.size() - 1].first(event_info, event);
						break;
					}
					event_handlers[i].first(event_info, event);
					if (once_list[i]) {
						EventHandlerId id = event_handlers[i].second;
						event_handlers.erase(event_handlers.begin() + i);
						once_list.erase(once_list.begin() + i);
						handler_indices_[id.GetEventType()].erase(id);
						i--;
					}
				}
			}
		}

		EventHandlerId EventSystem::RegisterHandler(SDL_EventType event_type, EventHandler handler, bool once) {
			return RegisterHandler(static_cast<std::uint32_t>(event_type), std::move(handler), once);
		}

		EventHandlerId EventSystem::RegisterHandler(std::uint32_t event_type, EventHandler handler, bool once)
		{
			std::vector<std::pair<EventHandler, EventHandlerId>>::iterator it;
			if (handlers_.count(event_type) == 0) {
				handlers_[event_type] = std::vector<std::pair<EventHandler, EventHandlerId>>{};
				handlers_once_[event_type] = std::vector<bool>{};
				handler_indices_[event_type] = std::unordered_map<EventHandlerId, std::size_t>{};
				it = handlers_[event_type].begin();
			}
			else {
				it = handlers_[event_type].end();
				if (event_type >= SDL_USEREVENT && event_type < SDL_LASTEVENT) {
					--it;
				}
			}

			const long long index = it - handlers_[event_type].begin();
			EventHandlerId id{ event_type, current_handler_id++ };
			handlers_[event_type].insert(it, std::make_pair(std::move(handler), id));
			handlers_once_[event_type].insert(handlers_once_[event_type].begin() + index, once);
			handler_indices_[event_type][id] = index;
			return id;
		}

		void EventSystem::RemoveHandler(EventHandlerId handler_id)
		{
			std::uint32_t event_type = handler_id.GetEventType();
			if (handlers_.count(handler_id.GetEventType()) > 0) {
				std::vector<std::pair<EventHandler, EventHandlerId>>& event_handlers = handlers_[event_type];
				std::unordered_map<EventHandlerId, std::size_t> event_handler_indices = handler_indices_[event_type];
				std::vector<bool>& event_handler_onces = handlers_once_[event_type];

				auto it = event_handler_indices.find(handler_id);
				if (it != event_handler_indices.end()) {
					const std::size_t index = it->second;
					event_handler_indices.erase(it);
					event_handlers.erase(event_handlers.begin() + index);
					event_handler_onces.erase(event_handler_onces.begin() + index);

					DecrementIndices(event_type, index);
				}
			}
		}

		std::uint32_t EventSystem::NextEventTypeId() const {
			static std::uint32_t current_id = SDL_RegisterEvents(max_events_);
			static std::uint32_t first_id = current_id;
			assert((current_id < std::numeric_limits<std::uint32_t>::max()) && (current_id < first_id + max_events_));
			return current_id++;
		}

		void EventSystem::DecrementIndices(std::uint32_t event_type, std::size_t removed_index) noexcept
		{
			std::unordered_map<EventHandlerId, std::size_t> event_handler_indices = handler_indices_[event_type];
			for (auto& entry : event_handler_indices) {
				if (entry.second > removed_index) {
					entry.second -= 1;
				}
			}
		}
	}
}