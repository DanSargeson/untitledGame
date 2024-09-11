#ifndef SHEOL_H_INCLUDED
#define SHEOL_H_INCLUDED

#include "NPC.h"
#include "State.h"

class Sheol : public State{

public:
    Sheol();
    ~Sheol();
    void update(const float& dt);
    void updateEvents(SDL_Event& e);
    void render();

private:
    std::shared_ptr<NPC> Yam;
    std::shared_ptr<NPC> randomNPC;
};


#endif // CHURCH_H_INCLUDED
