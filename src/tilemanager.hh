#ifndef TILEMANAGER_HH
#define TILEMANAGER_HH

#include <string>
#include <unordered_map>
#include "yamlparser.hh"
#include "types.hh"

namespace Level {
    class TileManager {
    public:
        TileManager();

        TileManager(const TileManager&) = delete; // disable copy
        void operator=(const TileManager&) = delete; // disable assign

        bool loadTileConfig(const std::string& path);
        const TileInfo& operator[](unsigned int id) const;
        const std::unordered_map<unsigned int, TileInfo> tileTypes() const;

    private:
        // has ownership, tile id as key 
        std::unordered_map<unsigned int, TileInfo> tileConfig_;
    };
}

#endif
