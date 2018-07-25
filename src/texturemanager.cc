#include "texturemanager.hh"
#include "SDL_image.h"
#include <iostream>

namespace Window {
	TextureManager::TextureManager() {
		// Init png loading
		int imgFlags{IMG_INIT_PNG};
		if (!(IMG_Init(imgFlags) & imgFlags)) {
			std::cout << "IMG_Init() failed: " << IMG_GetError() << std::endl;
		}
	}

	TextureManager::~TextureManager() {
		IMG_Quit();
	}

	texturePtr TextureManager::textureOf(const Renderable& object,
                                         const std::shared_ptr<SDL_Renderer>& rendr) {
		const auto it = textures_.find(object.textureName());
		if (it == textures_.end()) { // doesn't already exist
			texturePtr newTexture = loadFromFile("img/" + object.textureName() + ".png", rendr);
			if (newTexture == nullptr) { // use placeholder texture in case loading fails
				newTexture = placeholder(32, 32, rendr);
			}

			textures_.insert({object.textureName(), newTexture});

			return newTexture;
		}
		else {
			return it->second;
		}
	}

	texturePtr TextureManager::placeholder(unsigned int width, unsigned int height,
										   const std::shared_ptr<SDL_Renderer>& rendr) const {
		std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{SDL_CreateRGBSurface(0, width, height, 32,
																		 0, 0, 0, 0), SDL_FreeSurface};
		SDL_FillRect(surface.get(), NULL, 0xffff0000); // red

		texturePtr texture{SDL_CreateTextureFromSurface(rendr.get(), surface.get()),
                           SDL_DestroyTexture};

		return texture;
	}

	texturePtr TextureManager::loadFromFile(const std::string& path,
		                                    const std::shared_ptr<SDL_Renderer>& rendr) const {
		texturePtr texture;
		std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{IMG_Load(path.c_str()),
                                                                         SDL_FreeSurface};
		if (surface == nullptr) {
			std::cout << "IMG_Load() failed for '" << path << "': " << IMG_GetError() << std::endl;
		}
		else {
			std::cout << "Loaded texture: " << path << std::endl;
			texture.reset(SDL_CreateTextureFromSurface(rendr.get(), surface.get()), SDL_DestroyTexture);
		}
		
		return texture;
	}
}

