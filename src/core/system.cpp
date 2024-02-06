#include <core/system.h>

namespace rhythm_typer {
	namespace core {
		bool ISystem::ForceInitialize() {
			return Initialize();
		}

		void ISystem::ForceStart() { Start(); }
		void ISystem::ForceUpdate(float delta_time) { Update(delta_time); }

		bool ISystem::Initialize() {
			return true;
		}

		void ISystem::Start() {}
		void ISystem::Update(float delta_time) {}

		ISystem::~ISystem() = default;
	}
}