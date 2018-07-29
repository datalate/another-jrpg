#ifndef RENDERABLE_HH
#define RENDERABLE_HH

#include <memory>
#include <string>
#include "SDL_rect.h"
#include "texture.hh"

class Renderable {
public:
    Renderable(unsigned int renderX, unsigned int renderY, const std::string& textureName);
    virtual ~Renderable();

    void setTexture(std::shared_ptr<Window::Texture> texture);

    virtual unsigned int width() const = 0;
    virtual unsigned int height() const = 0;

    const std::string& textureName() const { return textureName_; }
    const std::shared_ptr<Window::Texture>& texture() const;
    const SDL_Rect& rect() const { return rect_; }
    SDL_Rect* clip() const { return clip_; } // can be nullptr

protected:
    void setRenderPos(unsigned int renderX, unsigned int renderY);
    void setTextureClip(SDL_Rect* clip);

private:
    std::string textureName_;
    std::shared_ptr<Window::Texture> texture_; // no ownership
    SDL_Rect rect_; // render dimensions
    SDL_Rect* clip_; // drawing offset
};

#endif
