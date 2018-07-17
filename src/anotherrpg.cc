#include "anotherrpg.hh"
#include <iostream>
#include <SDL.h>

using namespace Window;

namespace Game {
    AnotherRpg::AnotherRpg(MainWindow& window):
        win_{window}
    {
        std::cout << "Hello, world!" << std::endl;
    }

    void AnotherRpg::run() {
        SDL_Event e;
        bool quit{false};

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
            
            win_.clear();
            win_.update();

            SDL_Delay(1000);
        }
    }
}
