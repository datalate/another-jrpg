#include "tile.hh"
#include <iostream>

namespace Level {
    Tile::Tile(unsigned int x, unsigned int y, const std::string& textureName, bool solid):
        Renderable{x * TILE_WIDTH, y * TILE_HEIGHT, textureName}, x_{x}, y_{y}, solid_{solid} {

        //std::cout << "Tile created at: (" << x_ << ", " << y_ << "): " << typeId_ << std::endl;
    }

    Tile::~Tile() {
        //std::cout << "Tile destroyed at: (" << x_ << ", " << y_ << ")" << std::endl;
    }
}

