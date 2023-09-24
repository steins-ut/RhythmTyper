#ifndef _RTHANDLERID_H_
#define _RTHANDLERID_H_

#include <cstdint>
#include <functional>
#include <SDL.h>

namespace rhythm_typer {
	namespace event {
		class EventInfo {
		public:
			inline bool GetCancelled() const { return cancelled_; }
			inline void SetCancelled(bool value) { cancelled_ = value; };
		private:
			bool cancelled_{ false };
		};

		class EventHandlerId {
		public:
			EventHandlerId(std::uint32_t event_type, long long id) : event_type_{ event_type }, id_{ id } {}

			std::uint32_t GetEventType() const { return event_type_; }
			long long GetId() const { return id_; }

			inline bool operator==(const EventHandlerId& other) const {
				return event_type_ == other.event_type_ && id_ == other.id_;
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