#pragma once
#include "State.h"

class Settings : public State{

public:
        Settings();
        ~Settings();
        void update(const float &dt);
        void updateEvents(SDL_Event &e);
        void render();

private:

        std::unique_ptr<GUI::Text> settingsTxt;
        std::unique_ptr<GUI::Text> musicTxt;
   //     std::unique_ptr<GUI::Button> musicButton;
        std::unique_ptr<GUI::Text> volume;
//        std::unique_ptr<GUI::Button> volumeButton;
//        std::unique_ptr<GUI::Button> volDown;

};
