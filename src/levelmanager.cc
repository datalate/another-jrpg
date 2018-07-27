#include "levelmanager.hh"
#include <filesystem>
#include <iostream>
#include <vector>
#include <yaml-cpp/yaml.h>
#include "yamlparser.hh"
#include "npc.hh"

namespace fs = std::filesystem;
using Character::Npc;

namespace Level {
    LevelManager::LevelManager() {
        /*std::shared_ptr<Map> testMap(new Map("testMap"));
        testMap->load();
        maps_.insert({"test", testMap});
        writeMap("test");*/

        tileConf_.loadTileConfig("cfg/tiles.yml");
    }

    void LevelManager::loadFolder(const std::string& dir) {
        for (const auto& it: fs::directory_iterator(dir)) {
            if (it.is_directory()) {
                continue;
            }

            std::shared_ptr<Map> map(loadFile(it.path().string()));
            if (map != nullptr) {
                maps_.insert({it.path().stem().string(), map}); // stem is filename without ext
            }
        }

        //writeMap("level0");
    }

    bool LevelManager::exists(const std::string& map) const {
        return maps_.find(map) != maps_.end();
    }

    std::shared_ptr<Map> LevelManager::operator[](const std::string& map) {
        return maps_[map];
    }

    // This probably needs to get splitted to multiple methods later on
    std::shared_ptr<Map> LevelManager::loadFile(const std::string& file) { 
        bool ok{true};
        std::string errorMsg;
        std::shared_ptr<Map> map{nullptr};

        std::cout << "Loading level: " << file << "... ";

        YAML::Node node;
        if (!YamlParser::loadFile(file, node)) {
            errorMsg = "Failed to open/parse file";
            ok = false;
        }
        else {
            std::string name;
            unsigned int width{0};
            unsigned int height{0};
            std::vector<unsigned int> tileData;

            YamlParser::parse<std::string>(node["name"], name);
            YamlParser::parse<unsigned int>(node["width"], width);
            YamlParser::parse<unsigned int>(node["height"], height);
            YamlParser::parse<std::vector<unsigned int>>(node["tiles"], tileData);

            if (name.empty() || width == 0 || height == 0 || tileData.empty()) {
                errorMsg = "Key attributes missing";
                ok = false;
            }
            else if (tileData.size() != width * height) {
                errorMsg = "Incorrect number of tiles";
                ok = false;
            }
            else {
                std::vector<std::shared_ptr<Tile>> tiles;
                unsigned int x{0};
                unsigned int y{0};

                for (const auto& tile : tileData) {
                    const TileInfo& info = tileConf_[tile];
                    tiles.push_back(std::make_shared<Tile>(x, y, info.texture, info.solid));
                    ++x;

                    if (x == width) {
                        x -= width;
                        ++y;
                    }
                }

                map = std::make_shared<Map>(name);
                map->setTiles(width, height, tiles);

                // Rest of the data is optional

                if (node["portals"]) {
                    YAML::Node portalsNode = node["portals"];
                    for (YAML::const_iterator it = portalsNode.begin(); it != portalsNode.end(); ++it) {
                        Portal newPortal;
                        if (YamlParser::parse<Portal>(*it, newPortal)) {
                            map->addPortal(newPortal);
                        }
                    }
                }

                if (node["spawnPoint"]) {
                    Position spawnPoint;
                    if (YamlParser::parse<Position>(node["spawnPoint"], spawnPoint)) {
                        map->setPlayerSpawn(spawnPoint);
                    }
                }

                if (node["npcs"]) {
                    std::vector<std::shared_ptr<Npc>> npcs;
                    YAML::Node npcsNode = node["npcs"];

                    for (YAML::const_iterator it = npcsNode.begin(); it != npcsNode.end(); ++it) {
                        // TODO: change to npc type later on
                        Position npcPos;
                        if (YamlParser::parse<Position>(*it, npcPos)) {
                            npcs.push_back(std::make_shared<Npc>(npcPos.x, npcPos.y));
                        }
                    }

                    map->setNpcs(npcs);
                }
            }
        }

        if (!ok) {
            std::cout << "ERROR" << std::endl << errorMsg << std::endl;
        }
        else {
            std::cout << "OK" << std::endl;
        }

        return map; // nullptr if bad
    }

    // Dumps level as YAML-format to stdout
    void LevelManager::writeMap(const std::string& map) {
        const auto it = maps_.find(map);
        if (it != maps_.end()) {
            YAML::Emitter out;
            
            out << YAML::BeginMap;
            out << YAML::Key << "name";
            out << YAML::Value << it->second->name();
            out << YAML::Key << "width";
            out << YAML::Value << it->second->width();
            out << YAML::Key << "height";
            out << YAML::Value << it->second->height();
            out << YAML::Key << "tiles";
            out << YAML::Value << YAML::Flow << YAML::BeginSeq;
            
            for (const auto& tile: it->second->tiles()) {
                out << tile->textureName();
            }

            out << YAML::EndSeq << YAML::EndMap;

            std::cout << out.c_str() << std::endl;
        }
    }
}

