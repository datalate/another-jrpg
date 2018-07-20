#include "renderable.hh"

Renderable::Renderable(int renderX, int renderY, std::string textureName):
    textureName_{textureName}, texture_{nullptr} {

    rect_.x = renderX;
    rect_.y = renderY;
}

Renderable::~Renderable() { }

void Renderable::setTexture(std::shared_ptr<SDL_Texture> texture, int width, int height) {
    texture_ = texture;
    rect_.w = width;
    rect_.h = height;
}

void Renderable::setRenderPos(int renderX, int renderY) {
    rect_.x = renderX;
    rect_.y = renderY;
}

const std::shared_ptr<SDL_Texture>& Renderable::texture() const {
    return texture_;
}

