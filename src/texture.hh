#ifndef TEXTURE_HH
#define TEXTURE_HH

#include <memory>
#include "SDL_render.h"

namespace Window {
    typedef std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texturePtr;

    class Texture {
    public:
        Texture(texturePtr texture); // gets ownership of texture
        ~Texture();
        // Texture& operator=(texturePtr texture); // do we need something like this?

        Texture(const Texture&) = delete; // disable copy
        void operator=(const Texture&) = delete; // disable assign

        SDL_Texture* get() const { return texture_.get(); }

        int textureWidth() const { return width_; }
        int textureHeight() const { return height_; }

    private:
        texturePtr texture_;

        //SDL_Rect clip_; // offsets for texture, TODO
        int width_;
        int height_;
    };
}

#endif