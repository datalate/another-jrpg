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

    void MainWindow::render() const {
        if (renderer_ != nullptr) {
            for (auto it = renderables_.cbegin(); it != renderables_.cend(); ++it) {
                SDL_RenderCopy(renderer_.get(), (*it)->texture().get(), NULL, &(*it)->rect());
            }
        }
    }

    void MainWindow::addRenderable(const std::shared_ptr<Renderable>& renderable) {
		std::shared_ptr<SDL_Texture> texture = textures_.textureOf(*renderable.get(), renderer_);
		int w{0};
		int h{0};
		SDL_QueryTexture(texture.get(), NULL, NULL, &w, &h);

        renderable->setTexture(texture, w, h);
        renderables_.push_back(renderable);
    }

    void MainWindow::clearRenderables() {
        renderables_.clear();
    }
}

