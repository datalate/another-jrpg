#include "levelmanager.hh"
#include <filesystem>
#include <iostream>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace fs = std::filesystem;

namespace Level {
    LevelManager::LevelManager() {
        /*std::shared_ptr<Map> testMap(new Map("testMap"));
        testMap->load();
        maps_.insert({"test", testMap});
        writeMap("test");*/
    }

    void LevelManager::loadFolder(const std::string& dir) {
        for (auto& it: fs::directory_iterator(dir)) {
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

    std::shared_ptr<Map> LevelManager::loadFile(const std::string& file) { 
        bool ok{true};
        YAML::Node node;

        try {
            node = YAML::LoadFile(file);
        } catch (const YAML::Exception &e) {
            std::cout << "Failed to parse level '" << file << "': " << e.what() << std::endl;
            ok = false;
        }
        
        if (!ok) return std::shared_ptr<Map>(nullptr);

        std::string name;
        unsigned int width;
        unsigned int height;
        std::vector<std::string> tileData;
       
        try {
            name = node["name"].as<std::string>();
            width = node["width"].as<int>();
            height = node["height"].as<int>();
            tileData = node["tiles"].as<std::vector<std::string>>();
        } catch (const YAML::RepresentationException &e) {
            std::cout << "Key attributes missing in level '" << file << "': " << e.what() << std::endl;
            ok = false;
        }

        if (!ok) return std::shared_ptr<Map>(nullptr);
        
        if (tileData.size() != width * height) {
            std::cout << "Incorrect number of tiles in level '" << file << "'" << std::endl;
            return std::shared_ptr<Map>(nullptr);
        }

        std::vector<std::shared_ptr<Tile>> tiles;
        unsigned int x{0};
        unsigned int y{0};

        for (const auto& tile: tileData) {
            tiles.push_back(std::shared_ptr<Tile>(new Tile(x, y, tile)));
            ++x;

            if (x == width) {
                x -= width;
                ++y;
            }
        }

        std::shared_ptr<Map> map(new Map(name));
        map->setTiles(width, height, tiles);
        
        std::cout << "Loaded level: " << file << std::endl;

        return map;
    }

    // Dumps level as YAML-format to stdout
    void LevelManager::writeMap(const std::string& map) {
        auto it = maps_.find(map);
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


        /*std::vector<std::shared_ptr<Tile>> tiles;
        std::ifstream ifs(file, std::ifstream::in);

        if (ifs.is_open()) {
            std::istringstream ss;
            std::string line;
            std::string col;
            std::vector<std::string> cols;

            int lineNo{0};

            while (ifs) {
                std::getline(ifs, line);
                lineNo++;

                if (line.empty()) {
                    continue;
                }

                // Reset for new line
                ss.str(line);
                ss.clear();
                cols.clear();

                while (std::getline(ss, col, ';')) {
                    cols.push_back(col);
                }

                if (cols.size() < 4) {
                    std::cout << "Bad level format in level '" << path << "', row " << lineNo << std::endl;
                    continue;
                }

                // Parse item type
                if (cols[0] == "tile") {
                    // FORMAT: tile;tileId;x;y
                    // TODO: should we include tileId checking?
                    std::string& tileId{cols[1]};
                    int x{std::stoi(cols[2])}; // TODO: exception handling for std::stoi
                    int y{std::stoi(cols[3])};

                    tiles.push_back(std::shared_ptr<Tile>(new Tile(x, y, tileId)));
                } // No other types atm
                else {
                    std::cout << "Incorrect item type in level'" << path << "', row " << lineNo << std::endl;
                }
            }
        }
        else {
            std::cout << "Failed to open level '" << path <<  "' for reading" << std::endl;
        }*/
