#include "yamlparser.hh"
#include "map.hh"
#include <iostream>

namespace YAML {
    using Level::Portal;
    using Level::Position;
    using Level::TileInfo;

    // Conversions between internal and external (YAML) formats
    template<>
    struct convert<Portal> {
        static Node encode(const Portal& rhs) {
            Node node;

            node["sourceX"] = rhs.sourceX;
            node["sourceY"] = rhs.sourceY;
            node["destX"] = rhs.destX;
            node["destY"] = rhs.destY;
            node["destMap"] = rhs.destMap;;

            return node;
        }

        static bool decode(const Node& node, Portal& rhs) {
            if (!node.IsMap() || node.size() != 5) {
                return false;
            }

            rhs.sourceX = node["sourceX"].as<unsigned int>();
            rhs.sourceY = node["sourceY"].as<unsigned int>();
            rhs.destX = node["destX"].as<unsigned int>();
            rhs.destY = node["destY"].as<unsigned int>();
            rhs.destMap = node["destMap"].as<std::string>();

            return true;
        }
    };

    template<>
    struct convert<Position> {
        static Node encode(const Position& rhs) {
            Node node;

            node["x"] = rhs.y;
            node["y"] = rhs.x;

            return node;
        }

        static bool decode(const Node& node, Position& rhs) {
            if (!node.IsMap() || node.size() != 2) {
                return false;
            }

            rhs.x = node["x"].as<unsigned int>();
            rhs.y = node["y"].as<unsigned int>();

            return true;
        }
    };

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

YamlParser::YamlParser() {}

YamlParser::~YamlParser() {}

bool YamlParser::loadFile(const std::string& path, YAML::Node& node) const {
    bool success{true};

    try {
        node = YAML::LoadFile(path);
    } catch (const YAML::Exception &e) {
        std::cout << "Failed to parse YML-file '" << path << "': " << e.what() << std::endl;
        success = false;
    }

    return success;
}
