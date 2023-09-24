#ifndef _RTEVENT_SYSTEM_H_
#define _RTEVENT_SYSTEM_H_

#include <cstdint>
#include <cassert>
#include <type_traits>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <SDL.h>
#include <core/system.h>
#include <event/event_handler.h>

#define RT_MAX_EVENTS 100

namespace rhythm_typer {
	namespace event {
		class EventSystem : public core::ISystem {
		public:
			EventSystem(std::uint32_t max_events = RT_MAX_EVENTS) :
				max_events_{ max_events },
				handlers_{},
				handlers_once_{},
				handler_indices_{}
			{}

			bool Initialize() { return true; }
			void Start() {}
			void Update(float delta_time);

			//Registers an EventHandler for SDL events of type event_type
			//If once is true, the event handler is only evoked for the first
			//event it recieves, and is then removed automatically.
			inline EventHandlerId RegisterHandler(SDL_EventType event_type, EventHandler handler, bool once = false) {
				return RegisterHandler(static_cast<std::uint32_t>(event_type), handler, once);
			};

			//Registers handler for SDL_UserEvent events carrying custom data.
			//If once is true, the event handler is only evoked for the first
			//event it recieves, and is then removed automatically.
			//USE NON TEMPLATED OVERRIDE FOR OTHER SDL EVENTS
			template <typename T>
			inline EventHandlerId RegisterHandler(EventHandler handler, bool once = false) {
				static_assert(!std::is_integral_v<T>, "Do not put integral types in the template."
					"Use non templated override for SDL events.");

				if (handlers_.count(GetCustomEventTypeId<T>()) == 0) {
					RegisterHandler(GetCustomEventTypeId<T>(), DeleteCustomEventData<T>, false);
				}
				return RegisterHandler(GetCustomEventTypeId<T>(), handler, once);
			}

			//Pushes an SDL_Event carrying custom data in member user.data1
			template<typename T>
			inline void PushCustomEvent(T t)
			{
				std::uint32_t type = GetCustomEventTypeId<T>();
				SDL_Event event{};
				SDL_zero(event);
				event.type = type;
				event.user.data1 = new T(std::move(t));
				SDL_PushEvent(&event);
			}

			void RemoveHandler(EventHandlerId handler_id);

		private:
			std::uint32_t max_events_;
			std::unordered_map<std::uint32_t, std::vector<std::pair<EventHandler, EventHandlerId>>> handlers_;
			std::unordered_map<std::uint32_t, std::vector<bool>> handlers_once_;
			std::unordered_map<std::uint32_t, std::unordered_map<EventHandlerId, std::size_t>> handler_indices_;
			long long current_handler_id = 0;

			//Gets the next event type id
			inline std::uint32_t NextEventTypeId() {
				static std::uint32_t current_id = SDL_RegisterEvents(max_events_);
				static std::uint32_t first_id = current_id;
				assert(current_id < first_id + max_events_);
				return current_id++;
			}

			//Gets the event type id for SDL_UserEvent carrying data of type T
			template <typename T>
			inline std::uint32_t GetCustomEventTypeId() {
				static std::uint32_t id = NextEventTypeId();
				return id;
			}

			//Event handler to delete custom data of SDL user events. This handler
			//is automatically added for SDL user events carrying custom data
			template <typename T>
			inline static void DeleteCustomEventData(EventInfo& event_info, SDL_Event event) {
				delete static_cast<T*>(event.user.data1);
				event_info.SetCancelled(true);
			};

			//Actual implementation of event handler registration.
			EventHandlerId RegisterHandler(std::uint32_t event_type, EventHandler handler, bool once);

			//Decrements the indices stored in handler_indices_ of all event handlers.
			void DecrementIndices(std::uint32_t event_type, std::size_t removed_index);
		};
	}
}
#endif