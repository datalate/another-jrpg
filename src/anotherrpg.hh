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
            explicit AnotherRpg(Window::MainWindow& win);

            AnotherRpg(const AnotherRpg&) = delete; // disable copy
            void operator=(const AnotherRpg&) = delete; // disable assign
            
            void run();
        
        private:
            bool switchToMap(const std::string& map);
            void movePlayer(unsigned int x, unsigned int y);

            Window::MainWindow& win_;
            Level::LevelManager lvls_;

            std::shared_ptr<Player> player_; // has ownership
            std::shared_ptr<Level::Map> currentMap_; // no ownership
    };
}

#endif
