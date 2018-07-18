#ifndef ANOTHER_RPG_HH
#define ANOTHER_RPG_HH

#include "mainwindow.hh"
#include "map.hh"

namespace Game {
    class AnotherRpg {
        public:
            AnotherRpg(Window::MainWindow& win);
            
            void run();
        
        private:
            Window::MainWindow& win_;
            Level::Map map_;

            void initMap();
    };
}

#endif
