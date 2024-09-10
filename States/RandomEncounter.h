#pragma once

#include "State.h"
#include "NPC.h"
#include "GUI.h"
#include "LoadFiles.h"

class RandomEncounter : public State{

    public:

        RandomEncounter(int faction = -1);
        ~RandomEncounter();

        void update(const float& dt);
        void updateEvents(SDL_Event& e);
        void runMenuSelection();
        void render();

        void updateText();
        void startTextThread();

        void refreshGUI();
        bool charm();
        bool rob();

        void recruit();

        void attemptSteal();
        void barter();

    private:

        std::shared_ptr<NPC> npc;
        std::shared_ptr<GUI::Menu> menu;
        std::shared_ptr<GUI::Menu> buyMenu;
        std::shared_ptr<LoadFiles> file;
        std::string filename;
        bool firstEncounter;
        bool unlockedCharm;
        int choice;
        bool buying;
        bool selling;
        bool caught;

         std::thread textThread;
         bool textThreadRunning;
//         bool firstEncounter;
        std::string textMsg;

         std::string copyText;
         std::string builderText;
         int textBuildCounter;
};
