#include "character.hh"
#include <iostream>
#include <cmath>
#include <cassert>
#include "map.hh"

using Level::Position;

namespace Character {
    const std::vector<SDL_Rect*> CHARACTER_CLIPS{
        new SDL_Rect{0, CHARACTER_HEIGHT * 0, CHARACTER_WIDTH, CHARACTER_HEIGHT},
        new SDL_Rect{0, CHARACTER_HEIGHT * 1, CHARACTER_WIDTH, CHARACTER_HEIGHT},
        new SDL_Rect{0, CHARACTER_HEIGHT * 2, CHARACTER_WIDTH, CHARACTER_HEIGHT},
        new SDL_Rect{0, CHARACTER_HEIGHT * 3, CHARACTER_WIDTH, CHARACTER_HEIGHT}
    };

	Character::Character(unsigned int x, unsigned int y, const std::string& type):
        Renderable{x * CHARACTER_WIDTH, y * CHARACTER_HEIGHT, type},
        x_{x}, y_{y}, dirX_{0}, dirY_{1} {

        // TODO: a loop like this can be used later for animations and such
        /*for (int i = 0; i < 4; ++i) {
            SDL_Rect *clip = new SDL_Rect();
            clip->x = 0;
            clip->y = i * CHARACTER_HEIGHT;
            clip->w = CHARACTER_WIDTH;
            clip->h = CHARACTER_HEIGHT;
            clips_.push_back(clip);
        }*/

        updateSprite();
    }

    Character::~Character() {
    }

    void Character::moveTo(unsigned int x, unsigned int y) {
        const int dx{(int)x - (int)x_};
        const int dy{(int)y - (int)y_};

        if (dx * dy == 0 && (abs(dx) == 1 || abs(dy) == 1)) { // only moved one tile
            updateDirection(dx, dy);
        }

        x_ = x;
        y_ = y;

        setRenderPos(x * CHARACTER_WIDTH, y * CHARACTER_HEIGHT);
    }

    void Character::facePosition(unsigned int x, unsigned int y) {
        const int dx{(int)x - (int)x_};
        const int dy{(int)y - (int)y_};

        int dirX{0};
        int dirY{0};

        if (dx != 0) {
            dirX = dx / abs(dx);
        }
        else if (dy != 0) {
            dirY = dy / abs(dy);
        }

        updateDirection(dirX, dirY);
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

    Position Character::facingPosition() const {
        return {x_ + dirX_, y_ + dirY_};
    }

    void Character::updateDirection(int dirX, int dirY) {
        assert(dirX * dirY == 0 && (abs(dirX) == 1 || abs(dirY) == 1));

        int oldDirX{dirX_};
        int oldDirY{dirY_};

        dirX_ = dirX;
        dirY_ = dirY;

        if (dirX_ != oldDirX || dirY_ != oldDirY) {
            updateSprite();
        }
    }

    void Character::updateSprite() {
        setTextureClip(CHARACTER_CLIPS.at(direction()));
    }
}
