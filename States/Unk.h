#ifndef UNK_H_INCLUDED
#define UNK_H_INCLUDED

#include "NPC.h"
#include "State.h"

class Unk : public State{

public:
    Unk();
    ~Unk();
    void update(const float& dt);
    void updateEvents(SDL_Event& e);
    void render();

private:
    std::shared_ptr<NPC> apep;
    std::shared_ptr<NPC> randomNPC;
};


#endif // CHURCH_H_INCLUDED
