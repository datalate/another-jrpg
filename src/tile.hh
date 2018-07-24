#ifndef TILE_HH
#define TILE_HH

#include <string>
#include "renderable.hh"

namespace Level {
    static const unsigned int TILE_WIDTH{32};
    static const unsigned int TILE_HEIGHT{32};

    class Tile : public Renderable {
        public:
            Tile(unsigned int x, unsigned int y, const std::string& typeID);
            ~Tile();

            unsigned int x() const { return x_; }
            unsigned int y() const { return y_; }
            const std::string& typeId() const { return typeId_; }

        private:
            unsigned int x_;
            unsigned int y_;
            std::string typeId_;
    };
}

#endif

