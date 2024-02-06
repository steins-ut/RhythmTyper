#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <SDL.h>

#include <debug/debug_system.h>

namespace rhythm_typer {
	namespace debug {
		void DebugSystem::Update(float delta_time) {
			frame_count_ = ((frame_count_ + 1) % 60) + ((frame_count_ + 1) / 60);
			elapsed_time_ = (elapsed_time_) * (frame_count_ != 1) + delta_time;

			const float fps = frame_count_ / elapsed_time_;
			printf("Average FPS: %f || Elapsed time: %f || Delta time: %f\n", fps, elapsed_time_, delta_time);
		}
	}
}