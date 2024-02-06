#include <chrono>
#include <type_traits>
#include <iostream>
#include <core/window.h>

#include <core/game.h>

namespace rhythm_typer {
	namespace core {
		RTGame::RTGame() :
			window_{ RT_DEFAULT_WINDOW_NAME,
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					RT_DEFAULT_WINDOW_WIDTH,
					RT_DEFAULT_WINDOW_HEIGHT,
					static_cast<SDL_WindowFlags>(0) },
			systems_{ },
			initialized_{ false },
			running_{ false }
		{ }

		RTGame& RTGame::GetInstance() noexcept {
			static RTGame instance{};
			return instance;
		};

		RTWindow& RTGame::GetWindow() noexcept { return window_; }
		bool RTGame::IsRunning() const noexcept { return running_; }

		bool RTGame::Initialize() {
			if (!window_.Initialize()) {
				std::cout << "Could not initialize game window." << std::endl;
				return false;
			}
			for (ISystem* system : systems_) {
				if (system) {
					if (!system->Initialize()) {
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

				for (ISystem* system : systems_) {
					if (system) {
						system->Start();
					}
				}

				GameClock::time_point frame_end = GameClock::now();

				running_ = true;
				while (running_) {
					const float delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(frame_end - frame_start).count() / 1000000000.f;
					frame_start = GameClock::now();
					for (ISystem* system : systems_) {
						if (!running_) {
							break;
						}
						if (system) {
							system->Update(delta_time);
						}
					}
					frame_end = GameClock::now();
				}

				initialized_ = false;
				for (ISystem* system : systems_)
					delete system;

				window_.Close();
			}
			else
				std::cout << "Game is not initialized yet, cannot start.";
		}

		void RTGame::Stop() {
			running_ = false;
			initialized_ = false;
		}

		std::uint32_t RTGame::NextSystemId() noexcept {
			static std::uint32_t current_id = 0;
			assert(current_id < RT_MAX_SYSTEM_COUNT);
			return current_id++;
		}

		RTGame::~RTGame() {
			Stop();
		}
	}
}