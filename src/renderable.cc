#include "renderable.hh"

Renderable::Renderable(int x, int y, std::string textureName):
    textureName_{textureName}, texture_{nullptr} {

    rect_.x = x;
    rect_.y = y;
}

Renderable::~Renderable() { }

void Renderable::setTexture(std::shared_ptr<SDL_Texture> texture, int width, int height) {
    texture_ = texture;
    rect_.w = width;
    rect_.h = height;
}

void Renderable::setPos(int x, int y) {
    rect_.x = x;
    rect_.y = y;
}

const std::shared_ptr<SDL_Texture>& Renderable::texture() const {
    return texture_;
}

