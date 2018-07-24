#ifndef RENDERABLE_HH
#define RENDERABLE_HH

#include <memory>
#include <string>
#include "SDL_render.h"

class Renderable {
    public:
        Renderable(unsigned int renderX, unsigned int renderY, const std::string& textureName);
        virtual ~Renderable();

        void setTexture(std::shared_ptr<SDL_Texture> texture, unsigned int width, unsigned int height);

        const std::string& textureName() const { return textureName_; }
        const std::shared_ptr<SDL_Texture>& texture() const;
        const SDL_Rect& rect() const { return rect_; }

    protected:
        void setRenderPos(unsigned int renderX, unsigned int renderY);

    private:
        std::string textureName_;
        std::shared_ptr<SDL_Texture> texture_; // no ownership
        SDL_Rect rect_; // render dimensions
};

#endif
