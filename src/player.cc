#include "player.hh"
#include <iostream>

namespace Game {
	Player::Player(int x, int y):
		Renderable{x * 32, y * 32, "player"}, x_{x}, y_{y} { }

    Player::~Player() {

	}

    void Player::moveTo(int x, int y) {
        x_ = x;
        y_ = y;
        setRenderPos(x * 32, y * 32);

        std::cout << "Move player to: (" << x << ", " << y << ")" << std::endl;
    }
}
