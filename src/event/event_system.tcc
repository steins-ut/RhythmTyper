#ifndef RTEVENT_SYSTEM_TCC_
#define RTEVENT_SYSTEM_TCC_

#include <event/event_system.h>

namespace rhythm_typer {
	namespace event {
		template <typename T>
		EventHandlerId EventSystem::RegisterHandler(EventHandler handler, bool once) {
			static_assert(!std::is_integral_v<T>, "Do not put integral types in the template."
				"Use non template override for SDL events.");

			if (handlers_.count(GetCustomEventTypeId<T>()) == 0) {
				RegisterHandler(GetCustomEventTypeId<T>(), DeleteCustomEventData<T>, false);
			}
			return RegisterHandler(GetCustomEventTypeId<T>(), handler, once);
		}

		template<typename T>
		void EventSystem::PushCustomEvent(T t) {
			const std::uint32_t type = GetCustomEventTypeId<T>();
			SDL_Event event{};
			SDL_zero(event);
			event.type = type;
			event.user.data1 = new T(std::move(t));
			SDL_PushEvent(&event);
		}

		template <typename T>
		std::uint32_t EventSystem::GetCustomEventTypeId() const {
			static std::uint32_t id = NextEventTypeId();
			return id;
		}

		template <typename T>
		void EventSystem::DeleteCustomEventData(EventInfo& event_info, SDL_Event event) {
			delete static_cast<T*>(event.user.data1);
			event_info.SetCancelled(true);
		}
	}
}

#endif