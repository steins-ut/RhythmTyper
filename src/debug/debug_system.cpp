#include <cstdint>
#include <iostream>
#include <stdio.h>

#include "debug_system.h"

using namespace rhythm_typer::core;

namespace rhythm_typer {
	namespace debug {
		void DebugSystem::Update(uint64_t delta_time) {
			frame_count++;
			elapsed_time += delta_time;
			float seconds = (double)elapsed_time / 1000000000;
			float fps = frame_count / seconds;
			printf("Average FPS: %f || Elapsed time: %f\n", fps, seconds);
		}
	}
}