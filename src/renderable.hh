#ifndef RENDERABLE_HH
#define RENDERABLE_HH

#include <memory>
#include <string>
#include "SDL_render.h"

class Renderable {
    public:
        explicit Renderable(int x, int y, std::string textureName);
        virtual ~Renderable();

        void setTexture(std::shared_ptr<SDL_Texture> texture, int width, int height);
        void setPos(int x, int y);

        const std::string& textureName() const { return textureName_; }
        const std::shared_ptr<SDL_Texture>& texture() const;
        const SDL_Rect& rect() const { return rect_; }

    private:
        std::string textureName_;
        std::shared_ptr<SDL_Texture> texture_;
        SDL_Rect rect_;
};

#endif
