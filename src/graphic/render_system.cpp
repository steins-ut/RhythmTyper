#include <SDL_image.h>
#include <core/game.h>
#include <ui/space_utility.h>

#include <graphic/render_system.h>

namespace rhythm_typer {
	namespace graphic {
		using namespace core;
		using namespace math;
		using namespace ui;

		void RenderSystem::PriorityData::Clear() {
			render_count = 0;
			textures.clear();
			vertices.clear();
			indices.clear();
			num_vertices.clear();
			num_indices.clear();
		}

		void RenderSystem::PriorityData::Reserve() {
			textures.reserve(render_reserve_size);
			vertices.reserve(vertex_reserve_size);
			indices.reserve(index_reserve_size);
			num_vertices.reserve(render_reserve_size);
			num_indices.reserve(render_reserve_size);
			render_reserve_size = 0;
			vertex_reserve_size = 0;
			index_reserve_size = 0;
		}

		bool RenderSystem::Initialize() {
			renderer_ = RTGame::GetInstance().GetWindow().GetRenderer();
			SDL_RendererInfo renderer_info;
			if (SDL_GetRendererInfo(renderer_, &renderer_info) < 0) {
				return false;
			}
			renderer_format_ = renderer_info.texture_formats[0];
			return true;
		}

		void RenderSystem::Start() {};

		void RenderSystem::Update(float delta_time) {
			const SDL_Color clear_color = ColorToSdlColor(clear_color_);
			SDL_SetRenderDrawColor(renderer_, clear_color.r, clear_color.g, clear_color.b, clear_color.a);
			SDL_RenderClear(renderer_);
			SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
			for (auto& entry : priority_holders_) {
				PriorityData& priority_data = entry.second;
				int vertex_offset = 0;
				int index_offset = 0;
				for (int i = 0; i < priority_data.render_count; ++i) {
					SDL_RenderGeometry(renderer_, priority_data.textures[i],
						&priority_data.vertices[vertex_offset],
						priority_data.num_vertices[i],
						&priority_data.indices[index_offset],
						priority_data.num_indices[i]);
					vertex_offset += priority_data.num_vertices[i];
					index_offset += priority_data.num_indices[i];
				}
				priority_data.Clear();
				priority_data.Reserve();
			}
			SDL_RenderPresent(renderer_);
		}

		void RenderSystem::AddToRenderQueue(const Renderable& renderable, Position position, Vector2 size, Space render_space, int priority) {
			if (priority_holders_.count(priority) == 0) {
				priority_holders_.emplace(priority, PriorityData{});
			}

			PriorityData& priority_data = priority_holders_[priority];
			++priority_data.render_count;
			++priority_data.render_reserve_size;
			priority_data.index_reserve_size += renderable.GetIndices().size();
			priority_data.vertex_reserve_size += renderable.GetNormalizedVertices().size();

			Vector2 conversion_factor = GetTopSpaceFactor(render_space);
			const Vector2 render_size{ size.x * conversion_factor.x, size.y * conversion_factor.y };

			const Vector2 coords = GetRealCoords(ConvertToTopPosition(position));

			for (const Vertex& vertex : renderable.GetNormalizedVertices()) {
				priority_data.vertices.push_back({
					{ coords.x + vertex.coords.x * render_size.x, coords.y + vertex.coords.y * render_size.y * -1 },
					{ ColorToSdlColor(vertex.color) },
					{ vertex.tex_coords.x, vertex.tex_coords.y }
					});
			}

			priority_data.textures.push_back(renderable.GetTextureWrapper().GetTexture());
			priority_data.indices.insert(priority_data.indices.cend(),
				renderable.GetIndices().cbegin(), renderable.GetIndices().cend());
			priority_data.num_vertices.push_back(renderable.GetNormalizedVertices().size());
			priority_data.num_indices.push_back(renderable.GetIndices().size());
		}

		void RenderSystem::AddToRenderQueue(const Renderable& renderable, Position position, Space render_space, int priority) {
			AddToRenderQueue(renderable, position, renderable.GetSize(), render_space, priority);
		}

		void RenderSystem::AddToRenderQueue(const Renderable& renderable, Position position, Vector2 size, int priority) {
			AddToRenderQueue(renderable, position, size, RTGame::GetInstance().GetWindow().GetSpace(), priority);
		}

		void RenderSystem::AddToRenderQueue(const Renderable& renderable, Position position, int priority) {
			AddToRenderQueue(renderable, position, renderable.GetSize(), RTGame::GetInstance().GetWindow().GetSpace(), priority);
		}

		void RenderSystem::RenderToTexture(const Renderable& source, TextureWrapper destination, Vector2 position, Vector2 size, int priority) {
			if (!destination.GetTexture()) return;

			int access = -1;
			if (SDL_QueryTexture(destination.GetTexture(), NULL, &access, NULL, NULL) < 0) return;

			const Space& space = RTGame::GetInstance().GetWindow().GetSpace();
			AddToRenderQueue(source, Position{ space, position }, size, space, priority);
			std::vector<SDL_Texture*>& textures = priority_holders_[priority].textures;
			textures[textures.size() - 1] = destination.GetTexture();
		}

		void RenderSystem::RenderToTexture(TextureWrapper source, TextureWrapper destination, Vector2 position, Vector2 size, int priority) {
			if (!source.GetTexture()) return;

			RenderToTexture(Renderable{ source }, destination, position, size, priority);
		}

		void RenderSystem::SetClearColor(Color color) {
			clear_color_ = color;
		}

		TextureWrapper RenderSystem::CreateTargetableTexture(int width, int height) {
			SDL_Texture* texture = SDL_CreateTexture(renderer_, renderer_format_, SDL_TEXTUREACCESS_TARGET, width, height);
			created_textures_.push_back(texture);
			return TextureWrapper{ texture };
		}

		TextureWrapper RenderSystem::CreateTextureFromImage(std::string path) {
			SDL_Texture* tex = IMG_LoadTexture(renderer_, path.c_str());

			created_textures_.push_back(tex);
			return TextureWrapper{ tex };
		}

		RenderSystem::~RenderSystem() {
			for (SDL_Texture* texture : created_textures_)
				SDL_DestroyTexture(texture);
		}
	}
}