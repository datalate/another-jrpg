#ifndef NPC_HH
#define NPC_HH

#include "character.hh"

namespace Character {
	class Npc : public Character {
	public:
		Npc(unsigned int x, unsigned int y);
		~Npc();

        Npc(const Npc&) = delete; // disable copy
        void operator=(const Npc&) = delete; // disable assign
	};
}

#endif

