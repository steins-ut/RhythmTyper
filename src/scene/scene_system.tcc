#ifndef RTSCENE_SYSTEM_TCC_
#define RTSCENE_SYSTEM_TCC_

#include <scene/scene_system.h>

namespace rhythm_typer {
	namespace scene {
		template <SceneType type>
		SceneId SceneSystem::CreateScene(SceneInfo scene_info, bool auto_switch) {
			return SceneId{ -1 };
		}

		template <SceneType type, typename T, typename... TArgs,  std::enable_if_t<std::is_base_of_v<IScene, T>, bool>>
		SceneId SceneSystem::CreateScene(SceneInfo scene_info, bool auto_switch, TArgs&&... args) {
			if(switching_scene_) {
				return SceneId{ -1 };
			}

			SceneId id = alive_scenes_.size();
			SceneId previous_id = (current_scene && !auto_switch) ? current_scene->GetId() : -1;

			T* scene = new T(id, previous_id, std::forward<TArgs>(args));

			IScene* scene = static_cast<IScene>(scene);
			scene->SetName(scene_info.name);
			scene->SetInstanceName(scene_info.name);

			alive_scenes_.emplace(id, next_scene);

			if (auto_switch) {
				RequestSceneSwitch(id);
			}

			return id;
		}
	}
}

#endif