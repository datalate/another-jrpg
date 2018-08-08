#ifndef STATE_HH
#define STATE_HH

#include <vector>
#include <memory>
#include "input.hh"
#include "mainwindow.hh"
#include "renderable.hh"

namespace Game {
    class AnotherRpg;

    class State {
    public:
        explicit State(AnotherRpg& rpg);
        virtual ~State();

        State(const State&) = delete; // disable copy
        void operator=(const State&) = delete; // disable assign

        virtual bool init() = 0;
        virtual void cleanup() = 0;

        virtual void update(const Input& input) = 0;
        virtual void draw(Window::MainWindow& window) = 0;

        virtual void pause() { paused_ = true; }
        virtual void resume() { paused_ = false; }

    protected:
        AnotherRpg& rpg_;
        std::vector<std::shared_ptr<Renderable>> renderables_; // no ownership

        bool paused_;
        bool redrawNeeded_;
    };
}

#endif
