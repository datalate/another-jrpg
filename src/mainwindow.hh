#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <memory>
#include <string>
#include "SDL_video.h"
#include "SDL_render.h"
#include "texturemanager.hh"

namespace Window {
    class MainWindow {
        public:
            MainWindow();

            bool create(signed int width, signed int height, std::string title);
            void clear() const;
            void update() const;
    
        private:
            std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_; // has ownership
            std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_; // has ownership
            //TextureManager textures_;
    };
}

#endif
