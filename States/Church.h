#ifndef CHURCH_H_INCLUDED
#define CHURCH_H_INCLUDED

#include "NPC.h"
#include "State.h"
#include "LoadFiles.h"
///Load files should probs go into state....

enum AREA{

    entrance = 0,
    basin,
    pulpit
};

class Church : public State{

public:
    Church();
    ~Church();
    void update(const float& dt);
    void updateEvents(SDL_Event& e);
    void runMenuSelection();
    void render();

    void handleBasin();
    void handleEntrance();
    void handlePulpit();

    void updateBasinOptions();
    void updatePulpitOptions();

private:
    std::shared_ptr<NPC> satan;
    std::shared_ptr<NPC> randomNPC;
//    bool atPulpit;
//    bool atBasin;
    int currentArea;
    const char* mainMsg;
    int basinLevel;

    bool inDialogue;


    ///FILES/DIAG STUFF
    std::shared_ptr<LoadFiles> file;
    std::string m_fileName;
    std::string json_file;
};


#endif // CHURCH_H_INCLUDED
