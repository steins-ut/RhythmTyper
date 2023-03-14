#include <iostream>

#include "window.h"

namespace rhythm_typer {
	namespace core {
		bool RTWindow::Initialize() {
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
				std::cout << "SDL subsytem initialization failed: " << std::endl << SDL_GetError();
				return false;
			}

			window_ = SDL_CreateWindow(title_, pos_.x, pos_.y, size_.x, size_.y, flags_);
			if (window_ == NULL) {
				std::cout << "SDL window creation failed: " << std::endl << SDL_GetError();
				return false;
			}

			renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
			if (renderer_ == NULL) {
				std::cout << "SDL renderer creation failed: " << std::endl << SDL_GetError();
				return false;
			}

			initialized_ = true;
			return true;
		}

		RTWindow::~RTWindow()
		{
			SDL_DestroyRenderer(renderer_);
			SDL_DestroyWindow(window_);
			SDL_Quit();
		}
	}
}