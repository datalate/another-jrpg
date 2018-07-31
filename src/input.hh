#ifndef INPUT_HH
#define INPUT_HH

#include <SDL.h>
#include <unordered_map>
#include <vector>

namespace Game {
    //TODO: what about handling mouse and mouse keys?

    enum Key {
        MoveUp = 0,
        MoveDown,
        MoveLeft,
        MoveRight,
        Interact
    };

    class Input {
    public:
        Input();

        void update(SDL_Event& event);

        const Key& keyPressed() const; // returns the "newest" key pressed
        bool isKeyPressed() const;
        bool isMovement() const;

    private:
        std::unordered_map<SDL_Keycode, Key> keys_;
        std::vector<Key> pressed_;
    };
}

#endif