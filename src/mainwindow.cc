#include "mainwindow.hh"

namespace Window {
    MainWindow::MainWindow():
        window_{nullptr, SDL_DestroyWindow},
        renderer_{nullptr}
    { }

    bool MainWindow::create(unsigned int width, unsigned int height, const std::string& title) {
        bool success{true};

        renderer_ = nullptr;
        window_.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       width, height, SDL_WINDOW_SHOWN));

        if (window_ == nullptr) {
            success = false;
        }
        else {
            renderer_.reset(SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED),
                            SDL_DestroyRenderer);

            if (renderer_ == nullptr) {
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
        if (renderer_ != nullptr) {
            SDL_RenderClear(renderer_.get());
        }
    }

    void MainWindow::update() const {
        if (renderer_ != nullptr) {
            SDL_RenderPresent(renderer_.get());
        }
    }

    void MainWindow::render(std::vector<std::shared_ptr<Renderable>>& renderables) {
        if (renderer_ != nullptr) {
            for (auto it = renderables.cbegin(); it != renderables.cend(); ++it) {
                if ((*it)->texture() == nullptr) { // add texture if it's not yet loaded
                    (*it)->setTexture(textures_.textureOf(*(*it).get(), renderer_));
                }
                SDL_RenderCopy(renderer_.get(), (*it)->texture()->get(), (*it)->clip(), &(*it)->rect());
            }
        }
    }
}

