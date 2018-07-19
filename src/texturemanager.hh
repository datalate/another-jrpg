#ifndef TEXTURE_MANAGER_HH
#define TEXTURE_MANAGER_HH

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
												   std::shared_ptr<SDL_Renderer>& rendr);
			std::shared_ptr<SDL_Texture> placeholder(int width, int height,
													 std::shared_ptr<SDL_Renderer>& rendr) const;

		private:
			// has ownership, textureID as key
			std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> textures_;
			
			std::shared_ptr<SDL_Texture> loadFromFile(const std::string& file,
											          std::shared_ptr<SDL_Renderer>& rendr) const;
	};
}

#endif

