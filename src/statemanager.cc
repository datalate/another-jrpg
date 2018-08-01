#include "statemanager.hh"

namespace Game {
    StateManager::StateManager() {
    }

    void StateManager::init() {
    }

    void StateManager::pushState(std::unique_ptr<State> state) {
        states_.push_back(std::move(state));
        states_.back()->init();
    }

    void StateManager::popState() {
        states_.back()->cleanup();
        states_.pop_back();
    }
}
