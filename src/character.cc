#include "character.hh"
#include <iostream>

namespace Character {
	Character::Character(unsigned int x, unsigned int y, const std::string& type):
        Renderable{x * CHARACTER_WIDTH, y * CHARACTER_HEIGHT, type},
        x_{x}, y_{y}, dirX_{0}, dirY_{1} {

        // TODO: use const static clips for every character?
        for (int i = 0; i < 4; ++i) {
            SDL_Rect *clip = new SDL_Rect();
            clip->x = 0;
            clip->y = i * CHARACTER_HEIGHT;
            clip->w = CHARACTER_WIDTH;
            clip->h = CHARACTER_HEIGHT;
            clips_.push_back(clip);
        }

        updateSprite();
    }

    Character::~Character() {
    }

    void Character::moveTo(unsigned int x, unsigned int y) {
        int oldDirX{dirX_};
        int oldDirY{dirY_};

        dirX_ = x - x_;
        dirY_ = y - y_;

        if (dirX_ != oldDirX || dirY_ != oldDirY) {
            updateSprite();
        }

        x_ = x;
        y_ = y;

        setRenderPos(x * CHARACTER_WIDTH, y * CHARACTER_HEIGHT);
    }

    Direction Character::direction() const {
        if (dirY_ > 0) {
            return Direction::Down;
        }
        else if (dirY_ < 0) {
            return Direction::Up;
        }
        else if (dirX_ < 0) {
            return Direction::Left;
        }
        else {
            return Direction::Right;
        }
    }

    void Character::updateSprite() {
        setTextureClip(clips_.at(direction()));
    }
}
