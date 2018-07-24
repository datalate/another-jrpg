#ifndef TEXTUREMANAGER_HH
#define TEXTUREMANAGER_HH

#include <unordered_map>
#include <memory>
#include <string>
#include "SDL_render.h"
#include "renderable.hh"

namespace Window {
	class TextureManager {
		public:
			TextureManager();
			~TextureManager();

			TextureManager(const TextureManager&) = delete; // disable copy
			void operator=(const TextureManager&) = delete; // disable assign

			std::shared_ptr<SDL_Texture> textureOf(const Renderable& object,
												   const std::shared_ptr<SDL_Renderer>& rendr);
			std::shared_ptr<SDL_Texture> placeholder(int width, int height,
													 const std::shared_ptr<SDL_Renderer>& rendr) const;

		private:
			std::shared_ptr<SDL_Texture> loadFromFile(const std::string& path,
											          const std::shared_ptr<SDL_Renderer>& rendr) const;

            // has ownership, texture id as key
			std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> textures_;
	};
}

#endif

