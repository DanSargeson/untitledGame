#ifndef FOLLOWERMENU_H
#define FOLLOWERMENU_H

#include "GUI.h"
#include "State.h"

class FollowerMenu : public State{

    public:

        FollowerMenu();
        ~FollowerMenu();
        void update(const float &dt);
        void updateEvents(SDL_Event &e);
        void render();
        void refreshGUI();
        void runMenuSelection();

        void initFollowerList();

        void initButtons();
        //void loadCharacters();

    private:
            //std::shared_ptr<GUI::Menu> invMenu;
            std::shared_ptr<GUI::Menu> invMenu2;

            std::unique_ptr<Texture> followerIcons;
            std::vector<std::shared_ptr<GUI::Text>> followerText;
            std::vector<std::unique_ptr<GUI::InvSlot>> invSlotVec;
            std::unique_ptr<GUI::Button> battleButton;
          //  std::unordered_map<std::string, GUI::Button*> mButtons;
            int choice;


            SDL_Rect mummerRect;
            SDL_Rect doctorRect;
            SDL_Rect innkeeperRect;
            SDL_Rect prospectorRect;
            SDL_Rect blacksmithRect;
            SDL_Rect alchemistRect;
            SDL_Rect bardRect;


//            std::vector<SDL_Rect> slotsVector;
//            SDL_Rect slot1rect;
//            SDL_Rect slot2rect;
//            SDL_Rect slot3rect;
//            SDL_Rect slot4rect;
//            SDL_Rect slot5rect;
};

#endif // LOADGAME_H


