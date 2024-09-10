#ifndef PLAYERDEATH_H
#define PLAYERDEATH_H

#include "Timer.h"
#include "State.h"

class PlayerDeath : public State{


    public:

        PlayerDeath();
        ~PlayerDeath();
        void update(const float &dt);
        void updateEvents(SDL_Event &e);
        void render();

        void refreshGUI();

    private:

       // std::unique_ptr<GameTimer> textTimer;
        int alpha;
        int alpha2;
        std::shared_ptr<GUI::Text> deathMsg;
        std::shared_ptr<GUI::Text> deathMsg2;
        std::shared_ptr<GUI::Text> deathMsg3;
};

#endif
