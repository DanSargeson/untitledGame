#ifndef LOADGAME_H
#define LOADGAME_H

#include "GUI.h"
#include "State.h"

class LoadGame : public State{

    public:

        LoadGame();
        ~LoadGame();
        void update(const float &dt);
        void updateEvents(SDL_Event &e);
        void refreshGUI();
        void render();

//        void loadCharacters();

    private:
           // std::shared_ptr<GUI::Menu> loadMenu;
};

#endif // LOADGAME_H

