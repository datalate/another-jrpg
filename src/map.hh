#ifndef MAP_HH
#define MAP_HH

#include <memory>
#include <vector>
#include "tile.hh"

namespace Level {
    class Map {
        public:
            Map();

            // TODO: load from file
            void load();

            int width() const { return width_; }
            int height() const { return height_; }
            bool canMove(int x, int y) const;

            const std::shared_ptr<Tile>& tileAt(int x, int y) const;
            const std::vector<std::shared_ptr<Tile>>& tileSet() const;
            std::vector<std::shared_ptr<Tile>>& tileSet();

        private:
            std::vector<std::shared_ptr<Tile>> tileSet_; // has ownership
            void dump() const;

            int width_;
            int height_;
    };
}

#endif

