#include "state.hh"

namespace Game {
    State::State(AnotherRpg& rpg): rpg_{rpg}, paused_{false}, redrawNeeded_{true} {
    }

    State::~State() {
    }
}
