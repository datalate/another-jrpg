#include "player.hh"
#include <iostream>

namespace Game {
	Player::Player(unsigned int x, unsigned int y):
		Renderable{x * CHARACTER_WIDTH, y * CHARACTER_HEIGHT, "player"}, x_{x}, y_{y}
    { }

    Player::~Player() {
    }

    void Player::moveTo(unsigned int x, unsigned int y) {
        x_ = x;
        y_ = y;
        setRenderPos(x * CHARACTER_WIDTH, y * CHARACTER_HEIGHT);

        std::cout << "Move player to: (" << x << ", " << y << ")" << std::endl;
    }
}
