#include "texturemanager.hh"

using Level::Tile;

TextureManager::TextureManager():
{ }

/*std::shared_ptr<SDL_Texture> TextureManager::textureOf(const Tile& tile, std::shared_ptr<SDL_Renderer>& renderer) {
    
}*/

std::shared_ptr<SDL_Texture> TextureManager::placeholder(int width, int height, std::shared_ptr<SDL_Renderer>& renderer) {	
	// copied from libsdl wiki...
	Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	   on the endianness (byte order) of the machine */
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    	rmask = 0xff000000;
    	gmask = 0x00ff0000;
    	bmask = 0x0000ff00;
    	amask = 0x000000ff;
	#else
    	rmask = 0x000000ff;
    	gmask = 0x0000ff00;
    	bmask = 0x00ff0000;
    	amask = 0xff000000;
	#endif	
    
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, rmask, gmask, bmask, amask);

	auto texture{SDL_CreateTextureFromSurface(renderer, surface), SDL_DestroySurface};

    SDL_FreeSurface(surface);

    return texture;
}
