#include "npc.hh"

namespace Character {
    Npc::Npc(unsigned int x, unsigned int y):
        Character{x, y, "npc"}
    {}

    Npc::~Npc() {
    }
}
