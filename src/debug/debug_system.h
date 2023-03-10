#ifndef _RTDEBUG_SYSTEM_H_
#define _RTDEBUG_SYSTEM_H_

#include <cstdint>
#include <chrono>
#include <system.h>

namespace rhythm_typer {
	namespace debug {
		class DebugSystem final : public core::ISystem {
		public:
			DebugSystem() : frame_count{}, elapsed_time{}
			{ };

			void Start() {};
			void Update(uint64_t delta_time);

			~DebugSystem() {};
		private:
			uint64_t frame_count;
			uint64_t elapsed_time;
		};
	}
}
#endif