#ifndef LEVELMANAGER_HH
#define LEVELMANAGER_HH

#include <string>
#include <unordered_map>
#include <memory>
#include "map.hh"
#include "tilemanager.hh"

namespace Level {
    class LevelManager {
    public:
        LevelManager();

        LevelManager(const LevelManager&) = delete; // disable copy
        void operator=(const LevelManager&) = delete; // disable assign

        void loadFolder(const std::string& dir);
        bool exists(const std::string& map) const;
        std::shared_ptr<Map> operator[](const std::string& map);

    private:
        std::shared_ptr<Map> loadFile(const std::string& file);
        void writeMap(const std::string& map);

        // has ownership, map name as key
        std::unordered_map<std::string, std::shared_ptr<Map>> maps_;

        TileManager tileConf_;
    };
}

#endif
