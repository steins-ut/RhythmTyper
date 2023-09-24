#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <SDL.h>

#include <debug/debug_system.h>

namespace rhythm_typer {
	namespace debug {
		void DebugSystem::Update(float delta_time) {
			frame_count++;
			elapsed_time += delta_time;
			float fps = frame_count / elapsed_time;
			printf("Average FPS: %f || Elapsed time: %f || Delta time: %f\n", fps, elapsed_time, delta_time);
		}
	}
}