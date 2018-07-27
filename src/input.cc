#include "input.hh"
#include <iostream>

namespace Game {
    Input::Input() {
        // Config for keys
        keys_.insert({SDLK_w, MoveUp});
        keys_.insert({SDLK_s, MoveDown});
        keys_.insert({SDLK_a, MoveLeft});
        keys_.insert({SDLK_d, MoveRight});
    }

    void Input::update(SDL_Event& event) {
        const Uint32& eventType{event.type};
        
        if ((eventType == SDL_KEYDOWN || eventType == SDL_KEYUP) && event.key.repeat == 0) {
            const SDL_Keycode& keyCode{event.key.keysym.sym};

            auto key{keys_.find(keyCode)};
            if (key != keys_.end()) {
                if (eventType == SDL_KEYUP) {
                    // Remove key
                    for (auto it{pressed_.begin()}; it != pressed_.end(); ++it) {
                        if (*it == key->second) {
                            pressed_.erase(it);
                            break;
                        }
                    }
                }
                else {
                    // Add key
                    pressed_.push_back(key->second);
                }
            }
        }
    }

    const Key& Input::keyPressed() const {
        return pressed_.back();
    }

    bool Input::isKeyPressed() const {
        return !pressed_.empty();
    }
}