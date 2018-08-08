#include "state.hh"

namespace Game {
    State::State(AnotherRpg& rpg): rpg_{rpg}, paused_{false}, redrawNeeded_{true} {
    }

    State::~State() {
    }

    void State::draw(Window::MainWindow& window) {
        if (redrawNeeded_) {
            window.clear();
            window.render(renderables_);
            window.update();
        }
    }
}
