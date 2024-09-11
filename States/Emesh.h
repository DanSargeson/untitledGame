#ifndef EMESH_H_INCLUDED
#define EMESH_H_INCLUDED

#include "NPC.h"
#include "State.h"

class Emesh : public State{

public:
    Emesh();
    ~Emesh();
    void update(const float& dt);
    void updateEvents(SDL_Event& e);
    void render();

private:
    std::shared_ptr<NPC> Yam;
    std::shared_ptr<NPC> randomNPC;
};


#endif // CHURCH_H_INCLUDED
