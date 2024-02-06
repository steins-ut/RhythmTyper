#ifndef RTCOLOR_H_
#define RTCOLOR_H_

#include <cstdint>
#include <SDL.h>

namespace rhythm_typer {
	namespace graphic {
		struct Color {
			float r;
			float g;
			float b;
			float a;

			static constexpr Color white() { return Color{ 255 / 255.f, 255 / 255.f, 255 / 255.f, 1 }; }
			static constexpr Color red() { return Color{ 255 / 255.f, 0, 0, 1 }; }
			static constexpr Color orange() { return Color{ 255 / 255.f, 102 / 255.f, 0, 1 }; }
			static constexpr Color yellow() { return Color{ 255 / 255.f, 255 / 255.f, 0, 1 }; }
			static constexpr Color green() { return Color{ 0, 255 / 255.f, 0, 255 / 255.f }; }
			static constexpr Color purple() { return Color{ 204 / 255.f, 136 / 255.f, 153 / 255.f, 1 }; }
			static constexpr Color magenta() { return Color{ 255 / 255.f, 0, 255 / 255.f, 1 }; }
			static constexpr Color pink() { return Color{ 246 / 255.f, 153 / 255.f, 205 / 255.f, 1 }; }
			static constexpr Color brown() { return Color{ 35 / 255.f, 23 / 255.f, 9 / 255.f, 1 }; }
			static constexpr Color blue() { return Color{ 0, 0, 255 / 255.f, 1 }; }
			static constexpr Color black() { return Color{ 0, 0, 0, 1 }; }
		};

		constexpr Color ColorFromIntRGBA(int r, int g, int b, int a) noexcept {
			return { r / 255.f, g / 255.f, b / 255.f, a / 255.f };
		}

		SDL_Color ColorToSdlColor(Color color);

	}
}
#endif