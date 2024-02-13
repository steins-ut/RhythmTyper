#ifndef RTGAME_H_
#define RTGAME_H_

#include <array>
#include <functional>
#include <core/window.h>
#include <core/system.h>
#include <vector>

#define RT_MAX_SYSTEM_COUNT 16
#define RT_DEFAULT_WINDOW_NAME "Rhythm Typer"
#define RT_DEFAULT_WINDOW_WIDTH 960
#define RT_DEFAULT_WINDOW_HEIGHT 720

namespace rhythm_typer {
	namespace core {
		//The game class.
		class RTGame final {
		public:
			RTGame(const RTGame&) = delete;
			RTGame(RTGame&&) = delete;

			//Returns the singleton instance of the game.
			static RTGame& GetInstance() noexcept;

			//Adds a new system of type T to the game. There can only be
			//one of each type of system.
			template <typename T, typename... TArgs>
			T& AddSystem(TArgs&&... args);

			//Returns true if game has an instance of system T.
			template <typename T>
			bool HasSystem() noexcept;

			//Returns the instance of system T if there is one.
			template <typename T>
			T& GetSystem();

			//Removes system T if there is one.
			template <typename T>
			void RemoveSystem();

			//Initializes the game and it's systems. Returns true
			//if there are no errors, false if there are.
			bool Initialize();

			//Starts the game and it's systems. The game loop is
			//started and runs as long as IsRunning() returns true.
			void Start();

			//Queues the passed function to be executed in the next frame
			//before any systems are updated.
			void ExecuteOnNextFrame(std::function<void()> function);

			//Returns true if game is running.
			bool IsRunning() const noexcept;

			//Returns a reference to the window object.
			RTWindow& GetWindow() noexcept;

			//Stops the game loop
			void Stop();

			RTGame& operator=(const RTGame&) = delete;
			RTGame& operator=(RTGame&&) = delete;
		private:
			RTWindow window_;
			std::array<ISystem*, RT_MAX_SYSTEM_COUNT> systems_{};
			std::vector<std::function<void()>> current_frame_actions_{};
			std::vector<std::function<void()>> next_frame_functions_{};
			bool initialized_{ false };
			bool running_{ false };

			RTGame();

			//Gets the next system id.
			static std::uint32_t NextSystemId() noexcept;

			//Gets the id for system T.
			template <typename T>
			static std::uint32_t GetSystemId() noexcept;

			~RTGame();
		};
	}
}

#include <core/game.tcc>

#endif