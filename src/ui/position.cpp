#include <math/vector2.h>
#include <ui/space.h>
#include <ui/space_utility.h>

#include <ui/position.h>

namespace rhythm_typer {
	namespace ui {
		using namespace math;

		Position ConvertPosition(const Position position, const Space& target_space) {
			const Space* current_space = &position.space;
			Vector2 new_coords = position.coords;
			int distance = DepthBetweenSpaces(position.space, target_space);
			if (distance < 0) {
				return Position{};
			}

			while (distance > 0) {
				new_coords.x *= current_space->DomainToLocalFactor().x;
				new_coords.y *= current_space->DomainToLocalFactor().y;
				current_space = &current_space->GetParent();
				distance--;
			}
			return Position{ target_space, new_coords };
		}

		Position ConvertToParentPosition(const Position position) {
			if (position.space.GetParent() == position.space) {
				return position;
			}

			return Position{ position.space.GetParent(), GetRealCoords(position) };
		}

		Position ConvertToTopPosition(const Position position) {
			const Space& top = GetTopSpace(position.space);
			const Space* current_space = &position.space;
			Vector2 new_coords = position.coords;
			while (*current_space != top) {
				const Vector2 factor = current_space->DomainToLocalFactor();
				const Vector2 real_position = current_space->GetRealPosition();
				new_coords.x = new_coords.x * factor.x + real_position.x;
				new_coords.y = new_coords.y * factor.y + real_position.y;
				current_space = &current_space->GetParent();
			}
			return Position{ top, new_coords };
		}

		Vector2 GetRealCoords(const Position position) {
			const Vector2 factor = position.space.DomainToLocalFactor();
			const Vector2 real_position = position.space.GetRealPosition();
			return Vector2{ real_position.x + position.coords.x * factor.x,
							real_position.y + position.coords.y * factor.y };
		}
	}
}
