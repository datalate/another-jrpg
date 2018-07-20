#ifndef RENDERABLE_HH
#define RENDERABLE_HH

#include <memory>
#include <string>
#include "SDL_render.h"

class Renderable {
    public:
        explicit Renderable(int renderX, int renderY, std::string textureName);
        virtual ~Renderable();

        void setTexture(std::shared_ptr<SDL_Texture> texture, int width, int height);

        const std::string& textureName() const { return textureName_; }
        const std::shared_ptr<SDL_Texture>& texture() const;
        const SDL_Rect& rect() const { return rect_; }

    protected:
        void setRenderPos(int renderX, int renderY);

    private:
        std::string textureName_;
        std::shared_ptr<SDL_Texture> texture_;
        SDL_Rect rect_;
};

#endif
