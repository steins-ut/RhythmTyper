#include <cmath>
#include <cassert>
#include <math/vector2.h>
#include <ui/rect.h>

#include <ui/space.h>

namespace rhythm_typer {
	namespace ui {
		using namespace math;

		Space::Space() :
			parent_{ this },
			space_rect_{ 0, 0, 0, 0 },
			domain_size_{ 0, 0 }
		{}

		Space::Space(const SpaceType type, const FloatRect space_rect) : Space(null_space, type, space_rect) {}

		Space::Space(const SpaceType type, const FloatRect space_rect, const Vector2 domain_size) : Space(null_space, type, space_rect, domain_size) {}

		Space::Space(const Space& parent, SpaceType type, const FloatRect space_rect) :
			parent_{ &parent },
			type_{ type },
			space_rect_{ space_rect }
		{
			assert(space_rect_.width > 0 && space_rect_.height > 0);
			domain_size_ = Vector2{ std::floorf(space_rect_.width * RT_DEFAULT_SPACE_RATIO),
									std::floorf(space_rect_.height * RT_DEFAULT_SPACE_RATIO) };
		}

		Space::Space(const Space& parent, SpaceType type, const FloatRect space_rect, const Vector2 domain_size) :
			parent_{ &parent },
			type_{ type },
			space_rect_{ space_rect },
			domain_size_{ domain_size }
		{
			assert(space_rect_.width > 0 && space_rect_.height > 0);
			assert(domain_size_.x > 0 && domain_size_.y > 0);
		}

		const Space Space::null_space{};

		SpaceType Space::GetSpaceType() const noexcept { return type_; }

		Vector2 Space::GetDomainSize() const noexcept { return domain_size_; }

		const Space& Space::GetParent() const noexcept { return *parent_; }

		Vector2 Space::GetSize() const noexcept { return Vector2{ space_rect_.width, space_rect_.height }; }

		Vector2 Space::GetRealSize() const noexcept {
			return Vector2{
				parent_->GetSize().x * space_rect_.width * (type_ == SpaceType::kScaledSpace)
					+ space_rect_.width * (type_ == SpaceType::kRealSpace),
				parent_->GetSize().y * space_rect_.height * (type_ == SpaceType::kScaledSpace)
					+ space_rect_.height * (type_ == SpaceType::kRealSpace),
			};
		}

		Vector2 Space::GetPosition() const noexcept { return Vector2{ space_rect_.x, space_rect_.y }; }

		Vector2 Space::GetRealPosition() const noexcept {
			return Vector2{
				parent_->GetSize().x * space_rect_.x * (type_ == SpaceType::kScaledSpace)
					+ space_rect_.x * (type_ == SpaceType::kRealSpace),
				parent_->GetSize().y * space_rect_.y * (type_ == SpaceType::kScaledSpace)
					+ space_rect_.y * (type_ == SpaceType::kRealSpace),
			};
		}

		Vector2 Space::DomainToLocalFactor() const noexcept {
			return Vector2{
				(space_rect_.width / (domain_size_.x * (type_ == SpaceType::kRealSpace) + (type_ == SpaceType::kScaledSpace))),
				(space_rect_.height / (domain_size_.y * (type_ == SpaceType::kRealSpace) + (type_ == SpaceType::kScaledSpace))),
			};
		}

		void Space::SetPosition(const float x, const float y) {
			space_rect_.x = x;
			space_rect_.y = y;
		}

		void Space::Translate(const float x, const float y) {
			space_rect_.x += x;
			space_rect_.y += y;
		}

		void Space::SetSize(const float width, const float height) {
			space_rect_.width = width;
			space_rect_.height = height;
		}

		void Space::SetDomainSize(const float width, const float height) {
			domain_size_.x = width;
			domain_size_.y = height;
		}

		bool operator==(const Space& lhs, const Space& rhs) {
			return &lhs == &rhs;
		}

		bool operator!=(const Space& lhs, const Space& rhs) {
			return !operator==(lhs, rhs);
		}
	}
}