#include "tilemanager.hh"
#include <iostream>
#include <yaml-cpp/yaml.h>

namespace Level {
    TileManager::TileManager() {
    }

    bool TileManager::loadTileConfig(const std::string& path) {
        YAML::Node node;
        if (YamlParser::loadFile(path, node)) {
            for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
                TileInfo newInfo;
                if (YamlParser::parse<TileInfo>(*it, newInfo)) {
                    tileConfig_.insert({newInfo.id, newInfo});
                }
            }

            return true;
        }
        else {
            std::cout << "Failed to parse tile config" << std::endl;
            return false;
        }
    }

    const TileInfo& TileManager::operator[](unsigned int id) const {
        return tileConfig_.at(id);
    }

    const std::unordered_map<unsigned int, TileInfo> TileManager::tileTypes() const {
        return tileConfig_;
    }
}
