#ifndef ANOTHER_RPG_HH
#define ANOTHER_RPG_HH

#include "mainwindow.hh"
#include "input.hh"
#include "statemanager.hh"
#include <random>

namespace Game {
    class AnotherRpg {
    public:
        explicit AnotherRpg(Window::MainWindow& win);

        AnotherRpg(const AnotherRpg&) = delete; // disable copy
        void operator=(const AnotherRpg&) = delete; // disable assign

        void run();

    private:
        Window::MainWindow& win_;
        Input input_;
        StateManager stateManager_;

        std::mt19937 rand_;
    };
}

#endif
