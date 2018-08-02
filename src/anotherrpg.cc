#include "anotherrpg.hh"
#include <iostream>
#include <SDL.h>
#include "map.hh"
#include "types.hh"
#include <ctime>

using Window::MainWindow;
using Character::Player;
using Level::Position;

namespace Game {
    AnotherRpg::AnotherRpg(MainWindow& window):
        win_{window},
        player_{std::make_shared<Player>()}, currentMap_{nullptr},
        eventCooldown_{false} {

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

            handleInput();

            SDL_Delay(10); // ~100 frames per second
        }
    }

    void AnotherRpg::handleInput() {
        if (input_.isKeyPressed() && !eventCooldown_) {
            if (input_.isMovement()) {
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

                // Update window only when player moves (for now)
                // TODO: create a var "dirty" to mark if render is needed
                win_.render();
                win_.update();
            }
            else if (input_.keyPressed() == Key::Interact) {
                Position pos = player_->facingPosition();
                auto npc = currentMap_->npcAt(pos.x, pos.y);
                if (npc) {
                    // TODO
                    std::cout << "Interact with: " << npc->textureName() << std::endl;
                }
            }

            // Quick hack to slow down movement etc ;)
            eventCooldown_ = true;
            static const unsigned int coolDown{125}; // milliseconds
            SDL_AddTimer(coolDown, [](Uint32 interval, void* coolDown) -> Uint32 { *(bool*)coolDown = false; return 0; }, &eventCooldown_);
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
        if (currentMap_->canMove(x, y)) {
            player_->moveTo(x, y);

            auto portal = currentMap_->portalAt(x, y);
            if (portal != nullptr) {
                // Transition between maps
                switchToMap(portal->destMap);

                player_->moveTo(portal->destX, portal->destY);
            }

            /*std::uniform_int_distribution<int> d{0, 100};
            std::cout << "random:" << d(rand_) << std::endl;*/

            return true;
        }
        else {
            player_->facePosition(x, y);

            return false;
        }
    }
}

