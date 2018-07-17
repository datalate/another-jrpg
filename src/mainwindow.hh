#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <memory>
#include <string>
#include "SDL_video.h"
#include "SDL_render.h"

namespace Window {
    class MainWindow {
        private:
            std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;
            std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_;

        public:
            MainWindow();

            bool create(signed int width, signed int height, std::string title);
            void clear() const;
            void update() const;
    };
}

#endif
