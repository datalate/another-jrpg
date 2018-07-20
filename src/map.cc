#include "map.hh"
#include <iostream>

namespace Level {
    Map::Map(): width_{-1}, height_{-1} { }

    // placeholder
    void Map::load() {
        static int w{25};
        static int h{20};

        for (int y{0}; y < h; ++y) {
            for (int x{0}; x < w; ++x) {
				if (x == 0 || y == 0 || x == w - 1 || y == h - 1) {
                    tileSet_.push_back(std::shared_ptr<Tile>(new Tile(x, y, "wall")));
				}
				else {
                    tileSet_.push_back(std::shared_ptr<Tile>(new Tile(x, y, "ground")));
				}
            }
        }

        width_ = w;
        height_ = h;

        dump();
    }

    bool Map::canMove(int x, int y) const {
        // TODO
        return tileAt(x, y)->textureName() == "ground";
    }

    void Map::dump() const {
        std::cout << "Level tile dump:" << std::endl;
        for (int y{0}; y < height(); ++y) {
            for (int x{0}; x < width(); ++x) {
                if (canMove(x, y)) {
                    std::cout << "o";
                }
                else {
                    std::cout << "x";
                }
            }
            std::cout << std::endl;
        }
    }

    const std::shared_ptr<Tile>& Map::tileAt(int x, int y) const {
        //std::cout << y*width() + x << std::endl;
        return tileSet_.at(y * width() + x);
    }

    const std::vector<std::shared_ptr<Tile>>& Map::tileSet() const {
        return tileSet_;
    }

    std::vector<std::shared_ptr<Tile>>& Map::tileSet() {
        return tileSet_;
    }
}

