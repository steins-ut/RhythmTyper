#ifndef _RTGAME_H_
#define _RTGAME_H_

#include <cstddef>
#include <type_traits>
#include <assert.h>
#include <chrono>
#include <array>
#include <bitset>
#include <window.h>
#include <system.h>

#define MAX_SYSTEM_COUNT 16

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
				assert(!system_bitset_[GetSystemId<T>()]);

				T* s = new T(std::forward<TArgs>(args)...);
				if (initialized_) {
					s->Initialize();
				}
				systems_[GetSystemId<T>()] = s;
				system_bitset_[GetSystemId<T>()] = true;
				return *s;
			}

			//Returns true if game has an instance of system T.
			template <typename T>
			inline bool HasSystem() {
				return system_bitset_[GetSystemId<T>()];
			}

			//Returns the instance of system T if there is one.
			template <typename T>
			inline T& GetSystem() {
				//Check if system exists
				assert(!system_bitset_[GetSystemId<T>()]);
				return systems_[GetSystemId<T>()];
			}

			//Removes system T if there is one.
			template <typename T>
			inline void RemoveSystem() {
				//Check if system exists
				assert(!system_bitset_[GetSystemId<T>()]);
				system_bitset_[GetSystemId<T>()] = false;
				delete systems_[GetSystemId<T>()];
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
		private:
			RTGame() :
				window_{ "Rhythm Typer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 720, (SDL_WindowFlags)0 },
				start_time{},
				systems_{},
				system_bitset_{},
				initialized_{ false },
				running_{ false }
			{ }

			//Gets the next system id.
			inline static std::size_t NextSystemId() {
				static std::size_t currId = 0;
				return currId++;
			}

			//Gets the id for system T.
			template <typename T>
			inline static std::size_t GetSystemId() {
				static_assert(std::is_base_of_v<ISystem, T>);
				static std::size_t id = NextSystemId();
				return id;
			}

			static RTGame instance_;
			RTWindow window_;
			std::chrono::steady_clock::time_point start_time;
			std::array<ISystem*, MAX_SYSTEM_COUNT> systems_;
			std::bitset<MAX_SYSTEM_COUNT> system_bitset_;
			bool initialized_;
			bool running_;

			RTGame(const RTGame&) = delete;
			RTGame& operator=(const RTGame&) = delete;
			~RTGame() {};
		};
	}
}

#endif