//#include "stdafx.h"
#include "MainMenu.h"

//#include "GameState.h"
#include "CharacterCreator.h"
#include "LoadGame.h"
#include "Settings.h"
#include "Editor.h"
//#include "Texture.h"
#include "Engine.h"

#include <filesystem>
#ifdef WIN32
#include <SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif // WIN32

MainMenu::MainMenu() : State(){

    StateData::GetInstance()->initTimeCycle();
    setSkipIntro(true);
    mBgTexture = std::make_unique<Texture>();


    if (!mBgTexture->loadFromFile("Assets/titleScreenDark2.png", Engine::GetInstance()->GetRenderer())) {

		printf("Unable to load BG Texture. MainMenuState.cpp line 12");
	}

	//music = std::make_unique<Mix_Music>("");
	music = Mix_LoadMUS("Assets/Audio/Intro.wav");
	Mix_VolumeMusic(10);

	if(music == NULL){

        printf("Unable to load main menu music..");
	}

	initButtons();

	//If there is no music playing
                    if( Mix_PlayingMusic() == 0 )
                    {
                        Mix_VolumeMusic(10);
                        //Play the music
                        if( Mix_PlayMusic( music, -1) == -1 )
                        {
                            printf("ERROR PLAYING MUSIC mainMenu.cpp line 69.");
                        }
                    }

                   State::loadCharacters();
}

MainMenu::~MainMenu(){

//    auto it = this->mButtons.begin();
//	for (it = this->mButtons.begin(); it != this->mButtons.end(); ++it) {
//
//		delete it->second;
//	}

//	mBgTexture->free();
//	mBgTexture->~Texture();
//	delete mBgTexture;

Mix_FreeMusic(music);

//State::~State();
}

void MainMenu::refreshGUI(){

    State::refreshGUI();
    initButtons();
}

//void MainMenu::setStateData()
//{
//}

//void MainMenu::updateInput(const float & dt){
//
//	//mStateData->activeCharacter = 0;
//}

void MainMenu::update(const float & dt){

    if(!SDL_ShowCursor(SDL_QUERY)){

        SDL_ShowCursor(SDL_ENABLE);

        return;
    }

	for (auto button : mButtons) {

		button.second->update();
	}
}

//void MainMenu::updateKeyTime(const float &dt, float maxTime){
//}

//void MainMenu::updateEvents(SDL_Event & e){
//}

void MainMenu::loadFiles(){


}

void MainMenu::updateEvents(SDL_Event & e){

    if(!SDL_ShowCursor(SDL_QUERY)){

        SDL_ShowCursor(SDL_ENABLE);
    }

for (auto button : mButtons) {

		button.second->update();
	}

if( Mix_PlayingMusic() == 0 )
                    {
                        Mix_VolumeMusic(10);
                        music = Mix_LoadMUS("Assets/Audio/Intro.wav");

                        //Play the music
                        if( Mix_PlayMusic( music, -1) == -1 )
                        {
                            printf("ERROR PLAYING MUSIC mainMenu.cpp line 69.");
                        }
                    }
	if (mButtons["LOAD_GAME"]->isPressed(e.button)) {

///            std::cout << "LOAD GAME" << std::endl;
	}

	if (mButtons["GAME_STATE"]->isPressed(e.button)) {

		std::cout << "NEW GAME" << std::endl;

        Engine::GetInstance()->AddState(std::make_shared<CharacterCreator>());
		return;
	}

	if (mButtons["LOAD_CHAR"]->isPressed(e.button)) {


///	std::cout << "LOAD" << std::endl;



        if(std::filesystem::exists("characters.txt")){
            Engine::GetInstance()->AddState(std::make_shared<LoadGame>());

        }

        ///Engine::GetInstance()->AddState(std::make_shared<LoadCharacter>());
		return;
	}

	if (mButtons["SETTINGS"]->isPressed(e.button)) {


        Engine::GetInstance()->AddState(std::make_shared<Settings>());
        std::cout << "settings" << std::endl;

		SDL_Delay(400);

		return;
	}

	if(mButtons["QUIT"]->isPressed(e.button)){

        Engine::GetInstance()->Quit();
	}


	if (mButtons["EDITOR"]->isActive() && mButtons["EDITOR"]->isPressed(e.button)) {

		std::cout << "EDITOR" << std::endl;

        Engine::GetInstance()->AddState(std::make_shared<Editor>());
		return;
	}

	if(e.key.keysym.sym == SDLK_e && e.key.repeat == 0){

        mButtons["EDITOR"]->setActive(!mButtons["EDITOR"]->isActive());

        bool check = mButtons["EDITOR"]->isActive();

        std::cout << check;
	}
}

//void MainMenu::updateGUI(){
//
//	initButtons();
//}

void MainMenu::render(){

//        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 255, 0, 25);
        SDL_RenderClear(Engine::GetInstance()->GetRenderer());



        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), mBgTexture->getTexture(), NULL, NULL);




    //SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), , NULL. NULL);
//	SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), mBgTexture->getTexture(), NULL, NULL);
//
	for (auto i : mButtons) {

        if(i.second->isActive()){

            i.second->renderButtons();
        }
	}
}

void MainMenu::initKeyBinds()
{
}

void MainMenu::initVariables(){

//	mBgTexture = std::make_unique<Texture>();
}

//void MainMenu::initFonts()
//{
//}

void MainMenu::initSaveData() {

	if (std::filesystem::exists("Data/Characters.DATA")) {

	//TODO:: BRING THESE BACK
		//stateData->saveData->loadAllCharacters(stateData->characters);
		//stateData->activeCharacter = stateData->saveData->getLastChar();
	}
}

void MainMenu::initButtons(){

	unsigned int charSize = GUI::calcCharSize(80);


	///TODO: All need smart pointers...


	mButtons["LOAD_GAME"] = std::make_shared<GUI::Button>(GUI::p2pXi(75), GUI::p2pY(19.5f),
		GUI::p2pX(20.8f), GUI::p2pY(8.3f), charSize);
	mButtons["LOAD_GAME"]->setRenderText("Continue Game");

	if (!std::filesystem::exists("characters.DATA")) {

		mButtons["LOAD_GAME"]->setActive(false);
	}
	else {

		mButtons["LOAD_GAME"]->setActive(true);
	}

	mButtons["GAME_STATE"] = std::make_shared<GUI::Button>(75, 32.5f, 20.8f, 8.3f, charSize);
	mButtons["GAME_STATE"]->setRenderText("New Game");

	mButtons["LOAD_CHAR"] = std::make_shared<GUI::Button>(75, 45.5f, 20.8f, 8.3f, charSize);
	mButtons["LOAD_CHAR"]->setRenderText("Load Game");

	mButtons["SETTINGS"] = std::make_shared<GUI::Button>(75, 58.5f, 20.8f, 8.3f, charSize);
	mButtons["SETTINGS"]->setRenderText("Settings");

	mButtons["QUIT"] = std::make_shared<GUI::Button>(75, 71.5f, 20.8f, 8.3f, charSize);
	mButtons["QUIT"]->setRenderText("Quit");


	mButtons["EDITOR"] = std::make_shared<GUI::Button>(75, 85.5f, 20.8f, 8.3f, charSize);
	mButtons["EDITOR"]->setRenderText("Editor");
	mButtons["EDITOR"]->setActive(false);

	for (auto button : mButtons) {

		button.second->setBackgroundTexture("Assets/Background/button2.png");
	}
	///mButtons["EDITOR"]->setBackgroundTexture("Assets/Background/wood.png");

}
