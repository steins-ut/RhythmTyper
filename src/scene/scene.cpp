#include <utility>
#include <string>
#include <scene/scene.h>

namespace rhythm_typer {
	namespace scene {
		IScene::IScene(SceneId id, SceneId previous_id) : id_{ id }, previous_id_{ previous_id } {}

		void IScene::SetName(std::string name) { name_ = std::move(name); }
		void IScene::SetInstanceName(std::string instance_name) { instance_name_ = std::move(instance_name); }

		SceneId IScene::GetId() const noexcept { return id_; }
		const std::string& IScene::GetName() const noexcept { return name_; }
		const std::string& IScene::GetInstanceName() const noexcept { return instance_name_; }

		void IScene::Start() {}
		void IScene::Update() {}

		void IScene::OnSwitch(IScene& new_scene) {}

		void IScene::Freeze() {}
		void IScene::Unfreeze() {}

		IScene::~IScene() = default;
	}
}