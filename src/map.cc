#include "map.hh"

namespace Level {
    Map::Map(): width_{-1}, height_{-1} { }

    // placeholder
    void Map::load() {
        static int w{25};
        static int h{20};

        for (int x{0}; x < w; ++x) {
            for (int y{0}; y < h; ++y) {
				std::shared_ptr<Tile> newTile;
				if (x == 0 || y == 0 || x == w - 1 || y == h - 1) {
					newTile.reset(new Tile(x, y, "wall"));
				}
				else {
					newTile.reset(new Tile(x, y, "ground"));
				}
                tileSet_.push_back(newTile);
            }
        }

        width_ = w;
        height_ = h;
    }

    const std::shared_ptr<Tile>& Map::tileAt(int x, int y) const {
        return tileSet_.at(y * width() + x);
    }

    const std::vector<std::shared_ptr<Tile>>& Map::tileSet() const {
        return tileSet_;
    }
}

