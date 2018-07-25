#include <string>
#include <unordered_map>

namespace Level {
    struct TileInfo {
        unsigned int id;
        bool solid;
        std::string texture;
    };

    class TileManager {
        public:
            TileManager();

            TileManager(const TileManager&) = delete; // disable copy
            void operator=(const TileManager&) = delete; // disable assign

            void loadTileConfig(const std::string& path);
            const TileInfo& operator[](unsigned int id) const;

        private:
            // has ownership, tile id as key 
            std::unordered_map<unsigned int, TileInfo> tileConfig_;
    };
}
