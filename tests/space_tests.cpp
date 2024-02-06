#include <math/vector2.h>
#include <ui/space.h>
#include <ui/space_utility.h>
#include <ui/position.h>
#include <catch2/catch_test_macros.hpp>

using namespace rhythm_typer::math;
using namespace rhythm_typer::ui;

TEST_CASE("Coordinate tests", "[coordinates]") {
	Space parent{ SpaceType::kRealSpace, FloatRect{2, 2, 100, 100}, Vector2{5, 5} };
	Space child1{ parent, SpaceType::kRealSpace, FloatRect{ 0, 0, 1, 1 }, Vector2{ 10, 10 } };
	Space grandchild = { child1, SpaceType::kRealSpace, FloatRect{ 2, 2, 5, 5 }, Vector2{ 10, 10 } };

	SECTION("Position coords can be converted from the domain of the space to local coordinates") {
		const Position position{ parent, Vector2{2.5, 2.5} };
		const Position position2{ parent, Vector2{0, 0} };
		const Position position3{ grandchild, Vector2{5, 5} };

		REQUIRE(GetRealCoords(position) == Vector2{ 52, 52 });
		REQUIRE(GetRealCoords(position2) == Vector2{ 2, 2 });
		REQUIRE(GetRealCoords(position3) == Vector2{ 4.5f, 4.5f });
	}

	SECTION("Position coords can be converted from local domain to parent/top domain") {
		const Position position{ grandchild, Vector2{5, 5} };

		REQUIRE(ConvertToParentPosition(position).coords == Vector2{ 4.5f, 4.5f });
		INFO(GetRealCoords(ConvertToTopPosition(position)).x);
		REQUIRE(GetRealCoords(ConvertToTopPosition(position)) == Vector2{ 11, 11 });
	}
}

TEST_CASE("Space relation tests", "[space]") {
	Space space1{ SpaceType::kRealSpace, FloatRect{0, 0, 1, 1} };
	Space child1{ space1, SpaceType::kRealSpace, FloatRect{ 0, 0, 1, 1 } };
	Space grandchild = { child1, SpaceType::kRealSpace, FloatRect{ 0, 0, 1, 1 } };
	Space child2 = { space1, SpaceType::kRealSpace, FloatRect{ 0, 0, 1, 1 } };
	Space space2{ SpaceType::kRealSpace, FloatRect{0, 0, 1, 1} };

	SECTION("The parent of a top level space is null_space") {
		REQUIRE(space1.GetParent() == Space::null_space);
	}

	SECTION("The parent of a space is correctly stored") {
		REQUIRE(child1.GetParent() == space1);
		REQUIRE(child2.GetParent() == space1);
		REQUIRE(grandchild.GetParent() == child1);
	}

	SECTION("Top level parent of a space is successfully found") {
		REQUIRE(GetTopSpace(grandchild) == space1);
	}

	SECTION("Distance to parent in parent chain is calculated correctly") {
		REQUIRE(DepthBetweenSpaces(space1, space1) == 0);
		REQUIRE(DepthBetweenSpaces(space1, space2) == -1);
		REQUIRE(DepthBetweenSpaces(grandchild, space2) == -1);
		REQUIRE(DepthBetweenSpaces(grandchild, space1) == 2);
	}

	SECTION("Common parents of two spaces are found correctly") {
		REQUIRE(FindCommonParentSpace(space1, space1) == Space::null_space);
		REQUIRE(FindCommonParentSpace(space1, space2) == Space::null_space);
		REQUIRE(FindCommonParentSpace(grandchild, child1) == space1);
		REQUIRE(FindCommonParentSpace(grandchild, child2) == space1);
	}
}