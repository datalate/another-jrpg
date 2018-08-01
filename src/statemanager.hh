#ifndef STATEMANAGER_HH
#define STATEMANAGER_HH

#include <vector>
#include <memory>
#include "state.hh"

namespace Game {
    class StateManager {
    public:
        StateManager();
        // TODO: delete copy/assignment operators

        void init();

        void pushState(std::unique_ptr<State> state);
        void popState();

        bool isEmpty() const { return states_.empty(); }

        State& activeState() { return *states_.front(); }

    private:
        std::vector<std::unique_ptr<State>> states_;
    };
}

#endif
