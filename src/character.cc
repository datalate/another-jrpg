#include "character.hh"
#include <iostream>

namespace Character {
	Character::Character(unsigned int x, unsigned int y, const std::string& type):
        Renderable{x * CHARACTER_WIDTH, y * CHARACTER_HEIGHT, type},
        x_{x}, y_{y}, dirX_{0}, dirY_{1}
    { }

    Character::~Character() {
    }

    void Character::moveTo(unsigned int x, unsigned int y) {
        dirX_ = x - x_;
        dirY_ = y - y_;

        x_ = x;
        y_ = y;

        setRenderPos(x * CHARACTER_WIDTH, y * CHARACTER_HEIGHT);
    }
}
