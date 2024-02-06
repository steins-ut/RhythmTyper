#ifndef RTRECT_H_
#define RTRECT_H_

#include <type_traits>

namespace rhythm_typer {
	namespace ui {
		template <typename T, std::enable_if_t<std::is_arithmetic_v<T>, bool> = true>
		struct Rect {
			T x;
			T y;
			T width;
			T height;
		};

		using IntRect = Rect<int>;
		using FloatRect = Rect<float>;

		template <typename T>
		void ScaleRect(Rect<T> rect, float width, float height = width) {
			rect.width *= width;
			rect.height *= height;
		}
	}
}

#endif