#include "character.hh"
#include <iostream>

namespace Character {
	Character::Character(unsigned int x, unsigned int y, const std::string& type):
		Renderable{x * CHARACTER_WIDTH, y * CHARACTER_HEIGHT, type}, x_{x}, y_{y}
    { }

    Character::~Character() {
    }

    void Character::moveTo(unsigned int x, unsigned int y) {
        x_ = x;
        y_ = y;
        setRenderPos(x * CHARACTER_WIDTH, y * CHARACTER_HEIGHT);

        std::cout << "Move player to: (" << x << ", " << y << ")" << std::endl;
    }
}
