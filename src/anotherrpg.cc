#include "anotherrpg.hh"
#include <iostream>
#include <SDL.h>

using namespace Window;

namespace Game {
    AnotherRpg::AnotherRpg(MainWindow& window):
        win_{window}
    {
        std::cout << "Game created" << std::endl;
    }

    void AnotherRpg::run() {
        SDL_Event e;
        bool quit{false};

        map_.load();

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) { // move to input class
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                else if (e.type == SDL_KEYDOWN) { // testing
                    map_.tileAt(5, 1);
                }
            }
            
            win_.clear();
            win_.update();

            SDL_Delay(1000);
        }
    }
}
