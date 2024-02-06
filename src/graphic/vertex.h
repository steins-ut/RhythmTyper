#ifndef RTVERTEX_H_
#define RTVERTEX_H_

#include <math/vector2.h>
#include <graphic/color.h>

namespace rhythm_typer {
	namespace graphic {
		struct Vertex {
			math::Vector2 coords;
			Color color;
			math::Vector2 tex_coords;
		};
	}
}
#endif