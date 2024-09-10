#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "GUI.h"
#include "LoadFiles.h"
#include <thread>
#include <queue>
#include <functional>



enum LAST_SCREEN{

    character = 0,
    skills,
    faction,
    followers
};

class Game : public State{


public:
    Game();
    ~Game();
    	//void setStateData();
//	void updateInput(const float &dt);

    void update(const float &dt);
	void updateEvents(SDL_Event &e);

	void runMenuSelection();
	void runTutorial();
	void render();

//	void startBattleThread();
//	void runFollowerBattles();

	void initButtons();
	void refreshGUI();

private:

   // std::unique_ptr<GUI::Menu> gameMenu;
    std::shared_ptr<GUI::Text> mainText;
    std::queue<std::function<void()>> battleTasks;
    std::unique_ptr<Texture> bgTexture;

    int lastScreen;
//    int battleCounter;

    std::shared_ptr<GUI::textBox> textBox;

    std::shared_ptr<GUI::Text> levelUpText;

//    std::shared_ptr<class Battle> b;
//
//    std::shared_ptr<GameTimer> followerTimer;

//     std::unordered_map<std::string, GUI::Button*> mButtons;

    std::shared_ptr<Entity> testNpc;

    std::shared_ptr<LoadFiles> file;

    //std::unique_ptr<Texture> background;
    std::unique_ptr<Texture> bg1;
    std::unique_ptr<Texture> bg2;

    int tutorialCount;
    //Mix_Music *music;
};


#endif // GAME_H

