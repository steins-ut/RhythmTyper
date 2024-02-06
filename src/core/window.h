#ifndef RTWINDOW_H_
#define RTWINDOW_H_

#include <SDL.h>
#include <ui/space.h>

namespace rhythm_typer {
	namespace core {
		class RTWindow {
		public:
			RTWindow(const char* title, int x, int y, int w, int h, SDL_WindowFlags flags);
			RTWindow(const RTWindow&) = delete;
			RTWindow(RTWindow&& other) noexcept;

			bool Initialize();
			void Close();
			SDL_Renderer* GetRenderer() noexcept;
			ui::Space& GetSpace() noexcept;
			bool HasInputFocus() const noexcept;
			bool HasMouseFocus() const noexcept;
			bool IsMinimized() const noexcept;
			bool IsMaximized() const noexcept;
			bool IsFullscreen() const noexcept;
			bool IsBorderless() const noexcept;

			friend void swap(RTWindow& first, RTWindow& second) noexcept;

			RTWindow& operator=(const RTWindow&) = delete;
			RTWindow& operator=(RTWindow&& other) noexcept;

			~RTWindow();
		private:
			RTWindow() = default;

			SDL_Window* window_{ nullptr };
			SDL_Renderer* renderer_{ nullptr };
			const char* title_{ nullptr };
			SDL_Point pos_{};
			SDL_Point size_{};
			SDL_WindowFlags initial_flags_{};
			bool initialized_{ false };
			ui::Space space_{ ui::SpaceType::kRealSpace ,ui::FloatRect{} };
		};
	}
}
#endif
