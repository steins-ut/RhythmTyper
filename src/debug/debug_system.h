#ifndef RTDEBUG_SYSTEM_H_
#define RTDEBUG_SYSTEM_H_

#include <vector>
#include <core/system.h>
#include <graphic/render_system.h>

namespace rhythm_typer {
	namespace debug {
		class DebugSystem final : public core::ISystem {
		public:
			DebugSystem() = default;

			~DebugSystem() override = default;
		private:
			int frame_count_{ 0 };
			float elapsed_time_{ 0 };
			std::vector<graphic::Renderable> renderables_{};

			void Update(float delta_time) override;
		};
	}
}
#endif