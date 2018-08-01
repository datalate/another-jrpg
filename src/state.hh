#ifndef STATE_HH
#define STATE_HH

namespace Game {
    class AnotherRpg;

    class State {
    public:
        explicit State(AnotherRpg& rpg);
        virtual ~State();
        // TODO: delete copy/assignment operators
        
        virtual void init() = 0;
        virtual void cleanup() = 0;

        virtual void update() = 0;
        virtual void draw() = 0;

        virtual void pause() { paused_ = true; }
        virtual void resume() { paused_ = false; }

    protected:
        AnotherRpg& rpg_;
        bool paused_;
    };
}

#endif
