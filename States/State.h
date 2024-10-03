#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <atomic>

#include <mutex>
#include <condition_variable>

#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif // WIN32
#include "Player.h"
#include "Enemy.h"
#include "GUI.h"
#include "Camera.h"
#include "Timer.h"
//#include "SaveData.h"

class StateData{

public:

    static StateData* GetInstance(){       //Checks if object is created, if true returns object if false create object

            return s_Instance = (s_Instance != nullptr) ?  s_Instance : new StateData();
        }

    //SHOULD COME UNDER THE ENGINE
///    SDL_Window* window;
///    SDL_Renderer* renderer;
    //std::unordered_map<std::string, int>* supportedKeys;


    //int cameraVelocity;

    //Camera, same as old or use a new method??
    std::unique_ptr<Camera> camera;

    void initFonts();

    void push_state(std::shared_ptr<class State> s);
    void pop_state();

    std::shared_ptr<Player> getActiveCharacter(){
        if(!characters.empty()){

            return characters[activeCharacter];
        }
        else{
            return nullptr;
        }
    }

    void startBattleThread();
    void initTimeCycle();
    std::shared_ptr<class Battle> b;

    std::shared_ptr<GameTimer> followerTimer;
//    std::shared_ptr<GameTimer> worldTimer;
//    int daysPassed;
    bool prevDay;
    int battleCounter;

     void runFollowerBattles();
     void startFollowerAction();

     float cycleTime;
     float dayCycle;
     float hours;
     int minutes;
     int displayHours;
     bool isDay;


    static std::atomic<bool> battleThreadRunning;
    static std::atomic<bool> battleThreadPaused;
    std::thread battleThread;
    std::mutex mtx;
    std::condition_variable cv;


    //TO BE DETERMINED
    void createCamera(int maxSize);
    void moveCamera(int direction, int axis);
    void moveCam2(int dir, float time);
    void stopCam2(int dir, float time);
    void setCamPosition(int x, int y);

    void clearCharacters();

    void updateCamera(float dt);

    SDL_Rect getCamera();

    std::string saveName;

    int activeCharacter = 0;
    std::vector<std::shared_ptr<Player>> characters;

    std::vector<std::shared_ptr<class State>>* states;
    //SDL_Rect camera;

    bool gameEvent = false;
    int menuType = -1;
    int gridSize = 64;
    float gridSizeF = 64.0;
    bool refreshFollowerList = false;

    int currentState = 0;

    TTF_Font* font;

  ///  std::unique_ptr<class SaveData> saveData;

    std::shared_ptr<class TileMap> currentMap;

    inline void setTutorial(bool t) { tutorial = t; }
    inline bool getTutorial() { return tutorial; }

    std::vector<Enemy*> enemies;

    std::string mainTextStr;
    bool clickToNext = false;

    bool skipIntro = true;

   //Need to think how best to get text to work
    std::shared_ptr<GUI::Text> mainText;
    std::shared_ptr<GUI::Text> dynamicText;
    std::shared_ptr<GUI::Text> enemyText;
    std::shared_ptr<GUI::Text> followerScreenText;

    bool next = false;
    bool quit = false;
    bool gameOver = false;
    bool tutorial = false;

private:
    StateData() { };

     static StateData* s_Instance;
};

class State{

public:

    friend StateData;

    State();
    virtual ~State();

    void setData(StateData& StateData);

    virtual void update(const float &dt);
    virtual void updateEvents(SDL_Event &e);
    virtual void updateButtons();
    virtual void render() = 0;


    void calcWorldTime();

    int getRandomValue(int low, int high);
    bool chancePassed(int percentChance, int skillModifier = 0);

    void loadCharacters();
    virtual void refreshGUI();
    void initButtons();
    StateData* getData() { return StateData::GetInstance(); }

    std::shared_ptr<GUI::Text> getMainText() { return getData()->mainText; }
    std::shared_ptr<GUI::Text> getDynamicText() { return getData()->dynamicText; }
    std::shared_ptr<GUI::Text> getEnemyText() { return getData()->enemyText; }
    std::shared_ptr<GUI::Text> getFollowerText() { return getData()->followerScreenText; }
    bool skipIntro() { return getData()->skipIntro; }

    void setSkipIntro(bool skip) { getData()->skipIntro = skip; }
    std::shared_ptr<Player> getActiveCharacter() { return getData()->getActiveCharacter(); }

    bool getQuit();
    const bool getKeyTime();
    inline void endState() { quit = true; }
    inline void pauseState() { paused = true; }
    inline void unpauseState() { paused = false; }
    inline bool isPaused() { return paused; }

    int loadRandomFaction();

    void saveCharacters();

private:

protected:

    bool exitingBattles;
    bool mainScreen;
    std::shared_ptr<GameTimer> holdTimer;
    std::shared_ptr<GUI::Text> timerText;
    std::shared_ptr<GUI::Text> worldTimerText;
    std::map<std::string, std::shared_ptr<GUI::Button>> mButtons;
    std::shared_ptr<GUI::textBox> confirmationBox;
   // StateData* mStateData;
    std::unordered_map<std::string, int> keyBinds;
    bool quit;
    bool paused;
    float keyTime;
    float keyTimeMax;
    bool gameOver;
    bool resolutionChange;
    Mix_Music *music;

    std::shared_ptr<Texture> worldIcon;
    SDL_Rect worldRect;

    std::shared_ptr<GUI::Button> backButton;

    std::shared_ptr<GameTimer> textTimer;
    std::shared_ptr<GUI::Menu> menu;
    std::vector<std::string> ops;
    unsigned seed;
    std::default_random_engine generator;

    ///TODO: Replace StateData Test with this...
///    std::shared_ptr<GUI::Text> mainText;
///    std::shared_ptr<GUI::Text> dynamicText;
///    std::shared_ptr<GUI::Text> enemyText;
};

#endif // STATE_H

