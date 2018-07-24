#ifndef PLAYER_HH
#define PLAYER_HH

#include "renderable.hh"

namespace Game {
    static const unsigned int CHARACTER_WIDTH{32};
    static const unsigned int CHARACTER_HEIGHT{32};

	class Player : public Renderable {
	    public:
		    Player(unsigned int x, unsigned int y);
		    ~Player();

            Player(const Player&) = delete; // disable copy
            void operator=(const Player&) = delete; // disable assign

            void moveTo(unsigned int x, unsigned int y); // doesn't perform checks
		    unsigned int x() const { return x_; }
		    unsigned int y() const { return y_; }

	    private:
		    unsigned int x_;
		    unsigned int y_;
	};
}

#endif

