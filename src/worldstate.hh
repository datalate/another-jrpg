#ifndef WORLDSTATE_HH
#define WORLDSTATE_HH

#include "state.hh"
#include <string>
#include <memory>
#include "levelmanager.hh"
#include "map.hh"
#include "player.hh"

namespace Game {
    class AnotherRpg;

    class WorldState : public State {
    public:
        explicit WorldState(AnotherRpg& rpg);
        ~WorldState();

        virtual bool init();
        virtual void cleanup();

        virtual void update(const Input& input);

    private:
        bool switchToMap(const std::string& map);
        bool movePlayer(unsigned int x, unsigned int y);

        Level::LevelManager lvls_;
        std::shared_ptr<Level::Map> currentMap_; // no ownership

        std::shared_ptr<Character::Player> player_; // has ownership

        bool eventCooldown_;
    };
}

#endif
