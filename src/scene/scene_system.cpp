#include <scene/scene_system.h>

namespace rhythm_typer {
	namespace scene {
		void SceneSystem::Update(float delta_time) {
			if (switching_scene_) {
				//switch scene here
				current_scene->Start();
			}
			else {
				if (current_scene) {
					current_scene->Update();
				}
			}
		}
	}
}