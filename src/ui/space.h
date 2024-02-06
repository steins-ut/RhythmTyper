#ifndef RTSPACE_H_
#define RTSPACE_H_

#include <math/vector2.h>
#include <ui/rect.h>

#define RT_DEFAULT_SPACE_RATIO 1.f

namespace rhythm_typer {
	namespace ui {
		enum class SpaceType {
			kRealSpace,
			kScaledSpace
		};

		class Space {
		public:
			static const Space null_space;

			Space(SpaceType type, FloatRect space_rect);
			Space(SpaceType type, FloatRect space_rect, math::Vector2 domain_size);
			Space(const Space& parent, SpaceType type, FloatRect space_rect);
			Space(const Space& parent, SpaceType type, FloatRect space_rect, math::Vector2 domain_size);

			SpaceType GetSpaceType() const noexcept;
			const Space& GetParent() const noexcept;
			math::Vector2 GetSize() const noexcept;
			math::Vector2 GetRealSize() const noexcept;
			math::Vector2 GetPosition() const noexcept;
			math::Vector2 GetRealPosition() const noexcept;
			math::Vector2 GetDomainSize() const noexcept;
			math::Vector2 DomainToLocalFactor() const noexcept;

			void SetPosition(float x, float y);
			void Translate(float x, float y);
			void SetSize(float width, float height);
			void SetDomainSize(float width, float height);
		private:
			const Space* parent_{ nullptr };
			SpaceType type_{ SpaceType::kRealSpace };
			FloatRect space_rect_{};
			math::Vector2 domain_size_{};

			Space();
		};

		bool operator==(const Space& lhs, const Space& rhs);
		bool operator!=(const Space& lhs, const Space& rhs);
	}
}

#endif