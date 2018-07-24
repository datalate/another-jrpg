#include "player.hh"
#include <iostream>

namespace Character {
	Player::Player(unsigned int x, unsigned int y):
		Character{x, y, "player"}
    { }

    Player::~Player() {
    }

    void Player::moveTo(unsigned int x, unsigned int y) {
        Character::moveTo(x, y);

        std::cout << "Move player to: (" << x << ", " << y << ")" << std::endl;
    }
}
