#ifndef CHARACTER_HH
#define CHARACTER_HH

#include "renderable.hh"

namespace Character {
    static const unsigned int CHARACTER_WIDTH{32};
    static const unsigned int CHARACTER_HEIGHT{32};

    class Character : public Renderable {
    public:
        Character(unsigned int x, unsigned int y, const std::string& type);
        virtual ~Character();

        virtual void moveTo(unsigned int x, unsigned int y);

        unsigned int x() const { return x_; }
        unsigned int y() const { return y_; }

    private:
        unsigned int x_;
        unsigned int y_;

        int dirX_;
        int dirY_;
    };
}

#endif

