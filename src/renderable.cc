#include "renderable.hh"

using Window::Texture;

Renderable::Renderable(unsigned int renderX, unsigned int renderY, const std::string& textureName):
    textureName_{textureName}, texture_{nullptr} {

    rect_.x = renderX;
    rect_.y = renderY;
}

Renderable::~Renderable() {
}

void Renderable::setTexture(std::shared_ptr<Texture> texture) {
    texture_ = texture;
    rect_.w = texture->textureWidth();
    rect_.h = texture->textureHeight();
}

void Renderable::setRenderPos(unsigned int renderX, unsigned int renderY) {
    rect_.x = renderX;
    rect_.y = renderY;
}

const std::shared_ptr<Texture>& Renderable::texture() const {
    return texture_;
}

