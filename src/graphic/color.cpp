#include <SDL.h>
#include <graphic/color.h>

namespace rhythm_typer {
	namespace graphic {
		SDL_Color ColorToSdlColor(Color color) {
			return {
				static_cast<unsigned char>(color.r * 255),
				static_cast<unsigned char>(color.g * 255),
				static_cast<unsigned char>(color.b * 255),
				static_cast<unsigned char>(color.a * 255)
			};
		}
	}
}