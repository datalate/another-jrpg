#ifndef WORLDSTATE_HH
#define WORLDSTATE_HH

#include "state.hh"

namespace Game {
    class AnotherRpg;

    class WorldState : public State {
    public:
        explicit WorldState(AnotherRpg& rpg);
        ~WorldState();

        virtual void init();
        virtual void cleanup();

        virtual void update();
        virtual void draw();
    };
}

#endif
