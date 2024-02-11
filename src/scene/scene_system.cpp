#include <scene/scene_system.h>

#include "core/game.h"

namespace rhythm_typer {
	namespace scene {
		using namespace core;

		bool SceneSystem::RequestSceneSwitch(SceneId target_scene, bool destroy_previous_scene) {
			if(alive_scenes_.find(target_scene) == alive_scenes_.cend()) {
				return false;
			}

			std::function<void()> lambda = [&, target_scene, destroy_previous_scene]() {
				if(!current_scene) {
					SwitchScene(target_scene);
				}
				else if (current_scene->IsFrozen()) {
					if(destroy_previous_scene) {
						DeleteScene(target_scene);
					}

					SwitchScene(target_scene);
				}
				else {
					RTGame::GetInstance().ExecuteOnNextFrame(lambda);
				}
			};

			current_scene->Freeze();
			switching_scene_ = true;
			RTGame::GetInstance().ExecuteOnNextFrame(lambda);

			return true;
		}

		bool SceneSystem::DeleteScene(SceneId target_scene) {
			if (alive_scenes_.find(target_scene) == alive_scenes_.cend() || switching_scene_) {
				return false;
			}

			alive_scenes_.erase(current_scene->GetId());
			delete current_scene;
			return true;
		}

		void SceneSystem::SwitchScene(SceneId target_scene) {
			current_scene = alive_scenes_[target_scene];
			if (current_scene->IsFrozen()) {
				current_scene->Unfreeze();
			}
			else {
				current_scene->Start();
			}

			switching_scene_ = false;
		}

		void SceneSystem::Update(float delta_time) {
			if(current_scene) {
				current_scene->Update();
			}
		}
	}
}
