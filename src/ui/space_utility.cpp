#include <ui/space_utility.h>

namespace rhythm_typer {
	namespace ui {
		using namespace math;

		const Space& GetTopSpace(const Space& space) {
			const Space* current = &space;
			while (current->GetParent() != Space::null_space) {
				current = &current->GetParent();
			}
			return *current;
		}

		const Space& GetTopSpace(const Space& space, int& height_out) {
			const Space* current = &space;
			int out = 0;
			while (current->GetParent() != Space::null_space) {
				current = &current->GetParent();
				++out;
			}
			height_out = out;
			return *current;
		}

		int DepthBetweenSpaces(const Space& space, const Space& searched_parent) {
			if (space == searched_parent) { return 0; }
			if (space.GetParent() == Space::null_space) { return -1; }
			int distance = 0;
			bool searching = true;
			const Space* space_ptr = &space;
			while (searching) {
				if (space_ptr->GetParent() == Space::null_space) {
					distance = -1;
					searching = false;
				}
				else {
					distance++;
					searching = space_ptr->GetParent() != searched_parent;
					space_ptr = &space_ptr->GetParent();
				}
			}
			return distance;
		}

		const Space& FindCommonParentSpace(const Space& space1, const Space& space2) {
			if (space1 == space2) {
				return space1.GetParent();
			}

			int distance1;
			int distance2;
			GetTopSpace(space1, distance1);
			GetTopSpace(space2, distance2);
			const Space* space1_ptr = &space1;
			const Space* space2_ptr = &space2;

			while (distance2 > distance1) {
				space2_ptr = &space2_ptr->GetParent();
				--distance2;
			}
			while (distance1 > distance2) {
				space1_ptr = &space1_ptr->GetParent();
				--distance1;
			}

			while (distance1 >= 0) {
				space1_ptr = &space1_ptr->GetParent();
				space2_ptr = &space2_ptr->GetParent();
				--distance1;
				if (space1_ptr == space2_ptr) {
					return *space1_ptr;
				}
			}
			return Space::null_space;
		}

		Vector2 GetTopSpaceFactor(const Space& space) {
			Vector2 factor = Vector2::One();
			const Space* current_space = &space;
			while (current_space->GetParent() != Space::null_space) {
				const Vector2 current_factor = current_space->DomainToLocalFactor();
				factor.x *= current_factor.x;
				factor.y *= current_factor.y;
				current_space = &current_space->GetParent();
			}
			return factor;
		}
	}
}