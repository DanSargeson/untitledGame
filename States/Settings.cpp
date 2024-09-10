#include "Settings.h"
#include "Engine.h"

Settings::Settings(){

    SDL_ShowCursor(SDL_ENABLE);
    backButton->setActive(true);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
   // getDynamicText() = std::make_shared<GUI::Text>();
   // getDynamicText()->setPosition(GUI::p2pX(20), GUI::p2pY(40));
    getDynamicText()->setString("");
    settingsTxt = std::make_unique<GUI::Text>();
    volume = std::make_unique<GUI::Text>();

    settingsTxt->setString("Settings:");
    settingsTxt->setPosition(GUI::p2pX(30), GUI::p2pY(10));

    volume->setString("Volume");
    volume->setPosition(GUI::p2pX(15), GUI::p2pY(20));

    mButtons["VOLUME"] = std::make_shared<GUI::Button>(27.f, 20.5f, 4.f, 4.f, 20);
    mButtons["VOLUME"]->setRenderText(">");

    mButtons["VOLUME_DOWN"] = std::make_shared<GUI::Button>(23.f, 20.5f, 4.f, 4.f, 20);
    mButtons["VOLUME_DOWN"]->setRenderText("<");

    musicTxt = std::make_unique<GUI::Text>();
    musicTxt->setPosition(GUI::p2pX(15), GUI::p2pY(25));
    musicTxt->setString("Music");

    mButtons["MUSIC"] = std::make_shared<GUI::Button>(23.f, 25.5f, 4.f, 4.f, 20);
    //musicButton->setRenderText("OFF");

    if(Mix_PausedMusic() == 1){
        mButtons["MUSIC"]->setRenderText("OFF");
    }
    else{
        mButtons["MUSIC"]->setRenderText("ON");
    }
}

Settings::~Settings()
{
//    State::~State();
    State::refreshGUI();
}

void Settings::update(const float& dt){

     backButton->update();
}

void Settings::updateEvents(SDL_Event& e){

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){

        Engine::GetInstance()->PopState();
        getDynamicText()->clearText();
        return;
    }

    if(backButton->isPressed(e.button)){

        Engine::GetInstance()->PopState();
        getDynamicText()->clearText();
        return;
    }

    if(mButtons["VOLUME"]->isPressed(e.button)){

        if(Mix_PlayingMusic() != 0 || Mix_VolumeMusic(-1) == 0){

            int currentVol = Mix_VolumeMusic(-1);
            currentVol += 10;
            if(currentVol > 100){

                Mix_VolumeMusic(MIX_MAX_VOLUME);
                currentVol = 100;
            }
            else{

                Mix_VolumeMusic(currentVol);
            }
            std::string txt = "Curr Volume: " + std::to_string(currentVol);
            getDynamicText()->setString(txt);
        }
    }

    if(mButtons["VOLUME_DOWN"]->isPressed(e.button)){

    if(Mix_PlayingMusic() != 0){

            int currentVol = Mix_VolumeMusic(-1);
            if(currentVol >= 128){

                currentVol = 100;
            }

            currentVol-=10;

            if(currentVol < 0){

                currentVol = 0;
            }
            Mix_VolumeMusic(currentVol);
            std::string txt = "Curr Volume: " + std::to_string(currentVol);
            getDynamicText()->setString(txt);
        }
    }

    if(mButtons["MUSIC"]->isPressed(e.button)){

        if(Mix_PausedMusic() == 1){
            mButtons["MUSIC"]->setRenderText("ON");
            Mix_SetMusicPosition(0);
            Mix_ResumeMusic();
        }
        else{

            mButtons["MUSIC"]->setRenderText("OFF");
            Mix_PauseMusic();
        }

    }

    State::updateEvents(e);
}

void Settings::render(){


    getMainText()->render();
    settingsTxt->render();
    volume->render();
    musicTxt->render();
    getDynamicText()->render();
    for(auto &it : mButtons){

        it.second->renderButtons();
    }

    backButton->renderButtons();
}

