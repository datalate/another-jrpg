#include "map.hh"
#include <iostream>

using Character::Npc;

namespace Level {
    Map::Map(const std::string& name):
        name_{name}, width_{0}, height_{0}, playerSpawn_{0, 0}
    { }

    // placeholder
    void Map::load() {
        static unsigned int w{25};
        static unsigned int h{20};

        tiles_.clear();
        portals_.clear();

        for (unsigned int y{0}; y < h; ++y) {
            for (unsigned int x{0}; x < w; ++x) {
				if (x == 0 || y == 0 || x == w - 1 || y == h - 1) {
                    tiles_.push_back(std::make_shared<Tile>(x, y, "wall", true));
				}
				else {
                    tiles_.push_back(std::make_shared<Tile>(x, y, "ground", false));
				}
            }
        }

        width_ = w;
        height_ = h;

        dump();
    }

    bool Map::canMove(unsigned int x, unsigned int y) const {
        bool tileOk{x < width() && y < height() && !tileAt(x, y)->solid()};
        return tileOk && npcAt(x, y) == nullptr;
    }

    bool Map::good() const {
        return (width() > 0 && height() > 0 && !tiles_.empty());
    }

    void Map::dump() const {
        std::cout << "Level tile dump:" << std::endl;
        for (unsigned int y{0}; y < height(); ++y) {
            for (unsigned int x{0}; x < width(); ++x) {
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

    void Map::setTiles(unsigned int width, unsigned int height,
                       const std::vector<std::shared_ptr<Tile>>& tiles) {
        width_ = width;
        height_ = height;
        tiles_ = tiles; // perform copy
    }

    const std::shared_ptr<Tile>& Map::tileAt(unsigned int x, unsigned int y) const {
        return tiles_.at(y * width() + x);
    }

    void Map::setNpcs(const std::vector<std::shared_ptr<Npc>>& npcs) {
        npcs_ = npcs;
    }

    bool Map::hasPlayerSpawn() const {
        return (playerSpawn_.x != 0 && playerSpawn_.y != 0);
    }

    void Map::setPlayerSpawn(const Position& Position) {
        playerSpawn_ = Position;
    }

    std::shared_ptr<Portal> Map::portalAt(unsigned int x, unsigned int y) {
        for (auto& portal: portals_) {
            if (portal->sourceX == x && portal->sourceY == y) {
                return portal;
            }
        }

        return nullptr; // nothing found
    }

    std::shared_ptr<Npc> Map::npcAt(unsigned int x, unsigned int y) const {
        for (auto& npc: npcs_) {
            if (npc->x() == x && npc->y() == y) {
                return npc;
            }
        }

        return nullptr; // nothing found
    }


    void Map::addPortal(const Portal& portal) {
        portals_.push_back(std::make_shared<Portal>(portal));
    }
}

