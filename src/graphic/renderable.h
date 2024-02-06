#ifndef RTRENDERABLE_H_
#define RTRENDERABLE_H_

#include <vector>
#include <math/vector2.h>
#include <graphic/vertex.h>
#include <graphic/texture_wrapper.h>

namespace rhythm_typer {
	namespace graphic {
		class Renderable {
		public:
			Renderable(TextureWrapper texture);
			Renderable(float width, float height);

			bool AddNormalizedVertex(Vertex vertex);
			bool AddNormalizedVertex(Vertex vertex, int position);
			bool UpdateVertex(Vertex vertex, int position) noexcept;
			bool RemoveVertex(int position) noexcept;
			void ClearVertices() noexcept;
			bool AddIndex(int index);
			bool AddIndex(int index, int position);
			bool UpdateIndex(int index, int position) noexcept;
			bool RemoveIndex(int position) noexcept;
			void ClearIndices() noexcept;
			void SetColor(Color color) noexcept;
			void ResetColor() noexcept;
			void SetScale(float x, float y) noexcept;
			void SetScale(math::Vector2 scale) noexcept;
			void ResetScale() noexcept;
			void SetUnscaledSize(math::Vector2 size) noexcept;
			void SetUnscaledSize(float width, float height) noexcept;
			void SetTexture(TextureWrapper texture) noexcept;

			const std::vector<Vertex>& GetNormalizedVertices() const noexcept;
			const std::vector<int>& GetIndices() const noexcept;
			math::Vector2 GetUnscaledSize() const noexcept;
			math::Vector2 GetSize() const noexcept;
			math::Vector2 GetScale() const noexcept;
			TextureWrapper GetTextureWrapper() const noexcept;

		private:
			std::vector<Vertex> normalized_vertices_{};
			std::vector<int> indices_{};
			math::Vector2 unscaled_size_{};
			math::Vector2 scale_{ 1, 1 };
			TextureWrapper texture_wrapper_{};
		};
	}
}
#endif