#include "anotherrpg.hh"
#include <iostream>
#include <SDL.h>
#include "map.hh"

using Window::MainWindow;
using Character::Player;
using Level::Position;

namespace Game {
    AnotherRpg::AnotherRpg(MainWindow& window):
        win_{window}, player_{std::make_shared<Player>()}, currentMap_{nullptr} {

        std::cout << "Game created" << std::endl;
    }

    void AnotherRpg::run() {
        bool quit{false};

        lvls_.loadFolder("lev/");

        if (!switchToMap("level0")) {
            quit = true;
        }

        SDL_Event e;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) { // move to input class
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                else if (e.type == SDL_WINDOWEVENT) {
                    if (e.window.event == SDL_WINDOWEVENT_SHOWN) {
                        win_.render();
                    }
                    else if (e.window.event == SDL_WINDOWEVENT_EXPOSED) {
                        win_.update();
                    }
                }
                else if (e.type == SDL_KEYDOWN) { // testing
                    switch (e.key.keysym.sym) {
                    case SDLK_w: {
                        const unsigned int x{player_->x()};
                        const unsigned int y{player_->y() - 1};
                        movePlayer(x, y);

                        break;
                    }
                    case SDLK_s: {
                        const unsigned int x{player_->x()};
                        const unsigned int y{player_->y() + 1};
                        movePlayer(x, y);

                        break;
                    }
                    case SDLK_a: {
                        const unsigned int x{player_->x() - 1};
                        const unsigned int y{player_->y()};
                        movePlayer(x, y);

                        break;
                    }
                    case SDLK_d: {
                        const unsigned int x{player_->x() + 1};
                        const unsigned int y{player_->y()};
                        movePlayer(x, y);

                        break;
                    }
                    default: { }
                    }

                    // TODO: only update when necessary

                    // Window is not updated on every frame
                    win_.render();
                    win_.update();
                }
            }
            
            SDL_Delay(10); // ~100 frames per second
        }
    }

    bool AnotherRpg::switchToMap(const std::string& map) {
        if (lvls_.exists(map)) {
            win_.clearRenderables();

            currentMap_ = lvls_[map];
            for (auto& tile : currentMap_->tiles()) {
                win_.addRenderable(tile);
            }
            win_.addRenderable(player_);

            if (currentMap_->hasPlayerSpawn()) {
                const Position& spawn{currentMap_->playerSpawn()};
                player_->moveTo(spawn.x, spawn.y);
            }

            std::cout << "initMap(\"" << map << "\")" << std::endl;
            return true;
	    }
        else {
            std::cout << "Failed to init map " << map << std::endl;
            return false;
        }
    }

    void AnotherRpg::movePlayer(unsigned int x, unsigned int y) {
        if (currentMap_->canMove(x, y)) {
            player_->moveTo(x, y);

            auto portal = currentMap_->portalAt(x, y);
            if (portal != nullptr) {
                // Transition between maps
                switchToMap(portal->destMap);

                player_->moveTo(portal->destX, portal->destY);
            }
        }
    }
}

