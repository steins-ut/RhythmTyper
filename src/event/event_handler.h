#ifndef RTHANDLER_ID_H_
#define RTHANDLER_ID_H_

#include <cstdint>
#include <functional>
#include <SDL.h>

namespace rhythm_typer {
	namespace event {
		class EventInfo {
		public:
			bool GetCancelled() const noexcept;
			void SetCancelled(bool value) noexcept;
		private:
			bool cancelled_{ false };
		};

		class EventHandlerId {
		public:
			EventHandlerId(std::uint32_t event_type, long long id);
			std::uint32_t GetEventType() const noexcept;
			long long GetId() const noexcept;

			constexpr bool EventHandlerId::operator==(const EventHandlerId& other) const noexcept {
				return event_type_ == other.event_type_ && id_ == other.id_;
			}

			constexpr bool EventHandlerId::operator!=(const EventHandlerId& other) const noexcept {
				return !operator==(other);
			}
		private:
			std::uint32_t event_type_;
			long long id_;
		};

		using EventHandler = std::function<void(EventInfo&, SDL_Event)>;
	}
}

template <>
struct std::hash<rhythm_typer::event::EventHandlerId> {
	inline std::size_t operator()(const rhythm_typer::event::EventHandlerId& key) const {
		std::size_t h1 = std::hash<std::uint32_t>{}(key.GetEventType());
		std::size_t h2 = std::hash<long long>{}(key.GetId());
		return h1 ^ (h2 << h1);
	}
};

#endif