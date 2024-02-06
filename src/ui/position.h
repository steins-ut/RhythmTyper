#ifndef RTPOSITION_H_
#define RTPOSITION_H_

#include <math/vector2.h>
#include <ui/space.h>

namespace rhythm_typer {
	namespace ui {
		struct Position {
			const Space& space{ Space::null_space };
			math::Vector2 coords{};
		};

		Position ConvertPosition(Position position, const Space& target_space);
		Position ConvertToParentPosition(Position position);
		Position ConvertToTopPosition(Position position);
		math::Vector2 GetRealCoords(Position position);
	}
}

#endif