#include "renderable.hh"

Renderable::Renderable(unsigned int renderX, unsigned int renderY, const std::string& textureName):
    textureName_{textureName}, texture_{nullptr} {

    rect_.x = renderX;
    rect_.y = renderY;
}

Renderable::~Renderable() {
}

void Renderable::setTexture(std::shared_ptr<SDL_Texture> texture, unsigned int width, unsigned int height) {
    texture_ = texture;
    rect_.w = width;
    rect_.h = height;
}

void Renderable::setRenderPos(unsigned int renderX, unsigned int renderY) {
    rect_.x = renderX;
    rect_.y = renderY;
}

const std::shared_ptr<SDL_Texture>& Renderable::texture() const {
    return texture_;
}

