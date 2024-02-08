#ifndef RTSCENE_SYSTEM_H_
#define RTSCENE_SYSTEM_H_

#include <unordered_map>
#include <core/system.h>
#include <scene/scene.h>

namespace rhythm_typer {
	namespace scene {
		using SceneId = int;

		enum class SceneType {
			Custom
		};

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

			bool SwitchScene(SceneId target_scene, bool destroy_previous_scene = true);

		protected:
			IScene* current_scene{ nullptr };
			bool switching_scene_{ false };
			std::unordered_map<SceneId, IScene*> alive_scenes_{};

			void Update(float delta_time) override;
		};
	}
}

#include <scene/scene_system.tcc>

#endif