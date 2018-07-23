#ifndef MAP_HH
#define MAP_HH

#include <memory>
#include <vector>
#include <string>
#include "tile.hh"

namespace Level {
    class Map {
        public:
            Map(const std::string& name);
            void load();

            std::string name() const { return name_; }
            int width() const { return width_; }
            int height() const { return height_; }
            bool canMove(int x, int y) const;
            bool good() const;

            void setTiles(int width, int height, std::vector<std::shared_ptr<Tile>> tiles);
            const std::shared_ptr<Tile>& tileAt(int x, int y) const;
            const std::vector<std::shared_ptr<Tile>>& tiles() const;
            std::vector<std::shared_ptr<Tile>>& tiles();

        private:
            std::vector<std::shared_ptr<Tile>> tiles_; // has ownership
            void dump() const;

            std::string name_;
            int width_;
            int height_;
    };
}

#endif

