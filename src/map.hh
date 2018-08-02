#ifndef MAP_HH
#define MAP_HH

#include <memory>
#include <vector>
#include <string>
#include "tile.hh"
#include "npc.hh"
#include "types.hh"

namespace Level {
    class Map {
    public:
        explicit Map(const std::string& name);

        void load(); // for testing

        const std::string& name() const { return name_; }
        unsigned int width() const { return width_; }
        unsigned int height() const { return height_; }
        bool canMove(unsigned int x, unsigned int y) const; // is a ground tile
        bool good() const; // map has tiles

        void setTiles(unsigned int width, unsigned int height,
                        const std::vector<std::shared_ptr<Tile>> &tiles);
        const std::shared_ptr<Tile>& tileAt(unsigned int x, unsigned int y) const;
        const std::vector<std::shared_ptr<Tile>>& tiles() const { return tiles_; }
        std::vector<std::shared_ptr<Tile>>& tiles() { return tiles_; }

        void setNpcs(const std::vector<std::shared_ptr<Character::Npc>> &npcs);
        const std::vector<std::shared_ptr<Character::Npc>>& npcs() const { return npcs_; }
        std::vector<std::shared_ptr<Character::Npc>>& npcs() { return npcs_; }

        bool hasPlayerSpawn() const;
        void setPlayerSpawn(const Position& Position);
        const Position& playerSpawn() const { return playerSpawn_; }

        std::shared_ptr<Character::Npc> npcAt(unsigned int x, unsigned int y) const;
        // TODO: should we make a generic object class and inherit portal from it?
        // A new method could be created: objectAt which would return ptr to the object.
        // We could also restrict number of objects per tile to one.
        std::shared_ptr<Portal> portalAt(unsigned int x, unsigned int y);
        void addPortal(const Portal& portal);

    private:
        void dump() const;

        std::vector<std::shared_ptr<Tile>> tiles_; // has ownership
        std::vector<std::shared_ptr<Portal>> portals_; // has ownership
        std::vector<std::shared_ptr<Character::Npc>> npcs_; // has ownership

        std::string name_;
        unsigned int width_;
        unsigned int height_;

        Position playerSpawn_;
    };
}

#endif

