#ifndef BATTLE_H
#define BATTLE_H

#include <thread>
#include <atomic>

#include "State.h"
#include "Timer.h"
#include "Player.h"

class Battle : public State{

    public:

        Battle(bool debug = false);
        ~Battle();

        void update(const float &dt);
        void updateEvents(SDL_Event &e);

        void initBattle();
        void updateMenu();
        void updateText();
        void updateWinText();
        const void enemyAttacks();
        void enemyAttacksAuto();
        void magicAttack();
        const void playerAttacks();
        void followerAttacks();
        void render();
        void refreshGUI();

        void spawnEnemies();

        void startTextThread();
        void startWinThread();

        void runTests();
        void followersAutoBattle();


        void itemRoll();
        void runMenuSelection();
        void runAway();

        bool battleActive(){ return active; }

        std::vector<std::shared_ptr<Enemy>> getEnemies() { return enemies; };

    private:
        std::shared_ptr<GUI::Menu> battleMenu;
        std::shared_ptr<GUI::Menu> enemyMenu;
        std::vector<std::shared_ptr<Enemy>> enemies;
        std::vector<std::shared_ptr<GUI::textBox>> enemyTextBoxes;
        std::vector<std::shared_ptr<GUI::Text>> enemyText;
        GUI::Text temp;
        std::unique_ptr<Texture> bg1;
        std::unique_ptr<Texture> bg2;
        std::unique_ptr<GameTimer> moveTimer;

        bool debug;
        bool active;

        int moveDelay;

        std::unique_ptr<GUI::textBox> battleCloseMsg;

        std::unique_ptr<Timer> battleTxtTimer;
        std::unique_ptr<GameTimer> battleGameTimer;
        std::unique_ptr<GameTimer> endGameTimer;

        bool playerTurn;
        bool playerWins;
        int choice;
        int playerAccuracy;
        int playerDefence;
        int playerTotal;
        int enemyAccuracy;
        int enemyDefence;
        int enemyTotal;
        int combatTotal;
        int combatRoll;
        int combatRollPlayer;
        int combatRollEnemy;
        float alpha;
        float alpha2;
        float winAlpha;

        bool escape;
        bool playerDefeated;
        bool enemyDefeated;
        int noOfEnemies;

        //bool playerAtk;

        //BATTLE VARIABLES
        int attackRoll;
        int defendRoll;
        int damage;
        int gainEXP;
        int totalEXP;
        int totalGold;
        int gainGold;

        int missCounter;
        int enemyMissCounter;
        bool endTurn;

        std::string endMsg;
        std::unique_ptr<GUI::Text> playerAttkTxt;
        std::unique_ptr<GUI::Text> enemyAttkTxt;

        std::thread textThread;
        std::thread winThread;
        std::atomic<bool> textThreadRunning;
        std::atomic<bool> winThreadRunning;




//        unsigned seed;
//        std::default_random_engine generator;

        std::shared_ptr<Player> player;
        std::shared_ptr<GUI::Tooltip> battleEyes;
};

#endif // BATTLE_H
