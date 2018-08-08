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

		MainWindow(const MainWindow&) = delete; // disable copy
		void operator=(const MainWindow&) = delete; // disable assign

        bool create(unsigned int width, unsigned int height, const std::string& title);

        void clear() const;
        void update() const;
        void render(std::vector<std::shared_ptr<Renderable>>& renderables);

    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;
        std::shared_ptr<SDL_Renderer> renderer_; // has ownership

        TextureManager textures_;
    };
}

#endif
