#include "anotherrpg.hh"
#include <iostream>
#include <SDL.h>

using namespace Window;

namespace Game {
    AnotherRpg::AnotherRpg(MainWindow& window):
        win_{window}, player_{new Player(1, 1)} {

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
                    switch (e.key.keysym.sym) {
                    case SDLK_w: {
                        const int x{player_->x()};
                        const int y{player_->y() - 1};

                        if (map_.canMove(x, y)) {
                            player_->moveTo(x, y);
                        }

                        break;
                    }
                    case SDLK_s: {
                        const int x{player_->x()};
                        const int y{player_->y() + 1};

                        if (map_.canMove(x, y)) {
                            player_->moveTo(x, y);
                        }

                        break;
                    }
                    case SDLK_a: {
                        const int x{player_->x() - 1};
                        const int y{player_->y()};

                        if (map_.canMove(x, y)) {
                            player_->moveTo(x, y);
                        }

                        break;
                    }
                    case SDLK_d: {
                        const int x{player_->x() + 1};
                        const int y{player_->y()};

                        if (map_.canMove(x, y)) {
                            player_->moveTo(x, y);
                        }

                        break;
                    }
                    default: { }
                    }
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
        win_.addRenderable(player_);
    }

}

