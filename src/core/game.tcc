#ifndef RTGAME_TCC_
#define RTGAME_TCC_

#include <type_traits>
#include <assert.h>
#include <array>
#include <core/system.h>

#include <core/game.h>

namespace rhythm_typer {
	namespace core {
		template <typename T, typename... TArgs>
		T& RTGame::AddSystem(TArgs&&... args) {
			//There can't be two of the same system
			assert(!HasSystem<T>());

			T* s = new T(std::forward<TArgs>(args)...);
			if (initialized_) {
				static_cast<ISystem*>(s)->Initialize();
			}
			systems_[GetSystemId<T>()] = s;
			return *s;
		}

		template <typename T>
		bool RTGame::HasSystem() noexcept {
			return systems_[GetSystemId<T>()] != nullptr;
		}

		template <typename T>
		T& RTGame::GetSystem() {
			//Check if system exists
			assert(HasSystem<T>());
			return *static_cast<T*>(systems_[GetSystemId<T>()]);
		}

		template <typename T>
		void RTGame::RemoveSystem() {
			//Check if system exists
			assert(HasSystem<T>());
			delete systems_[GetSystemId<T>()];
			systems_[GetSystemId<T>()] = nullptr;
		}

		template <typename T>
		std::uint32_t RTGame::GetSystemId() noexcept {
			static_assert(std::is_base_of_v<ISystem, T>, "ONLY USE ISYSTEMS FOR SYSTEM RELATED FUNCTIONS.");
			static std::uint32_t id = NextSystemId();
			return id;
		}
	}
}
#endif