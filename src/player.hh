#ifndef PLAYER_HH
#define PLAYER_HH

#include "character.hh"

namespace Character {
	class Player : public Character {
	    public:
		    Player(unsigned int x, unsigned int y);
		    ~Player();

            Player(const Player&) = delete; // disable copy
            void operator=(const Player&) = delete; // disable assign

            void moveTo(unsigned int x, unsigned int y) override;
	};
}

#endif

