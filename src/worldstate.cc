#include "worldstate.hh"
#include "anotherrpg.hh"
#include "types.hh"
#include <iostream>

using Character::Player;
using Level::Position;

namespace Game {
    WorldState::WorldState(AnotherRpg& rpg):
        State{rpg},
        player_{std::make_shared<Player>()}, currentMap_{nullptr},
        eventCooldown_{false} {
    }

    WorldState::~WorldState() {
    }

    bool WorldState::init() {
        lvls_.loadFolder("lev/");

        if (!switchToMap("level0")) {
            return false;
        }
        else {
            return true;
        }
    }

    void WorldState::cleanup() {
    }

    void WorldState::update(const Input& input) {
        if (input.isKeyPressed() && !eventCooldown_ && !paused_) {
            if (input.isMovement()) {
                unsigned int x{player_->x()};
                unsigned int y{player_->y()};

                switch (input.keyPressed()) {
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
                redrawNeeded_ = true; // Update window only when player moves (for now)
            }
            else if (input.keyPressed() == Key::Interact) {
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

    void WorldState::draw(Window::MainWindow& window) {
        if (redrawNeeded_) {
            window.render(renderables_);
            window.update();
        }
    }

    bool WorldState::switchToMap(const std::string& map) {
        if (lvls_.exists(map)) {
            currentMap_ = lvls_[map];

            renderables_.clear();
            for (auto& tile : currentMap_->tiles()) {
                renderables_.push_back(tile);
            }
            for (auto& npc : currentMap_->npcs()) {
                renderables_.push_back(npc);
            }
            renderables_.push_back(player_);

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

    bool WorldState::movePlayer(unsigned int x, unsigned int y) {
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
