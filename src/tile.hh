#ifndef TILE_HH
#define TILE_HH

#include <string>

namespace Level {
    class Tile {
        public:
            Tile(int x, int y, std::string typeID);
            ~Tile();

            int x() const { return x_; }
            int y() const { return y_; }
            std::string typeId() const { return typeId_; }

        private:
            int x_;
            int y_;
            std::string typeId_;
    };
}

#endif

