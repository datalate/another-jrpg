#include "texturemanager.hh"

//using Level::Tile;

TextureManager::TextureManager()
{ }

/*std::shared_ptr<SDL_Texture> TextureManager::textureOf(const Tile& tile, std::shared_ptr<SDL_Renderer>& renderer) {
    
}*/

std::shared_ptr<SDL_Texture> TextureManager::placeholder(int width, int height,
                                                         std::shared_ptr<SDL_Renderer>& renderer) const {
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{SDL_CreateRGBSurface(0, width, height, 32,
                                                             0, 0, 0, 0), SDL_FreeSurface};
    SDL_FillRect(surface.get(), NULL, 0xffff0000); // red

    std::shared_ptr<SDL_Texture> texture{SDL_CreateTextureFromSurface(renderer.get(), surface.get()),
                                         SDL_DestroyTexture};

    return texture;
}
