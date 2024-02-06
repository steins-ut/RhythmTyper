#include <event/event_handler.h>

namespace rhythm_typer {
	namespace event {
		bool EventInfo::GetCancelled() const noexcept { return cancelled_; }
		void EventInfo::SetCancelled(bool value) noexcept { cancelled_ = value; };

		EventHandlerId::EventHandlerId(std::uint32_t event_type, long long id) : event_type_{ event_type }, id_{ id } {}

		std::uint32_t EventHandlerId::GetEventType() const noexcept { return event_type_; }
		long long EventHandlerId::GetId() const noexcept { return id_; }
	}
}