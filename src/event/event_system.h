#ifndef RTEVENT_SYSTEM_H_
#define RTEVENT_SYSTEM_H_

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
		class EventSystem final : public core::ISystem {
		public:
			EventSystem(std::uint32_t max_events = RT_MAX_EVENTS) :
				max_events_{ max_events }
			{}

			//Registers an EventHandler for SDL events of type event_type
			//If once is true, the event handler is only evoked for the first
			//event it receives, and is then removed automatically.
			EventHandlerId RegisterHandler(SDL_EventType event_type, EventHandler handler, bool once = false);

			//Registers handler for SDL_UserEvent events carrying custom data.
			//If once is true, the event handler is only evoked for the first
			//event it receives, and is then removed automatically.
			//USE NON TEMPLATE OVERRIDE FOR OTHER SDL EVENTS
			template <typename T>
			EventHandlerId RegisterHandler(EventHandler handler, bool once = false);

			//Pushes an SDL_Event carrying custom data in member user.data1
			template<typename T>
			void PushCustomEvent(T t);

			void RemoveHandler(EventHandlerId handler_id);

			~EventSystem() override = default;
		private:
			std::uint32_t max_events_{};
			std::unordered_map<std::uint32_t, std::vector<std::pair<EventHandler, EventHandlerId>>> handlers_{};
			std::unordered_map<std::uint32_t, std::vector<bool>> handlers_once_{};
			std::unordered_map<std::uint32_t, std::unordered_map<EventHandlerId, std::size_t>> handler_indices_{};
			long long current_handler_id{};

			//Gets the next event type id
			std::uint32_t NextEventTypeId() const;

			//Gets the event type id for SDL_UserEvent carrying data of type T
			template <typename T>
			std::uint32_t GetCustomEventTypeId() const;

			//Event handler to delete custom data of SDL user events. This handler
			//is automatically added for SDL user events carrying custom data
			template <typename T>
			static void DeleteCustomEventData(EventInfo& event_info, SDL_Event event);

			//Actual implementation of event handler registration.
			EventHandlerId RegisterHandler(std::uint32_t event_type, EventHandler handler, bool once);

			//Decrements the indices stored in handler_indices_ of all event handlers.
			void DecrementIndices(std::uint32_t event_type, std::size_t removed_index) noexcept;

			void Update(float delta_time) override;
		};
	}
}

#include <event/event_system.tcc>
#endif