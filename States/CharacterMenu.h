#ifndef CHARACTERMENU_H
#define CHARACTERMENU_H

#include "GUI.h"
#include "State.h"

class CharacterMenu : public State{

    public:

        CharacterMenu();
        ~CharacterMenu();
        void update(const float &dt);
        void updateEvents(SDL_Event &e);
        void render();
        void refreshGUI();
        void runMenuSelection();
        void checkItemStrength();
        void craft();

        void initButtons();
        //void loadCharacters();

    private:
            //std::shared_ptr<GUI::Menu> invMenu;
            std::shared_ptr<GUI::Menu> invMenu2;
            std::unordered_map<std::string, GUI::Button*> mButtons;
            int choice;
};

#endif // LOADGAME_H


