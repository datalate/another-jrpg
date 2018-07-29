#ifndef TILE_HH
#define TILE_HH

#include <string>
#include "renderable.hh"

namespace Level {
    static const unsigned int TILE_WIDTH{32};
    static const unsigned int TILE_HEIGHT{32};

    class Tile : public Renderable {
    public:
        Tile(unsigned int x, unsigned int y, const std::string& textureName, bool solid);
        ~Tile();

        unsigned int x() const { return x_; }
        unsigned int y() const { return y_; }
        virtual unsigned int width() const { return TILE_WIDTH; }
        virtual unsigned int height() const { return TILE_HEIGHT; }

        bool solid() const { return solid_; }

    private:
        unsigned int x_;
        unsigned int y_;
        bool solid_;
    };
}

#endif

