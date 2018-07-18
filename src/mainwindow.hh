#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <memory>
#include <string>
#include <vector>
#include "SDL_video.h"
#include "SDL_render.h"
#include "texturemanager.hh"
#include "renderable.hh"

namespace Window {
    class MainWindow {
        public:
            MainWindow();

            bool create(signed int width, signed int height, std::string title);
            void clear() const;
            void update() const;
            void render() const;

            void addRenderable(const std::shared_ptr<Renderable>& renderable);
            void clearRenderables();
    
        private:
            std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_; // has ownership
            std::shared_ptr<SDL_Renderer> renderer_; // has ownership

            TextureManager textures_;
            std::vector<std::shared_ptr<Renderable>> renderables_;
    };
}

#endif
