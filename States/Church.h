#ifndef CHURCH_H_INCLUDED
#define CHURCH_H_INCLUDED

#include "NPC.h"
#include "State.h"

class Church : public State{

public:
    Church();
    ~Church();
    void update(const float& dt);
    void updateEvents(SDL_Event& e);
    void render();

private:
    std::shared_ptr<NPC> satan;
    std::shared_ptr<NPC> randomNPC;
};


#endif // CHURCH_H_INCLUDED
