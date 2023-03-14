#ifndef _RTEVENT_SYSTEM_H_
#define _RTEVENT_SYSTEM_H_

#include <cstdint>
#include <type_traits>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <system.h>

namespace rhythm_typer {
	namespace event {
		using namespace core;

		class EventSystem;
		typedef void (*EventHandler)(EventSystem& system, SDL_Event event);

		class EventSystem : public ISystem {
		public:
			EventSystem(std::uint32_t max_events = 100) : event_cancelled_{ false }, max_events_{ max_events }, handlers_{}, handlers_once_{}
			{}

			inline bool Initialize() { return true; }
			void Start() {}
			void Update(std::uint64_t delta_time);

			std::uint32_t RegisterHandler(SDL_EventType type, EventHandler handler, bool once = false);

			template <typename T>
			inline std::uint32_t GetCustomEventId() {
				static id = NextEventId();
				return id;
			};
			template <typename T> std::uint32_t RegisterHandler(EventHandler handler, bool once = false);

			void RemoveEventHandler(std::uint32_t type, std::uint32_t id);

			template <typename T> void PushCustomEvent(T& t);
			inline void CancelEvent() { event_cancelled_ = true; }
		private:
			inline std::uint32_t NextEventId() {
				static std::uint32_t currId = SDL_RegisterEvents(max_events_);
				return currId++;
			};

			bool event_cancelled_;
			std::uint32_t max_events_;
			std::unordered_map<std::uint32_t, std::vector<EventHandler>> handlers_;
			std::unordered_map<std::uint32_t, std::vector<bool>> handlers_once_;
		};
	}
}
#endif