#include <cstdint>
#include <vector>
#include <iostream>
#include <window.h>

#include <game.h>

namespace rhythm_typer {
	namespace core {
		bool RTGame::Initialize() {
			if (!window_.Initialize()) {
				std::cout << "Could not initialize game window." << std::endl;
				return false;
			}
			for (int i = 0; i < MAX_SYSTEM_COUNT; i++) {
				if (system_bitset_[i]) {
					if (!systems_[i]->Initialize()) {
						return false;
					}
				}
			}
			initialized_ = true;
			return true;
		}

		void RTGame::Start() {
			if (initialized_) {
				for (int i = 0; i < MAX_SYSTEM_COUNT; i++) {
					if (system_bitset_[i]) {
						systems_[i]->Start();
					}
				}

				start_time = std::chrono::steady_clock::now();
				std::chrono::steady_clock::time_point frame_start = std::chrono::steady_clock::now();
				std::chrono::steady_clock::time_point frame_end = start_time;
				uint64_t delta_time;

				running_ = true;
				while (running_) {
					delta_time = (frame_end - frame_start).count();
					frame_start = std::chrono::steady_clock::now();
					for (int i = 0; i < MAX_SYSTEM_COUNT; i++) {
						if (system_bitset_[i]) {
							systems_[i]->Update(delta_time);
						}
					}
					frame_end = std::chrono::steady_clock::now();
				}
			}
			else
				std::cout << "Game is not initialized yet, cannot start.";
		}
	}
}