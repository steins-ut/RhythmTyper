#ifndef _RTEVENT_SYSTEM_H_
#define _RTEVENT_SYSTEM_H_

#include <cstdint>
#include <type_traits>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <core/system.h>

#define RT_MAX_EVENTS 100

namespace rhythm_typer {
	namespace event {
		class EventSystem : public core::ISystem {
		public:
			EventSystem(std::uint32_t max_events = RT_MAX_EVENTS) :
				event_cancelled_{ false },
				max_events_{ max_events },
				handlers_{},
				handlers_once_{}
			{}

			typedef void (*EventHandler)(EventSystem& system, SDL_Event event);

			bool Initialize() { return true; }
			void Start() {}
			void Update(float delta_time);

			void RegisterHandler(SDL_EventType event_type, EventHandler handler, bool once = false);

			template <typename T>
			inline void RegisterHandler(EventHandler handler, bool once = false) {
				std::uint32_t event_type = GetCustomEventTypeId<T>();
				if (handlers_.count(event_type) == 0) {
					handlers_[event_type] = std::vector<EventHandler>();
					handlers_once_[event_type] = std::vector<bool>();
				}
				handlers_[event_type].push_back(handler);
				handlers_once_[event_type].push_back(once);
				return handlers_[event_type].size() - 1;
			}

			template<typename T>
			inline void PushCustomEvent(T t)
			{
				std::uint32_t type = GetCustomEventTypeId<T>();
				SDL_Event event;
				SDL_zero(event);
				event.type = type;
				event.user.data1 = new T(std::move(t));
				SDL_PushEvent(event);
			}

			inline void CancelEvent() { event_cancelled_ = true; }

			void RemoveEventHandler(SDL_EventType event_type, EventHandler handler);

			template<typename T>
			inline void RemoveEventHandler(EventHandler handler) {
				static_assert(std::is_integral_v<T>, "Do not put integral types in the template."
					"Use non templated override for SDL events.")

					std::uint32_t event_type = GetCustomEventTypeId<T>();
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

		private:
			bool event_cancelled_;
			std::uint32_t max_events_;
			std::unordered_map<std::uint32_t, std::vector<EventHandler>> handlers_;
			std::unordered_map<std::uint32_t, std::vector<bool>> handlers_once_;

			inline std::uint32_t NextEventTypeId() {
				static std::uint32_t current_id = SDL_RegisterEvents(max_events_);
				return current_id++;
			};

			template <typename T>
			inline std::uint32_t GetCustomEventTypeId() {
				static id = NextEventTypeId();
				return id;
			};
		};
	}
}
#endif