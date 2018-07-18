#include "mainwindow.hh"

namespace Window {
    MainWindow::MainWindow():
        window_{nullptr, SDL_DestroyWindow},
        renderer_{nullptr, SDL_DestroyRenderer}
    { }

    bool MainWindow::create(signed int width, signed int height, std::string title) {
        bool success{true};

        renderer_ = nullptr;
        window_.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       width, height, SDL_WINDOW_SHOWN));
        
        if (window_.get() == nullptr) {
            success = false;
        }
        else {
            renderer_.reset(SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED),
                            SDL_DestroyRenderer);

            if (renderer_.get() == nullptr) {
                success = false;
            }
            else {
                clear();
                update();
            }
        }

        return success;
    }

    void MainWindow::clear() const {
        if (renderer_.get() != nullptr) {
            SDL_RenderClear(renderer_.get());
        }
    }

    void MainWindow::update() const {
        if (renderer_.get() != nullptr) {
            SDL_RenderPresent(renderer_.get());
        }
    }

    void MainWindow::render() const {
        if (renderer_.get() != nullptr) {
            for (auto it = renderables_.cbegin(); it != renderables_.cend(); ++it) {
                SDL_RenderCopy(renderer_.get(), (*it)->texture().get(), NULL, &(*it)->rect());
            }
        }
    }

    void MainWindow::addRenderable(const std::shared_ptr<Renderable>& renderable) {
        renderable->setTexture(textures_.placeholder(48, 48, renderer_), 48, 48);
        renderables_.push_back(renderable);

        // TODO: texture handling using texture manager
    }

    void MainWindow::clearRenderables() {
        renderables_.clear();
    }
}

