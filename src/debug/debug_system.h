#ifndef _RTDEBUG_SYSTEM_H_
#define _RTDEBUG_SYSTEM_H_

#include <cstdint>
#include <chrono>
#include <core/system.h>

namespace rhythm_typer {
	namespace debug {
		class DebugSystem final : public core::ISystem {
		public:
			DebugSystem() : frame_count{}, elapsed_time{}
			{ };

			void Start() {};
			void Update(float delta_time);

			~DebugSystem() {};
		private:
			long long frame_count;
			float elapsed_time;
		};
	}
}
#endif