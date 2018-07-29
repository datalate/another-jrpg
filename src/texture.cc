#include "texture.hh"
#include <iostream>

namespace Window {
    Texture::Texture(texturePtr texture):
        texture_{std::move(texture)}, width_{0}, height_{0} {

        // Get dimensions
        SDL_QueryTexture(get(), NULL, NULL, &width_, &height_);
    }

    Texture::~Texture() {
        //std::cout << "Deleted texture" << std::endl;
    }

    /*Texture& Texture::operator=(texturePtr texture) {
        texture_ = std::move(texture);
        return *this;
    }*/
}