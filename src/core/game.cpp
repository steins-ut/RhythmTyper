#include <cstdint>
#include <chrono>
#include <type_traits>
#include <vector>
#include <iostream>
#include <core/window.h>

#include <core/game.h>

namespace rhythm_typer {
	namespace core {
		bool RTGame::Initialize() {
			if (!window_.Initialize()) {
				std::cout << "Could not initialize game window." << std::endl;
				return false;
			}
			for (auto s : systems_) {
				if (s != NULL) {
					if (!s->Initialize()) {
						return false;
					}
				}
			}
			initialized_ = true;
			return true;
		}

		void RTGame::Start() {
			if (initialized_) {
				using GameClock = std::conditional <std::chrono::high_resolution_clock::is_steady,
					std::chrono::high_resolution_clock, std::chrono::steady_clock>::type;

				GameClock::time_point frame_start = GameClock::now();

				for (auto s : systems_) {
					if (s != NULL) {
						s->Start();
					}
				}

				GameClock::time_point frame_end = GameClock::now();
				float delta_time;

				running_ = true;
				while (running_) {
					delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(frame_end - frame_start).count() / 1000000000.f;
					frame_start = GameClock::now();
					for (auto system : systems_) {
						if (!running_) {
							break;
						}
						if (system != NULL) {
							system->Update(delta_time);
						}
					}
					frame_end = GameClock::now();
				}
			}
			else
				std::cout << "Game is not initialized yet, cannot start.";
		}
	}
}