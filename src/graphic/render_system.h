#ifndef RTRENDER_SYSEM_H_
#define RTRENDER_SYSEM_H_

#include <string>
#include <vector>
#include <map>
#include <SDL.h>

#include <core/system.h>
#include <ui/position.h>
#include <graphic/renderable.h>

#define RT_DEFAULT_TEXTURE_PRIORITY -100

namespace rhythm_typer {
	namespace graphic {
		class RenderSystem final : public core::ISystem {
		public:
			void AddToRenderQueue(const Renderable& renderable, ui::Position position, int priority = 0);
			void AddToRenderQueue(const Renderable& renderable, ui::Position position, ui::Space render_space, int priority = 0);
			void AddToRenderQueue(const Renderable& renderable, ui::Position position, math::Vector2 size, int priority = 0);
			void AddToRenderQueue(const Renderable& renderable, ui::Position position, math::Vector2 size, ui::Space render_space, int priority = 0);

			void RenderToTexture(const Renderable& source, TextureWrapper destination, math::Vector2 position, math::Vector2 size, int priority = RT_DEFAULT_TEXTURE_PRIORITY);
			void RenderToTexture(TextureWrapper source, TextureWrapper destination, math::Vector2 position, math::Vector2 size, int priority = RT_DEFAULT_TEXTURE_PRIORITY);

			void SetClearColor(Color color);
			TextureWrapper CreateTargetableTexture(int width, int height);
			TextureWrapper CreateTextureFromImage(std::string path);

			~RenderSystem() override;
		private:
			struct PriorityData {
				int render_count{ 0 };
				int render_reserve_size{ 0 };
				int vertex_reserve_size{ 0 };
				int index_reserve_size{ 0 };
				std::vector<SDL_Texture*> textures{};
				std::vector<SDL_Vertex> vertices{};
				std::vector<int> indices{};
				std::vector<int> num_vertices{};
				std::vector<int> num_indices{};

				void Clear();
				void Reserve();
			};

			SDL_Renderer* renderer_{ nullptr };
			std::vector<SDL_Texture*> created_textures_{};
			std::map<int, PriorityData> priority_holders_{};
			std::uint32_t renderer_format_{ 0 };
			Color clear_color_ = Color::black();

			bool Initialize() override;
			void Start() override;
			void Update(float delta_time) override;
		};
	}
}
#endif