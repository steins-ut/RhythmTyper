#include <scene/scene_system.h>

#include "core/game.h"

namespace rhythm_typer {
	namespace scene {
		using namespace core;

		bool SceneSystem::RequestSceneSwitch(SceneId target_scene_id, bool destroy_previous_scene) {
			if (alive_scenes_.find(target_scene_id) == alive_scenes_.cend() || switching_scene_ || deleting_scene_) {
				return false;
			}

			std::function<void()> lambda = [&, target_scene_id, destroy_previous_scene]() {
				if (!current_scene) {
					SwitchScene(target_scene_id);
				}
				else if (current_scene->IsFrozen()) {
					const IScene* const previous_scene = current_scene;
					SwitchScene(target_scene_id);

					if (destroy_previous_scene) {
						DestroyScene(previous_scene->GetId());
					}
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

		bool SceneSystem::RequestSceneDestruction(SceneId target_scene_id) {
			const auto it = alive_scenes_.find(target_scene_id);
			if (it == alive_scenes_.cend() || switching_scene_ || deleting_scene_) {
				return false;
			}

			RTGame::GetInstance().ExecuteOnNextFrame([&, target_scene_id]() {
				DestroyScene(target_scene_id);
				});

			return true;
		}

		void SceneSystem::SwitchScene(SceneId target_scene_id) {
			current_scene = alive_scenes_[target_scene_id];
			if (current_scene->IsFrozen()) {
				current_scene->Unfreeze();
			}
			else {
				current_scene->Start();
			}

			switching_scene_ = false;
		}

		void SceneSystem::DestroyScene(SceneId target_scene_id) {
			const IScene* const scene = alive_scenes_[target_scene_id];
			if (current_scene == scene) {
				current_scene = nullptr;
			}
			delete scene;
			alive_scenes_.erase(target_scene_id);
			deleting_scene_ = false;
		}

		void SceneSystem::Update(float delta_time) {
			if (current_scene) {
				current_scene->Update(delta_time);
			}
		}
	}
}