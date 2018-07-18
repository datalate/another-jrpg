#include "tile.hh"
#include <iostream>

namespace Level {
    Tile::Tile(int x, int y, std::string typeId): x_{x}, y_{y}, typeId_{typeId} {
        std::cout << "Tile created at: (" << x_ << ", " << y_ << ")" << std::endl;
    }

    Tile::~Tile() {
        std::cout << "Tile destroyed at: (" << x_ << ", " << y_ << ")" << std::endl;
    }
}

