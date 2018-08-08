#include "anotherrpg.hh"
#include <iostream>
#include <SDL.h>
#include "types.hh"
#include <ctime>
#include "worldstate.hh"
#include <memory>

using Window::MainWindow;

namespace Game {
    AnotherRpg::AnotherRpg(MainWindow& window):
        win_{window} {

        std::random_device r;
        if (r.entropy() != 0) {
            rand_.seed(r());
        }
        else {
            rand_.seed((int)time(NULL));
        }

        std::cout << "Game created" << std::endl;
    }

    void AnotherRpg::run() {
        bool quit{false};

        stateManager_.init();
        stateManager_.pushState(std::make_unique<WorldState>(*this));

        SDL_Event e;
        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                //else if (e.type ==
                else if (e.type == SDL_WINDOWEVENT) {
                    if (e.window.event == SDL_WINDOWEVENT_SHOWN) {
                        //win_.render();
                        if (!stateManager_.isEmpty()) {
                            stateManager_.activeState().draw(win_);
                        }
                    }
                    else if (e.window.event == SDL_WINDOWEVENT_EXPOSED) {
                        win_.update();
                    }
                }
                else {
                    // SDL_QUIT and SDL_WINDOWEVENT are not needed for updating input
                    input_.update(e);
                }
            }

            if (!stateManager_.isEmpty()) {
                stateManager_.activeState().update(input_);
                stateManager_.activeState().draw(win_);
            }

            SDL_Delay(10); // ~100 frames per second
        }
    }
}

