#ifndef RTSCENE_SYSTEM_H_
#define RTSCENE_SYSTEM_H_

#include <unordered_map>
#include <core/system.h>
#include <scene/scene.h>

namespace rhythm_typer {
	namespace scene {
		enum class SceneType {
			Custom
		};
		//temporary
		struct SceneInfo {
			SceneType type;
			std::string name;
		};;

		class SceneSystem : public core::ISystem {
		public:
			template <SceneType type>
			SceneId CreateScene(SceneInfo scene_info, bool auto_switch = true);

			template <SceneType type = SceneType::Custom, typename T, typename... TArgs,
				std::enable_if_t<std::is_base_of_v<IScene, T>, bool> = true>
			SceneId CreateScene(SceneInfo scene_info, bool auto_switch = true, TArgs&&... args);

			bool RequestSceneSwitch(SceneId target_scene_id, bool destroy_previous_scene = true);
			bool RequestSceneDestruction(SceneId target_scene_id);

		protected:
			IScene* current_scene{ nullptr };
			IScene* next_scene{ nullptr };
			bool switching_scene_{ false };
			bool deleting_scene_{ false };
			std::unordered_map<SceneId, IScene*> alive_scenes_{};

			void SwitchScene(SceneId target_scene_id);
			void DestroyScene(SceneId target_scene_id);

			void Update(float delta_time) override;
		};
	}
}

#include <scene/scene_system.tcc>

#endif