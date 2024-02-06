#ifndef RTSPACE_UTILITY_H_
#define RTSPACE_UTILITY_H_

#include <ui/space.h>

namespace rhythm_typer {
	namespace ui {
			const Space& GetTopSpace(const Space& space);
			const Space& GetTopSpace(const Space& space, int& height_out);
			int DepthBetweenSpaces(const Space& space, const Space& searched_parent);
			const Space& FindCommonParentSpace(const Space& space1, const Space& space2);
			math::Vector2 GetTopSpaceFactor(const Space& space);
	}
}

#endif