#include "tilemanager.hh"
#include <iostream>
#include <yaml-cpp/yaml.h>

namespace YAML {
    using Level::TileInfo;

    // Conversions for TileInfo between internal and external (tile config) format
	template<>
    struct convert<TileInfo> {
		static Node encode(const TileInfo& rhs) {
			Node node;

            node["id"] = rhs.id;
            node["solid"] = rhs.solid;
            node["texture"] = rhs.texture;

			return node;
		}

        static bool decode(const Node& node, TileInfo& rhs) {
            if (!node.IsMap() || node.size() != 3) {
                return false;
            }

            rhs.id = node["id"].as<unsigned int>();
            rhs.solid = node["solid"].as<bool>();
            rhs.texture = node["texture"].as<std::string>();

            return true;
        }
    };
}
namespace Level {
    TileManager::TileManager() { }

    void TileManager::loadTileConfig(const std::string& path) {
        YAML::Node node;
        bool ok{true};

        try {
            node = YAML::LoadFile(path);
        } catch (const YAML::Exception &e) {
            std::cout << "Failed to parse tile config '" << path << "': " << e.what() << std::endl;
        }

        if (ok) {
            for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
                TileInfo newInfo = it->as<TileInfo>();
                tileConfig_.insert({newInfo.id, newInfo});
            }
        }
    }

    const TileInfo& TileManager::operator[](unsigned int id) const {
        return tileConfig_.at(id);
    }
}
