#include "renderable.hh"

using Window::Texture;

Renderable::Renderable(unsigned int renderX, unsigned int renderY, const std::string& textureName):
    textureName_{textureName}, texture_{nullptr}, clip_{nullptr} {

    rect_.x = renderX;
    rect_.y = renderY;
    rect_.w = 0;
    rect_.h = 0;
}

Renderable::~Renderable() {
}

void Renderable::setTexture(std::shared_ptr<Texture> texture) {
    texture_ = texture;

    if (width() == 0 || height() == 0) {
        rect_.w = texture->textureWidth();
        rect_.h = texture->textureHeight();
    }
    else {
        rect_.w = width();
        rect_.h = height();
    }
}

void Renderable::setRenderPos(unsigned int renderX, unsigned int renderY) {
    rect_.x = renderX;
    rect_.y = renderY;
}

void Renderable::setTextureClip(SDL_Rect* clip) {
    clip_ = clip;
}

const std::shared_ptr<Texture>& Renderable::texture() const {
    return texture_;
}

