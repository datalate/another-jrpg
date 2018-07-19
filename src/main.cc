#include <iostream>
#include <SDL.h>
#include "anotherrpg.hh"
#include "mainwindow.hh"

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL_Init() failed: " << SDL_GetError() << std::endl;

		return 1;
	}

    atexit(SDL_Quit);

    Window::MainWindow window;
    if (window.create(800, 640, "Another JRPG")) {
        Game::AnotherRpg rpg(window);
        rpg.run();
    }
    else {
        std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        return 1;
    }

	return 0;
}

