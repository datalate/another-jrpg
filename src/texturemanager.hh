#ifndef TEXTURE_MANAGER_HH
#define TEXTURE_MANAGER_HH

#include <map>
#include <memory>
#include "SDL_render.h"
#include "tile.hh"

class TextureManager {
    public:
        TextureManager();

        /*std::shared_ptr<SDL_Texture> textureOf(const Level::Tile& tile,
                                               std::shared_ptr<SDL_Renderer>& renderer);*/
        std::shared_ptr<SDL_Texture> placeholder(int width, int height, std::shared_ptr<SDL_Renderer>& renderer);

    private:
        std::map<std::string, std::shared_ptr<SDL_Texture>> tileTextures_; // has ownership
        // TODO: load from file
};

#endif

