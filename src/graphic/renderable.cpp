#include <array>
#include <vector>
#include <graphic/vertex.h>
#include <graphic/texture_wrapper.h>
#include <graphic/renderable.h>

namespace rhythm_typer {
	namespace graphic {
		using namespace math;

		const std::array<Vertex, 4> DefaultVertices = { {
			{{0, 0}, {1, 1, 1, 1}, {0, 0}},
			{{0, -1}, {1, 1, 1, 1}, {0, 1}},
			{{1, -1}, {1, 1, 1, 1}, {1, 1}},
			{{1, 0}, {1, 1, 1, 1}, {1, 0}}
		} };

		const std::array<int, 6> DefaultIndices = { 0, 1, 2, 0, 2, 3 };

		Renderable::Renderable(TextureWrapper texture) :
			normalized_vertices_(DefaultVertices.cbegin(), DefaultVertices.cend()),
			indices_(DefaultIndices.cbegin(), DefaultIndices.cend()),
			unscaled_size_{ static_cast<float>(texture.GetWidth()),
							static_cast<float>(texture.GetHeight()) },
			texture_wrapper_{ texture }
		{ }

		Renderable::Renderable(float width, float height) :
			normalized_vertices_(DefaultVertices.cbegin(), DefaultVertices.cend()),
			indices_(DefaultIndices.cbegin(), DefaultIndices.cend()),
			unscaled_size_{ width,
							height }
		{}

		bool Renderable::AddNormalizedVertex(Vertex vertex) { return AddNormalizedVertex(vertex, normalized_vertices_.size()); }

		bool Renderable::AddNormalizedVertex(Vertex vertex, int position) {
			if (position < 0 || position > normalized_vertices_.size()) {
				return false;
			}

			if (vertex.coords.x < 0 || vertex.coords.x > 1 || vertex.coords.y < 0 || vertex.coords.y > 1) {
				return false;
			}

			if (vertex.tex_coords.x < 0 || vertex.tex_coords.x > 1 || vertex.tex_coords.y < 0 || vertex.tex_coords.y > 1) {
				return false;
			}

			normalized_vertices_.insert(normalized_vertices_.cbegin() + position, vertex);
			return true;
		}

		bool Renderable::UpdateVertex(Vertex vertex, int position) noexcept {
			if (position < 0 || position > normalized_vertices_.size()) {
				return false;
			}

			if (vertex.coords.x < 0 || vertex.coords.x > 1 || vertex.coords.y < 0 || vertex.coords.y > 1) {
				return false;
			}

			if (vertex.tex_coords.x < 0 || vertex.tex_coords.x > 1 || vertex.tex_coords.y < 0 || vertex.tex_coords.y > 1) {
				return false;
			}

			normalized_vertices_[position] = vertex;
			return true;
		}

		bool Renderable::RemoveVertex(int position) noexcept {
			if (position < 0 || position > normalized_vertices_.size()) {
				return false;
			}

			normalized_vertices_.erase(normalized_vertices_.cbegin() + position);
			return true;
		}

		void Renderable::ClearVertices() noexcept { normalized_vertices_.clear(); }

		bool Renderable::AddIndex(int index) {
			return AddIndex(index, indices_.size());
		}

		bool Renderable::AddIndex(int index, int position) {
			if (position < 0 || position > indices_.size()) {
				return false;
			}

			indices_.insert(indices_.cbegin() + position, index);
			return true;
		}

		bool Renderable::UpdateIndex(int index, int position) noexcept {
			if (position < 0 || position > indices_.size()) {
				return false;
			}

			indices_[position] = index;
			return true;
		}

		bool Renderable::RemoveIndex(int position) noexcept {
			if (position < 0 || position > indices_.size()) {
				return false;
			}

			indices_.erase(indices_.cbegin() + position);
			return true;
		}

		void Renderable::ClearIndices() noexcept { indices_.clear(); }

		void Renderable::SetColor(Color color) noexcept {
			for (Vertex& vertex : normalized_vertices_)
				vertex.color = color;
		}

		void Renderable::ResetColor() noexcept { SetColor(Color::white()); }

		void Renderable::SetScale(float x, float y) noexcept {
			scale_.x = x;
			scale_.y = y;
		}

		void Renderable::SetScale(Vector2 scale) noexcept { scale_ = scale; }

		void Renderable::ResetScale() noexcept { scale_ = Vector2::One(); }

		void Renderable::SetUnscaledSize(Vector2 size) noexcept { unscaled_size_ = size; }

		void Renderable::SetUnscaledSize(float width, float height) noexcept {
			unscaled_size_.x = width;
			unscaled_size_.y = height;
		}

		void Renderable::SetTexture(TextureWrapper texture) noexcept { texture_wrapper_ = texture; }

		const std::vector<Vertex>& Renderable::GetNormalizedVertices() const noexcept { return normalized_vertices_; }

		const std::vector<int>& Renderable::GetIndices() const noexcept { return indices_; }

		Vector2 Renderable::GetUnscaledSize() const noexcept { return unscaled_size_; }

		Vector2 Renderable::GetSize() const noexcept {
			return {
				unscaled_size_.x * scale_.x,
				unscaled_size_.y * scale_.y
			};
		}

		Vector2 Renderable::GetScale() const noexcept { return scale_; }

		TextureWrapper Renderable::GetTextureWrapper() const noexcept { return texture_wrapper_; }
	}
}