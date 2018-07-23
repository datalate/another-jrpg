#ifndef ANOTHER_RPG_HH
#define ANOTHER_RPG_HH

#include <memory>
#include "mainwindow.hh"
#include "map.hh"
#include "player.hh"
#include "levelmanager.hh"

namespace Game {
    class AnotherRpg {
        public:
            AnotherRpg(Window::MainWindow& win);
            
            void run();
        
        private:
            bool switchToMap(const std::string &map);
            void movePlayer(unsigned int x, unsigned int y);

            Window::MainWindow& win_;
            Level::LevelManager lvls_;

            std::shared_ptr<Player> player_;
            std::shared_ptr<Level::Map> currentMap_;
    };
}

#endif
