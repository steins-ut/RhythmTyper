#ifndef RTSCENE_H_
#define RTSCENE_H_

#include <string>

namespace rhythm_typer {
	namespace scene {
		class IScene {
		public:
			void SetInstanceName(std::string name);

			const std::string& GetInstanceName() const noexcept;
			const std::string& GetName() const noexcept;

			virtual ~IScene() = 0;

		protected:
			std::string instance_name_;
			std::string name_;

			void SetName(std::string name);

			virtual void Start();
			virtual void Update();

			virtual void OnSwitch(IScene& new_scene);
			virtual void Freeze();
			virtual void Unfreeze();

			friend class SceneSystem;
		};
	}
}
#endif