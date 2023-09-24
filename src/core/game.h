#ifndef _RTGAME_H_
#define _RTGAME_H_

#include <cstddef>
#include <type_traits>
#include <assert.h>
#include <chrono>
#include <array>
#include <bitset>
#include <core/window.h>
#include <core/system.h>

#define RT_MAX_SYSTEM_COUNT 16

namespace rhythm_typer {
	namespace core {
		//The game class.
		class RTGame final {
		public:
			//Returns the singleton instance of the game.
			inline static RTGame& GetInstance() {
				static RTGame instance{};

				return instance;
			};

			//Adds a new system of type T to the game. There can only be
			//one of each type of system.
			template <typename T, typename... TArgs>
			inline T& AddSystem(TArgs&&... args) {
				//There can't be two of the same system
				assert(!HasSystem<T>());

				T* s = new T(std::forward<TArgs>(args)...);
				if (initialized_) {
					static_cast<ISystem*>(s)->Initialize();
				}
				systems_[GetSystemId<T>()] = s;
				return *s;
			}

			//Returns true if game has an instance of system T.
			template <typename T>
			inline bool HasSystem() {
				return systems_[GetSystemId<T>()] != nullptr;
			}

			//Returns the instance of system T if there is one.
			template <typename T>
			inline T& GetSystem() {
				//Check if system exists
				assert(HasSystem<T>());
				return *static_cast<T*>(systems_[GetSystemId<T>()]);
			}

			//Removes system T if there is one.
			template <typename T>
			inline void RemoveSystem() {
				//Check if system exists
				assert(HasSystem<T>());
				delete systems_[GetSystemId<T>()];
				systems_[GetSystemId<T>()] = nullptr;
			}

			//Initializes the game and it's systems. Returns true
			//if there are no errors, false if there are.
			bool Initialize();

			//Starts the game and it's systems. The game loop is
			//started and runs as long as IsRunning() returns true.
			void Start();

			//Returns true if game is running.
			inline bool IsRunning() { return running_; }

			//Returns a reference to the window object.
			inline RTWindow& GetWindow() { return window_; }

			//Stops the game loop
			inline void Stop() { running_ = false; }
		private:
			RTWindow window_;
			std::array<ISystem*, RT_MAX_SYSTEM_COUNT> systems_;
			bool initialized_;
			bool running_;

			RTGame() :
				window_{ "Rhythm Typer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 720, (SDL_WindowFlags)0 },
				systems_{},
				initialized_{ false },
				running_{ false }
			{ }

			//Gets the next system id.
			inline static std::uint32_t NextSystemId() {
				static std::uint32_t current_id = 0;
				assert(current_id < RT_MAX_SYSTEM_COUNT);
				return current_id++;
			}

			//Gets the id for system T.
			template <typename T>
			inline static std::uint32_t GetSystemId() {
				static_assert(std::is_base_of_v<ISystem, T>, "ONLY USE ISYSTEMS FOR SYSTEM RELATED FUNCTIONS.");
				static std::uint32_t id = NextSystemId();
				return id;
			}

			RTGame(const RTGame&) = delete;
			RTGame& operator=(const RTGame&) = delete;
			~RTGame() {};
		};
	}
}

#endif