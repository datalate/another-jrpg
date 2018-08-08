#ifndef STATEMANAGER_HH
#define STATEMANAGER_HH

#include <vector>
#include <memory>
#include "state.hh"

namespace Game {
    class StateManager {
    public:
        StateManager();

        StateManager(const StateManager&) = delete; // disable copy
        void operator=(const StateManager&) = delete; // disable assign

        void init();

        void pushState(std::unique_ptr<State> state);
        void popState();

        bool isEmpty() const { return states_.empty(); }

        State& activeState() { return *states_.back(); }

    private:
        std::vector<std::unique_ptr<State>> states_;
    };
}

#endif
