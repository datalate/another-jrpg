#ifndef ANOTHER_RPG_HH
#define ANOTHER_RPG_HH

#include "SDL_video.h"
#include "mainwindow.hh"

namespace Game {
    class AnotherRpg {
        private:
            Window::MainWindow& win_;

        public:
            AnotherRpg(Window::MainWindow& win);
            
            void run();
    };
}

#endif
