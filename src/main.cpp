#include <iostream>

#include <SDL.h>

int main(int argc, char *argv[]) {
	std::cout << "Hello, world!" << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL_Init() failed: " << SDL_GetError() << std::endl;

		return 1;
	}

	return 0;
}
