#ifndef RTSCENE_H_
#define RTSCENE_H_

#include <string>

namespace rhythm_typer {
	namespace scene {
		using SceneId = int;

		class IScene {
		public:
			IScene(SceneId id, SceneId previous_id_);

			virtual void Freeze() = 0;
			virtual void Unfreeze() = 0;

			void SetInstanceName(std::string name);

			SceneId GetId() const noexcept;
			const std::string& GetInstanceName() const noexcept;
			const std::string& GetName() const noexcept;
			virtual bool IsFrozen() const noexcept = 0;

			virtual ~IScene() = 0;

		protected:
			SceneId id_;
			SceneId previous_id_;
			std::string instance_name_;
			std::string name_;

			void SetName(std::string name);

			virtual void Start();
			virtual void Update();

			virtual void OnSwitch(IScene& new_scene);

			friend class SceneSystem;
		};
	}
}
#endif