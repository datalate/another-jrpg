#ifndef TYPES_HH
#define TYPES_HH

#include <string>

namespace Level {
    struct Position {
        unsigned int x;
        unsigned int y;
    };
    
    struct Portal {
        unsigned int sourceX;
        unsigned int sourceY;
        unsigned int destX;
        unsigned int destY;
        std::string destMap;
    };

    struct TileInfo {
        unsigned int id;
        bool solid;
        std::string texture;
    };
}

#endif
