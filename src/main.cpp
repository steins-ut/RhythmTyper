#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 720, 0);

	SDL_Delay(3000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}