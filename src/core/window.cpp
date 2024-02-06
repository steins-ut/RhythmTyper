#include <utility>
#include <iostream>
#include <SDL.h>

#include <core/window.h>

namespace rhythm_typer {
	namespace core {
		RTWindow::RTWindow(const char* title, const int x, const int y, const int w, const int h, const SDL_WindowFlags flags) :
			title_{ title },
			pos_{ x, y },
			size_{ w, h },
			initial_flags_{ flags },
			space_{ ui::SpaceType::kRealSpace,
					{0, 0, static_cast<float>(w), static_cast<float>(h)},
					{static_cast<float>(w), static_cast<float>(h)} }
		{ }

		RTWindow::RTWindow(RTWindow&& other) noexcept : RTWindow() {
			swap(*this, other);
		}

		SDL_Renderer* RTWindow::GetRenderer() noexcept { return renderer_; }

		ui::Space& RTWindow::GetSpace() noexcept { return space_; }

		bool RTWindow::HasInputFocus() const noexcept { return (SDL_GetWindowFlags(window_) & SDL_WINDOW_INPUT_FOCUS) > 0; }
		
		bool RTWindow::HasMouseFocus() const noexcept { return (SDL_GetWindowFlags(window_) & SDL_WINDOW_MOUSE_FOCUS) > 0; }
		
		bool RTWindow::IsMinimized() const noexcept { return (SDL_GetWindowFlags(window_) & SDL_WINDOW_MINIMIZED) > 0; }
		
		bool RTWindow::IsMaximized() const noexcept { return (SDL_GetWindowFlags(window_) & SDL_WINDOW_MAXIMIZED) > 0; }
		
		bool RTWindow::IsFullscreen() const noexcept { return (SDL_GetWindowFlags(window_) & SDL_WINDOW_FULLSCREEN) > 0; }
		
		bool RTWindow::IsBorderless() const noexcept { return (SDL_GetWindowFlags(window_) & SDL_WINDOW_BORDERLESS) > 0; }

		bool RTWindow::Initialize() {
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
				std::cout << "SDL subsystem initialization failed: " << std::endl << SDL_GetError() << std::endl;
				return false;
			}

			window_ = SDL_CreateWindow(title_, pos_.x, pos_.y, size_.x, size_.y, initial_flags_);
			if (window_ == NULL) {
				std::cout << "SDL window creation failed: " << std::endl << SDL_GetError() << std::endl;
				return false;
			}

			renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
			if (renderer_ == NULL) {
				std::cout << "SDL renderer creation failed: " << std::endl << SDL_GetError() << std::endl;
				return false;
			}
			SDL_SetHintWithPriority(SDL_HINT_RENDER_VSYNC, "0", SDL_HINT_OVERRIDE);
			SDL_RenderSetVSync(renderer_, 0);

			initialized_ = true;
			return true;
		}

		void RTWindow::Close() {
			if(renderer_) 
				SDL_DestroyRenderer(renderer_);

			if(window_) 
				SDL_DestroyWindow(window_);

			renderer_ = nullptr;
			window_ = nullptr;
			SDL_Quit();
		}

		void swap(RTWindow& first, RTWindow& second) noexcept {
			using std::swap;

			swap(first.window_, second.window_);
			swap(first.renderer_, second.renderer_);
			swap(first.title_, second.title_);
			swap(first.pos_, second.pos_);
			swap(first.size_, second.size_);
			swap(first.initial_flags_, second.initial_flags_);
			swap(first.initialized_, second.initialized_);
			swap(first.space_, second.space_);
		}

		RTWindow& RTWindow::operator=(RTWindow&& other) noexcept {
			swap(*this, other);

			return *this;
		}

		RTWindow::~RTWindow() {
			Close();
		}
	}
}