#include "player.hh"
#include <iostream>

namespace Character {
	Player::Player():
		Character{0, 0, "player"}
    { }

    Player::~Player() {
    }

    void Player::moveTo(unsigned int x, unsigned int y) {
        Character::moveTo(x, y);

        //std::cout << "Move player to: (" << x << ", " << y << ")" << std::endl;
    }
}
