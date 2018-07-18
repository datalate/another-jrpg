#include "anotherrpg.hh"
#include <iostream>
#include <SDL.h>

using namespace Window;

namespace Game {
    AnotherRpg::AnotherRpg(MainWindow& window):
        win_{window} {

        std::cout << "Game created" << std::endl;
    }

    void AnotherRpg::run() {
        SDL_Event e;
        bool quit{false};

        map_.load();
        initMap();

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) { // move to input class
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                else if (e.type == SDL_KEYDOWN) { // testing
                    win_.clearRenderables();
                }
                else if (e.type == SDL_KEYUP) {
                    initMap();
                }
            }
            
            win_.clear();
            win_.render();
            win_.update();

            SDL_Delay(20); // ~50 frames per second
        }
    }

    void AnotherRpg::initMap() {
        for (auto& tile : map_.tileSet()) {
            win_.addRenderable(tile);
	    }
    }

}

