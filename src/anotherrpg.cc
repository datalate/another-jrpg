#include "anotherrpg.hh"
#include <iostream>
#include <SDL.h>
#include "map.hh"

using Window::MainWindow;
using Character::Player;
using Level::Position;

namespace Game {
    AnotherRpg::AnotherRpg(MainWindow& window):
        win_{window}, player_{std::make_shared<Player>()}, currentMap_{nullptr}, eventCooldown_{false} {

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
            while (SDL_PollEvent(&e)) {
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
                else {
                    // SDL_QUIT and SDL_WINDOWEVENT are not needed for updating input
                    input_.update(e);
                }
            }

            // TODO: move to another method
            if (input_.isKeyPressed()) {
                // TODO: check if player moves
                unsigned int x{player_->x()};
                unsigned int y{player_->y()};

                switch (input_.keyPressed()) {
                case Key::MoveUp: {
                    --y;
                    break;
                }
                case Key::MoveDown: {
                    ++y;
                    break;
                }
                case Key::MoveLeft: {
                    --x;
                    break;
                }
                case Key::MoveRight: {
                    ++x;
                    break;
                }
                default: break;
                }

                movePlayer(x, y);

                // Update window only when player moves
                win_.render();
                win_.update();
            }
            
            SDL_Delay(10); // ~100 frames per second
        }
    }

    bool AnotherRpg::switchToMap(const std::string& map) {
        if (lvls_.exists(map)) {
            currentMap_ = lvls_[map];

            win_.clearRenderables();
            for (auto& tile: currentMap_->tiles()) {
                win_.addRenderable(tile);
            }
            for (auto& npc: currentMap_->npcs()) {
                win_.addRenderable(npc);
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

    bool AnotherRpg::movePlayer(unsigned int x, unsigned int y) {
        if (!eventCooldown_ && currentMap_->canMove(x, y)) {
            player_->moveTo(x, y);

            auto portal = currentMap_->portalAt(x, y);
            if (portal != nullptr) {
                // Transition between maps
                switchToMap(portal->destMap);

                player_->moveTo(portal->destX, portal->destY);
            }

            // Quick hack to slow down movement ;)
            eventCooldown_ = true;
            static const unsigned int coolDown = 125;
            SDL_AddTimer(coolDown, [](Uint32 interval, void* coolDown) -> Uint32 { *(bool*)coolDown = false; return 0; }, &eventCooldown_);

            return true;
        }
        else {
            return false;
        }
    }
}

