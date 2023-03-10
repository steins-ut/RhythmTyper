#ifndef _RTWINDOW_H_
#define _RTWINDOW_H_
#include <SDL.h>

namespace rhythm_typer {
	namespace core {
		class RTWindow {
		public:
			RTWindow(const char* title, int x, int y, int w, int h, SDL_WindowFlags flags) :
				window_{ NULL },
				renderer_{ NULL },
				title_{ title },
				pos_{ x, y },
				size_{ w, h },
				flags_{ flags },
				initialized_{ false }
			{ }

			bool Initialize();
			inline SDL_Renderer& GetRenderer() const { return *renderer_; };
			inline bool HasInputFocus() const { return (SDL_GetWindowFlags(window_) & SDL_WINDOW_INPUT_FOCUS) > 0; }
			inline bool HasMouseFocus() const { return (SDL_GetWindowFlags(window_) & SDL_WINDOW_MOUSE_FOCUS) > 0; }
			inline bool IsMinimized() const { return (SDL_GetWindowFlags(window_) & SDL_WINDOW_MINIMIZED) > 0; }
			inline bool IsMaximized() const { return (SDL_GetWindowFlags(window_) & SDL_WINDOW_MAXIMIZED) > 0; }
			inline bool IsFullscreen() const { return (SDL_GetWindowFlags(window_) & SDL_WINDOW_FULLSCREEN) > 0; }
			inline bool IsBorderless() const { return (SDL_GetWindowFlags(window_) & SDL_WINDOW_BORDERLESS) > 0; }

			~RTWindow();
		private:
			SDL_Window* window_;
			SDL_Renderer* renderer_;
			const char* title_;
			SDL_Point pos_;
			SDL_Point size_;
			SDL_WindowFlags flags_;
			bool initialized_;
		};
	}
}
#endif
