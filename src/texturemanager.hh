#ifndef TEXTUREMANAGER_HH
#define TEXTUREMANAGER_HH

#include <unordered_map>
#include <memory>
#include <string>
#include "SDL_render.h"
#include "renderable.hh"
#include "texture.hh"

namespace Window {
	class TextureManager {
	public:
		TextureManager();
		~TextureManager();

		TextureManager(const TextureManager&) = delete; // disable copy
		void operator=(const TextureManager&) = delete; // disable assign

		std::shared_ptr<Texture> textureOf(const Renderable& object,
				                           const std::shared_ptr<SDL_Renderer>& rendr);

	private:
		texturePtr loadFromFile(const std::string& path,
		                        const std::shared_ptr<SDL_Renderer>& rendr) const;
        texturePtr placeholder(unsigned int width, unsigned int height,
                               const std::shared_ptr<SDL_Renderer>& rendr) const;

        // has ownership, texture id as key
		std::unordered_map<std::string, std::shared_ptr<Texture>> textures_;
	};
}

#endif

