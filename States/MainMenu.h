#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.h"
#include "Texture.h"
#include "GUI.h"


class MainMenu : public State{

public:

	MainMenu();
	~MainMenu();

	//void setStateData();
//	void updateInput(const float &dt);
	void update(const float &dt);
	void updateEvents(SDL_Event &e);
//	void updateMouseEvents(SDL_MouseButtonEvent& e);
	void refreshGUI();
    void loadFiles();
	void render();

	//void updateTextInput(SDL_Event &e);
	//void updateKeyTime(const float &dt, float maxTime = 10.f);

private:

	void initKeyBinds();
	void initVariables();
	//void initFonts();
	void initSaveData();
	void initButtons();

	//SDL_Surface* bg;
	std::unique_ptr<class Texture> mBgTexture;
//	std::unordered_map<std::string, GUI::Button*> mButtons;
    //Mix_Music *music;
	//StateData* stateData;
};

#endif
