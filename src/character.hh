#ifndef CHARACTER_HH
#define CHARACTER_HH

#include "renderable.hh"
#include <vector>
#include "SDL_rect.h"
#include "types.hh"

namespace Character {
    static const unsigned int CHARACTER_WIDTH{32};
    static const unsigned int CHARACTER_HEIGHT{32};

    extern const std::vector<SDL_Rect*> CHARACTER_CLIPS;

    enum Direction {
        Up = 0,
        Down,
        Left,
        Right
    };

    class Character : public Renderable {
    public:
        Character(unsigned int x, unsigned int y, const std::string& type);
        virtual ~Character();

        virtual void moveTo(unsigned int x, unsigned int y);
        void facePosition(unsigned int x, unsigned int y);

        unsigned int x() const { return x_; }
        unsigned int y() const { return y_; }
        virtual unsigned int width() const { return CHARACTER_WIDTH; }
        virtual unsigned int height() const { return CHARACTER_HEIGHT; }

        Direction direction() const;
        Level::Position facingPosition() const;

    private:
        void updateDirection(int dirX, int dirY); // valid values: other zero, other -1 or 1
        void updateSprite();

        unsigned int x_;
        unsigned int y_;
        int dirX_;
        int dirY_;
    };
}

#endif
