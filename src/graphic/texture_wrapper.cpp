#include <graphic/texture_wrapper.h>

namespace rhythm_typer {
	namespace graphic {
		TextureWrapper::TextureWrapper(SDL_Texture* texture) : texture_pointer_{texture} {
			SDL_QueryTexture(texture, NULL, NULL, &width_, &height_);
		}

		SDL_Texture* TextureWrapper::GetTexture() const noexcept { return texture_pointer_; }
		int TextureWrapper::GetWidth() const noexcept { return width_; }
		int TextureWrapper::GetHeight() const noexcept { return height_; }
	}
}