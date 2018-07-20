#ifndef PLAYER_HH
#define PLAYER_HH

#include "renderable.hh"

namespace Game {
	class Player : public Renderable {
	public:
		Player(int x, int y);
		~Player();

        void moveTo(int x, int y);
		int x() const { return x_; }
		int y() const { return y_; }

	private:
		int x_;
		int y_;
	};
}

#endif

