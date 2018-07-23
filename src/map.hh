#ifndef MAP_HH
#define MAP_HH

#include <memory>
#include <vector>
#include <string>
#include "tile.hh"

namespace Level {
    struct Portal {
        unsigned int sourceX;
        unsigned int sourceY;
        unsigned int destX;
        unsigned int destY;
        std::string destMap;
    };

    class Map {
        public:
            Map(const std::string& name);
            void load();

            std::string name() const { return name_; }
            unsigned int width() const { return width_; }
            unsigned int height() const { return height_; }
            bool canMove(unsigned int x, unsigned int y) const;
            bool good() const;

            void setTiles(unsigned int width, unsigned int height, std::vector<std::shared_ptr<Tile>> tiles);
            const std::shared_ptr<Tile>& tileAt(unsigned int x, unsigned int y) const;
            const std::vector<std::shared_ptr<Tile>>& tiles() const;
            std::vector<std::shared_ptr<Tile>>& tiles();

            // TODO: should we make a generic object class and inherit portal from it?
            // A new method could be created: objectAt which would return ptr to the object.
            // We could also restrict number of objects per tile to one.
            std::shared_ptr<Portal> portalAt(unsigned int x, unsigned int y);
            void addPortal(const Portal& portal);

        private:
            void dump() const;

            std::vector<std::shared_ptr<Tile>> tiles_; // has ownership
            std::vector<std::shared_ptr<Portal>> portals_; // has ownership

            std::string name_;
            unsigned int width_;
            unsigned int height_;
    };
}

#endif
