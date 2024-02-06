#ifndef RTTEXTURE_WRAPPER_H_
#define RTTEXTURE_WRAPPER_H_

#include <SDL.h>

namespace rhythm_typer {
	namespace graphic {
		class TextureWrapper {
		public:
			TextureWrapper() = default;
			TextureWrapper(SDL_Texture* texture);

			SDL_Texture* GetTexture() const noexcept;
			int GetWidth() const noexcept;
			int GetHeight() const noexcept;

		private:
			SDL_Texture* texture_pointer_{ NULL };
			int width_{ 0 };
			int height_{ 0 };
		};
	}
}

#endif