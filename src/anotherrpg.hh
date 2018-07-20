#ifndef ANOTHER_RPG_HH
#define ANOTHER_RPG_HH

#include <memory>
#include "mainwindow.hh"
#include "map.hh"
#include "player.hh"

namespace Game {
    class AnotherRpg {
        public:
            AnotherRpg(Window::MainWindow& win);
            
            void run();
        
        private:
            Window::MainWindow& win_;
            Level::Map map_;
            std::shared_ptr<Player> player_;

            void initMap();
    };
}

#endif
