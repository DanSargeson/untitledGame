#include "Battle.h"
#include "Engine.h"
#include "Input.h"
#include "PlayerDeath.h"
#include "SkillComponent.h"
#include "Texture.h"
#include "Resource.h"
#include "Key.h"

Battle::Battle(bool d) : State(), debug(d), alpha(255), alpha2(255), missCounter(0), enemyMissCounter(0), battleTxtTimer(std::make_unique<Timer>()), battleGameTimer(std::make_unique<GameTimer>())/*, seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())), generator(seed)*/, noOfEnemies(0) {


    bg1 = std::make_unique<Texture>();
    bg2 = std::make_unique<Texture>();

    moveDelay = 300; //miliseconds between player attacking and enemy attacking...

    moveTimer = std::make_unique<GameTimer>();

    if(!bg1->loadFromFile("Assets/Background/metal.png", Engine::GetInstance()->GetRenderer())){

        printf("Error loading wood. Lol");
    }

    if(!bg2->loadFromFile("Assets/Background/metal.png", Engine::GetInstance()->GetRenderer())){

        printf("Error loading wood. Lol");
    }

//     std::uniform_int_distribution<int> numEnemiesDistribution(1, 3);
//     noOfEnemies = numEnemiesDistribution(generator);

    textThreadRunning = false;
    winThreadRunning = false;

    active = true;

   /// debug = debug;
    backButton->setActive(true);

     playerWins = false;
     totalEXP = 0;
     totalGold = 0;

     if (!debug) {


     player = StateData::GetInstance()->getActiveCharacter();

//    std::vector<std::string> ops;
    ops.clear();
    ops.push_back("Attack");
    ops.push_back("Defend");
    ops.push_back("Use Magic");
    ops.push_back("Use Third Eye");
    //menu.reset();
    //menu = std::make_shared<GUI::Menu>();
    menu->setMenuOptions(ops, true);

    enemyMenu.reset();
    enemyMenu = std::make_shared<GUI::Menu>();

    enemyMenu->setActive(false);

   // getMainText() = std::make_shared<GUI::Text>(5, 10, 12, 8, true);
    //getMainText()->setString("Test");
    //getDynamicText()->setString("You are attacked: ");

    getEnemyText()->setString("");
    getEnemyText()->setColour(255, 0, 0, 0);

    playerAttkTxt = std::make_unique<GUI::Text>(true);
    playerAttkTxt->setColour(0, 0, 255, 0);
    playerAttkTxt->setPosition(GUI::p2pX(15.f), GUI::p2pY(55.f));
    playerAttkTxt->clearText();

    enemyAttkTxt = std::make_unique<GUI::Text>(true);
    enemyAttkTxt->setColour(255, 0, 0, 0);
    enemyAttkTxt->setPosition(GUI::p2pX(60.f), GUI::p2pY(50.f));
    enemyAttkTxt->clearText();

    battleCloseMsg = std::make_unique<GUI::textBox>();
    battleCloseMsg->setSize(60, 40);
    battleCloseMsg->centreTextBox();
    battleCloseMsg->setActive(false);

     }  //END DEBUG CHECK
    playerTurn = false;
    endTurn = false;
	choice = 0;
	playerAccuracy = 0;
	playerDefence = 0;
	playerTotal = 0;
	enemyAccuracy = 0;
	enemyDefence = 0;
	enemyTotal = 0;
	combatTotal = 0;
	combatRoll = 0;
	combatRollPlayer = 0;
	combatRollEnemy = 0;
	while(enemies.size() > 0) {
		enemies.erase(enemies.begin());
	}


	spawnEnemies();

	//COIN TOSS DETERMINES TURN


	seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

     generator.seed(seed);

     std::uniform_int_distribution<int> coinDistribution(1, 6);
     int coinToss = coinDistribution(generator);

	playerTurn = (coinToss <= 4);
	if(!playerTurn){

        moveTimer->start();
	}
	escape = false;
	playerDefeated = false;
	enemyDefeated = false;

	//BATTLE VARIABLES
	attackRoll = 0;
	defendRoll = 0;
	damage = 0;
	gainEXP = 0;
	gainGold = 0;

	battleEyes = std::make_shared<GUI::Tooltip>();

	initBattle();
}

void Battle::spawnEnemies(){

    active = true;
    enemies.clear();
    /*Spawn Enemies*/
    std::random_device rd;
    std::mt19937 gen(rd());
    int maxi = 1 + getData()->getActiveCharacter()->getLevel();
    if(debug){

        maxi = 1 + getActiveCharacter()->getActiveFollower()->getLevel();
    }
    if(maxi > 3){

        maxi = 3;
    }
    std::uniform_int_distribution<> dis(1, maxi);

    noOfEnemies = dis(gen);
    int playerLvl = getData()->getActiveCharacter()->getLevel();
    if(debug){

        playerLvl = getActiveCharacter()->getActiveFollower()->getLevel();
    }
    if(playerLvl <= 10){

        noOfEnemies = 2;
        if(playerLvl <= 10){

            noOfEnemies = 1;
        }
    }

//    if(debug){
//
//        noOfEnemies = 1;
//    }

    int faction = getRandomValue(2,4);
	for (int i = 0; i < noOfEnemies; i++){

		///*Easy Mode*/
//		int low = getData()->getActiveCharacter()->getLevel() - 2;
//		int high = getData()->getActiveCharacter()->getLevel();

		int low = getData()->getActiveCharacter()->getLevel() - 3;
		int high = getData()->getActiveCharacter()->getLevel();

		if(debug){

            low = getActiveCharacter()->getActiveFollower()->getLevel() - 1;
            high = getActiveCharacter()->getActiveFollower()->getLevel() + 1;
		}

		int rando = 0;
		std::uniform_int_distribution<>randEnemies(low, high);
		rando = randEnemies(gen);
		if(low <= 1){

            rando = 1;
		}

		std::shared_ptr<Enemy> temp = std::make_shared<Enemy>(rando, faction);
		enemies.push_back(temp);
		if(!debug){
            enemyText.push_back(std::make_shared<GUI::Text>());

            for(size_t i = 0; i < enemies.size(); i++){

                enemyText[i]->setColour(255, 0, 0, 0);
            }
		}
        SDL_Delay(19);
	}

	for(size_t i = 0; i < enemies.size(); i++){

        enemies[i]->createComponents();
        enemies[i]->updateStats();
        enemies[i]->calculateSkills();
        if(!debug){

        std::string msg = "Corrupted " + enemies[i]->getSavedFactionName() + " " + enemies[i]->getName() + " HP: " + std::to_string(enemies[i]->getHP()) + "/" + std::to_string(enemies[i]->getHPMax());
        enemyText[i]->setString(msg);
        enemyText[i]->setColour(255, 0, 0, 0);
		enemyText[i]->setPosition(GUI::p2pX(55), GUI::p2pY(15 + (i*5)));
        }
	}
    /*END SPAWN ENEMIES */
}

void Battle::runTests(){

    int win = 0;
    int lose = 0;

        if(getActiveCharacter()->getActiveFollower()->isAlive() && !enemies.empty()){

            if(playerTurn){

                followerAttacks();
                std::cout << "Follower attack" << std::endl;
                playerTurn = false;
            }
            else{

                enemyAttacks();
                std::cout << "Enemy attack" << std::endl;
                playerTurn = true;
            }
        }

        if(enemies.empty()){

            win++;
            playerWins = true;
            getActiveCharacter()->gainXP(gainEXP / 4);
            getActiveCharacter()->getActiveFollower()->gainXP(gainEXP);
            ///std::string msg = getActiveCharacter()->getActiveFollower()->getName() + " earned some value experience";
            ///battleCloseMsg->setText(msg);

            active = false;
        }
        else if(!getActiveCharacter()->getActiveFollower()->isAlive()){

            lose++;
            ///getActiveCharacter()->removeFollower(getActiveCharacter()->getActiveFollower());
            ///this->battleCloseMsg->setHeader("Follower Lost!");
            ///this->battleCloseMsg->setText("A brave soul returns to the void.");
            playerWins = true;

            active = false;
        }
}

void Battle::followersAutoBattle(){

    if(getActiveCharacter()->getActiveFollower()->isAlive()){

        if(enemies.empty()){

            initBattle();
        }

        if(active && playerTurn){

            followerAttacks();

            return;
        }
        if(active && !playerTurn){

            enemyAttacksAuto();

            return;
        }
    }
    else{

        std::cout << "Follower 0 is dead!" << std::endl;
    }
}

Battle::~Battle(){

//    menu.reset();
//    enemyMenu.reset();

//    enemyAttkTxt.reset();
//    playerAttkTxt.reset();

    //getMainText()->clearText();
    //getMainText() = std::make_shared<GUI::Text>(5, 5, 89, 60, true);
    //getEnemyText()->clearText();
    //getDynamicText()->clearText();
    enemies.clear();

    backButton->setRenderText("Back");

    if(textThread.joinable()){

        textThread.join();
    }

    if(winThread.joinable()){

        winThread.join();
    }

  getEnemyText()->setPosition(GUI::p2pX(55), GUI::p2pY(40));
  getDynamicText()->setPosition(GUI::p2pX(55), GUI::p2pY(30));

    std::cout << "BATTLE DESTRUCTOR CALLED" << std::endl;
}

void Battle::refreshGUI(){

    State::refreshGUI();

    for(size_t i = 0; i < enemies.size(); i++){

        std::string msg = "Corrupted " + enemies[i]->getSavedFactionName() + " " + enemies[i]->getName() + " HP: " + std::to_string(enemies[i]->getHP()) + "/" + std::to_string(enemies[i]->getHPMax());
        enemyText[i]->setString(msg);
     //   enemyText[i]->setColour(255, 0, 0, 0);
		enemyText[i]->setPosition(GUI::p2pX(55), GUI::p2pY(15 + (i*5)));
	}

    enemyAttkTxt->refreshGUI();
    playerAttkTxt->refreshGUI();

    playerAttkTxt->setPosition(GUI::p2pX(15.f), GUI::p2pY(55.f));
    enemyAttkTxt->setPosition(GUI::p2pX(55.f), GUI::p2pY(50.f));


    battleCloseMsg->setSize(60, 40);
    battleCloseMsg->centreTextBox();
    //menu->setPosition();
}


void Battle::initBattle(){

spawnEnemies();
if(!debug){

endMsg = "";
winAlpha = 0;
endGameTimer = std::make_unique<GameTimer>();
endGameTimer->start();
battleGameTimer->start();

moveTimer->start();

if(!escape && !playerDefeated && !enemyDefeated) {

		if (playerTurn && !playerDefeated) {
            //TODO:: HERE IS WHERE TO CHANGE THINGS FOR BATTLEMODE
            std::vector<std::string> ops;
            ops.push_back("Attack");
            ops.push_back("Defend");
            ops.push_back("Use Magic");
            ops.push_back("Use Third Eye");
            menu->setMenuOptions(ops, true);
            std::string msg = "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHPMax());
            std::string enemyMsg = "";
            if(menu->getActive()){

//                for(int i = 0; i < enemies.size(); i++){
//
//                    enemyMsg += enemies[i]->getName() + ": " + "HP: " + std::to_string(enemies[i]->getHP()) + "/" + std::to_string(enemies[i]->getHPMax()) + " ";
//                }
//                getEnemyText()->setString(enemyMsg);
            }
			}
        }

        else{

            enemyAttacks();
        }
    }
}


void Battle::updateMenu(){


    //getDynamicText()->setString("Which enemy to attack?: ");
    std::vector<std::string> enemyMenuStr;

    for(size_t i = 0; i < enemies.size(); i++){

        enemyMenuStr.push_back(enemies[i]->getName());
    }

    enemyMenu->setMenuOptions(enemyMenuStr, true);
    enemyMenu->setActive(true);
    menu->setActive(false);
}

void Battle::update(const float& dt){

//    if(moveTimer->getTicks() < 500){
//
//        //if(!enem)
//        return;
//    }

//calcWorldTime();


if(!endTurn){

        backButton->setActive(true);

        backButton->update();

        if(!enemyMenu->getActive()){

            backButton->setRenderText("Run away");
        }
        else{

            backButton->setRenderText("Back");
        }
}


if(endTurn){

    backButton->setActive(false);
//    if(playerWins){
//
//        updateText();
//    }

    menu->setActive(false);

    if(!playerDefeated){

        if(!playerWins){

            return;
        }
    }
}

menu->update();
enemyMenu->update();

///moveTimer->Tick();
battleTxtTimer->Tick();

if(playerDefeated){

    getMainText()->setColour(255, 0, 0, 0);
    getMainText()->setString("You Died!");

    playerTurn = false;
    endTurn = true;

    textThreadRunning = false;
    winThreadRunning = false;
    if(textThread.joinable()){

        textThread.join();
    }

    if(winThread.joinable()){

        winThread.join();
    }

//    if(debug){
//
//        return;
//    }
//    ~Battle();

        if(!debug){

           // Engine::GetInstance()->PopState();
            Engine::GetInstance()->PopState();
            Engine::GetInstance()->AddState(std::make_shared<PlayerDeath>());
        }
    return;
}

if(playerWins){

    if(winThread.joinable()){

        if(winAlpha >= 255){

            winThread.join();
        }
        return;
    }
}


        if(!debug){

            std::string msg = "You are attacked.\n\n";
            msg += "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHPMax());
            getMainText()->setString(msg, true);
            getMainText()->render();
            std::string enemyMsg = "";
        }

    if(!escape && !playerDefeated && !enemyDefeated) {

		if (playerTurn && !playerDefeated) {

        //#############FINALISE TURN
            if (!StateData::GetInstance()->getActiveCharacter()->isAlive()) {
                playerDefeated = true;
//                ~Battle();
               // Engine::GetInstance()->PopState();
                Engine::GetInstance()->PopState();
                Engine::GetInstance()->AddState(std::make_shared<PlayerDeath>());

                return;
            }
            else if (enemies.size() <= 0) {
                enemyDefeated = true;
                ///cout << "All enemies defeated!\n\n";
  //              ~Battle();
              //  Engine::GetInstance()->PopState();
                Engine::GetInstance()->PopState();
            }
        }

        if(!playerTurn && !playerDefeated){

                //std::cout << "DT:  " << battleGameTimer->getTicks() << std::endl;
   //             SDL_Delay(10);
                    enemyAttacks();
                   /// battleGameTimer->stop();
                //}
        }
	}

//	if(alpha2 <=5 || alpha <=5){
//        if(textThread.joinable()){
//            textThread.join();
//        }
//        textThreadRunning = false;      ///HREE YOU COMMENTED
//	}
}

void Battle::startTextThread(){

    if(textThread.joinable()){

        textThread.join();
    }

    textThreadRunning = true;
    textThread = std::thread(&Battle::updateText, this);
}

void Battle::startWinThread(){

    winThreadRunning = true;
    winThread = std::thread(&Battle::updateWinText, this);
}

void Battle::updateWinText(){

    while(winThreadRunning){

    if(playerWins){

        if(winThreadRunning && endGameTimer != nullptr && endGameTimer->getTicks() > 5){

            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
            winAlpha+= 7;
            if(winAlpha > 255){

                winAlpha = 255;
                winThreadRunning = false;
            }

            battleCloseMsg->setAlpha(winAlpha);
            SDL_SetTextureAlphaMod(this->battleCloseMsg->getTexture(), winAlpha);
            SDL_SetTextureAlphaMod(this->battleCloseMsg->getHeaderTexture(), winAlpha);

            endGameTimer->restart();
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Battle::updateText(){


    while(textThreadRunning){

    if(playerAttkTxt && playerTurn && !endTurn){

        if(alpha >= 0){

            alpha -= 5;
            SDL_SetTextureAlphaMod(playerAttkTxt->getTexture(), alpha);
     ///       battleTxtTimer->Restart();
        }
        else{

            //alpha = 255;
            textThreadRunning = false;
        }
    }


    if(enemyAttkTxt && !endTurn){

        //std::this_thread::sleep_for(std::chrono::milliseconds(20));
        if(alpha2 >= 0){

            alpha2 -= 5;
            SDL_SetTextureAlphaMod(enemyAttkTxt->getTexture(), alpha2);
        }
        else{

///            enemyAttkTxt->clearText();
        //    alpha2 = 255;
            textThreadRunning = false;
        }
    }
     std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void Battle::magicAttack(){

    alpha = 255;
    int faction = enemies[0]->getSavedFaction();
    int magicMultiplier = 1;

    ///CHECK PLAYER'S STANDING WITH FACTION
    if (getActiveCharacter()->getRep(faction) > 110) {
        magicMultiplier = 3;
    }

    ///CAST MAGIC HERE
    int baseDmg = 50;
    std::string msg = "";
    // Use iterators instead of indices
    for (auto it = enemies.begin(); it != enemies.end();) {
        (*it)->loseHP(baseDmg * magicMultiplier);
        if ((*it)->isAlive()) {
            msg = "Corrupted " + (*it)->getSavedFactionName() + " " + (*it)->getName() + " HP: " +
                  std::to_string((*it)->getHP()) + "/" + std::to_string((*it)->getHPMax()) + "\n";
            enemyText[it - enemies.begin()]->setString(msg);
            ++it;  // Move iterator forward
        } else {
            // Remove dead enemy and get iterator to the next valid position
            enemyText[it - enemies.begin()]->setString("");
            enemyText.erase(enemyText.begin() + (it - enemies.begin()));
            battleCloseMsg->setHeader("YOU DEFEATED!");
            gainGold = getRandomValue(1, 10);
            totalGold += gainGold;
            StateData::GetInstance()->getActiveCharacter()->gainGold(gainGold);
            gainEXP = enemies[it - enemies.begin()]->getExp();
            totalEXP += gainEXP;
            StateData::GetInstance()->getActiveCharacter()->gainXP(gainEXP);

            getActiveCharacter()->gainRep(enemies[it - enemies.begin()]->getSavedFaction(), 10);
            endMsg += "Gold Gained: " + std::to_string(gainGold) + "\n";
            endMsg += "EXP Gained: " + std::to_string(gainEXP) + "\n";

            if(getData()->getActiveCharacter()->getExp() >= getData()->getActiveCharacter()->getExpNext()){

                getData()->getActiveCharacter()->levelUp();
                endMsg += "\nLevelled up!!\n";
            }

            gainEXP = 0;
            gainGold = 0;
            int x = getRandomValue(0, 100);

            ///if(x >= 75){ ///TODO CHANGE TO DROP CHANCE VARIABLE

                itemRoll();
            ///}

            battleCloseMsg->setText(endMsg);
            it = enemies.erase(it);
        }
    }
    ///END CAST MAGIC

    std::string dmgMsg = "ALL ENEMIES HIT for " + std::to_string(baseDmg * magicMultiplier) + " damage!";
    playerAttkTxt->setString(dmgMsg);

    if (enemies.empty()) {
        // All enemies are dead
        endMsg += "\n\nTotal EXP Gained: " + std::to_string(totalEXP);
                                endMsg += "\nTotal Gold Gained: " + std::to_string(totalGold);

                                playerWins = true;
                                winAlpha = 0;
    //                            if(textThread.joinable()){
    //
    //                                textThread.join();
    //                            }

        if(!debug){

            startWinThread();
        }

        return;
    }

//for (auto it = enemies.begin(); it != enemies.end(); ++it) {
//    // Process remaining enemies
//    // ...
//}
}

const void Battle::playerAttacks(){

            damage = 0;
            defendRoll = 0;
            alpha = 255;

            playerAccuracy = StateData::GetInstance()->getActiveCharacter()->getSkill(SKILLS::ACCURACY); //3 == ACCURACY
            enemyTotal = enemies[choice]->getSkill(SKILLS::DODGE); // 2 == DEFENCE

                int min = 1;
                int max = 5;

                int check = getRandomValue(min, max);

				if (getActiveCharacter()->skillCheck(enemies[choice], playerAccuracy, enemyTotal) || missCounter >= check) { //###########PLAYER HITS
					//HIT
					missCounter = 0;
					damage = StateData::GetInstance()->getActiveCharacter()->getDamage();
					defendRoll = enemies[choice]->getDefence();
                    int tot = 0;
                    if(damage >= defendRoll){

                        tot = damage - defendRoll;
                    }else{

                        tot = damage * 0.10;
                     }

                     if(tot <= 0){

                        tot = damage * 0.50;
                     }
					enemies[choice]->loseHP(abs(tot));
					std::string dmgMsg = "HIT for " + std::to_string(abs(tot)) + " damage!";

					std::string msg = "Corrupted " + enemies[choice]->getSavedFactionName() + " " + enemies[choice]->getName() + " HP: " + std::to_string(enemies[choice]->getHP()) + "/" + std::to_string(enemies[choice]->getHPMax());
                    enemyText[choice]->setString(msg);
					playerAttkTxt->setString(dmgMsg);
					//alpha = 255;

					//#####PLAYER WINS
					if (!enemies[choice]->isAlive()) {
						battleCloseMsg->setHeader("YOU DEFEATED!");
						gainGold = rand() & enemies[choice]->getLevel() * (10 + 1);
						totalGold += gainGold;
						StateData::GetInstance()->getActiveCharacter()->gainGold(gainGold);
						gainEXP = enemies[choice]->getExp();
						totalEXP += gainEXP;
						StateData::GetInstance()->getActiveCharacter()->gainXP(gainEXP);

                        getActiveCharacter()->gainRep(enemies[choice]->getSavedFaction(), 10);
                        endMsg += "Gold Gained: " + std::to_string(gainGold) + "\n";
                        endMsg += "EXP Gained: " + std::to_string(gainEXP) + "\n";

                        if(getData()->getActiveCharacter()->getExp() >= getData()->getActiveCharacter()->getExpNext()){

                            getData()->getActiveCharacter()->levelUp();
                            endMsg += "\nLevelled up!!\n";
						}

                        gainEXP = 0;
                        gainGold = 0;
						if(enemies.size() == 1){

                                active = false;

                            endMsg += "\n\nTotal EXP Gained: " + std::to_string(totalEXP);
                            endMsg += "\nTotal Gold Gained: " + std::to_string(totalGold);

                            playerWins = true;
                            winAlpha = 0;
//                            if(textThread.joinable()){
//
//                                textThread.join();
//                            }
                            if(debug == false){

                                startWinThread();
                            }
						}

                        int x = getRandomValue(0, 100);

                    ///    if(x >= 75){ ///TODO CHANGE TO DROP CHANCE VARIABLE

                            itemRoll();
                 ///       }

                        //HURR
                        battleCloseMsg->setText(endMsg);
						enemies.erase(enemies.begin() + choice);
						enemyText.erase(enemyText.begin() + choice);
//						int s = enemies.size();
//						std::cout << std::endl << std::to_string(s);
						for(size_t i = 0; i < enemies.size(); i++){

                            std::string msg = "Corrupted " + enemies[i]->getSavedFactionName() + " " + enemies[i]->getName() + " HP: " + std::to_string(enemies[i]->getHP()) + "/" + std::to_string(enemies[i]->getHPMax());
                            enemyText[i]->setString(msg);
                            //enemyText[i]->setString(enemies[i]->getName());
                            enemyText[i]->setColour(255, 0, 0, 0);
                            enemyText[i]->setPosition(GUI::p2pX(55), GUI::p2pY(15 + (i*5)));
                        }
					} //####END PLAYER WINS
				}
				else {
					//MISS
					playerAttkTxt->setString("Missed enemy!");
					alpha = 255;
					missCounter++;
					//cout << "MISSED ENEMY!\n\n";
				}

				battleGameTimer->start();
				moveTimer->restart();
				///endTurn = true;
//				playerTurn = false;
            //}
}

void Battle::followerAttacks(){

                if(debug){

                choice = getRandomValue(0, enemies.size()-1);

                ///** DEBUG START
                damage = 0;
                defendRoll = 0;
                alpha = 255;

                playerAccuracy = getActiveCharacter()->getActiveFollower()->getSkill(SKILLS::ACCURACY); //3 == ACCURACY
                enemyTotal = enemies[choice]->getSkill(SKILLS::DODGE); // 2 == DEFENCE

                int min = 1;
                int max = 5;

                int check = getRandomValue(min, max);

				if (getActiveCharacter()->getActiveFollower()->skillCheck(enemies[choice], playerAccuracy, enemyTotal) || missCounter >= check) { //###########PLAYER HITS
					//HIT
					missCounter = 0;
					damage = getActiveCharacter()->getActiveFollower()->getDamage();
					defendRoll = enemies[choice]->getDefence();
                    int tot = 0;
                    if(damage >= defendRoll){

                        tot = damage - defendRoll;
                    }else{

                        tot = damage * 0.10;
                     }

                     if(tot <= 0){

                        tot = damage * 0.50;
                     }
					enemies[choice]->loseHP(abs(tot));
					std::string dmgMsg = "HIT for " + std::to_string(abs(tot)) + " damage!";
                    std::cout << dmgMsg << std::endl;

					//#####PLAYER WINS
					if (!enemies[choice]->isAlive()) {

                            std::cout << "Enemy Killed" << std::endl;
//						gainGold = rand() & enemies[choice]->getLevel() * (10 + 1);
//						totalGold += gainGold;
//						///getActiveCharacter()->gainGold((gainGold/4));
						gainEXP = enemies[choice]->getExp();
						totalEXP += gainEXP;
						///getActiveCharacter()->gainXP(gainEXP / 4);
						getActiveCharacter()->getActiveFollower()->gainXP(gainEXP);

                        ///std::unique_lock<std::mutex> lock(StateData::GetInstance()->mtx);
                        if(getData()->getActiveCharacter()->getActiveFollower()->getExp() >= getData()->getActiveCharacter()->getActiveFollower()->getExpNext()){

                            getData()->getActiveCharacter()->getActiveFollower()->levelUp();
                            std::cout << "Follower levelled up!" << std::endl;
						}


                        gainEXP = 0;
                        gainGold = 0;
						if(enemies.size() == 1){

                            active = false;
                            playerWins = true;
                            winAlpha = 0;
                            enemies.clear();
						}

                        int x = getRandomValue(0, 100);

                        if(x >= 99){ ///TODO CHANGE TO DROP CHANCE VARIABLE

                           /// itemRoll();
                        }

					} //####END PLAYER WINS
				}
				else {
					//MISS
					///playerAttkTxt->setString("Missed enemy!");
					std::cout << "Follower missed!" << std::endl;
					///alpha = 255;
					missCounter++;
					//cout << "MISSED ENEMY!\n\n";
				}

				///battleGameTimer->start();

				///** DEBUG END

                playerTurn = false;
            }
}

void Battle::enemyAttacksAuto(){

if(enemies.size() <= 0){

        endTurn = true;
        textThreadRunning = false;
        active = false;
        return;
    }

    if(debug){

        if(true){   ///TODO FIX THIS
			//ENEMY TURN
			for (size_t i = 0; i < enemies.size(); i++){    //TIMER NEEDS TO GO AROUND HERE....

				enemyTotal = enemies[i]->getSkill(SKILLS::ACCURACY); //3 == ACCURACY
                combatTotal = getActiveCharacter()->getActiveFollower()->getSkill(SKILLS::DODGE);

				seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
             generator.seed(seed);
             std::uniform_int_distribution<int> playerTotalDistribution(1, combatTotal);
             combatRollPlayer = playerTotalDistribution(generator);

             std::uniform_int_distribution<int> enemyTotalDistribution(1, (enemyTotal));
             combatRollEnemy = enemyTotalDistribution(generator);


             int min = 1;
                int max = 5;

                int check = getRandomValue(min, max);

                //std::cout << "Enemy Miss counter: " << std::to_string(enemyMissCounter) << std::endl;

				if (enemies[i]->skillCheck(getActiveCharacter()->getActiveFollower(), enemyTotal, combatTotal) || enemyMissCounter >= check) {


                    enemyMissCounter = 0;
					damage = enemies[i]->getDamage();
					int defendRoll = getActiveCharacter()->getActiveFollower()->getDefence();
                    int tot = 0;
                    if(damage >= defendRoll){

                        tot = damage - defendRoll;
                    }else{

                        tot = damage * 0.10;
                     }

                     if(tot <= 0){

                        tot = damage * 0.4;
                     }
                     std::cout << "Enemy hit you for " << std::to_string(tot) << " damge!" << std::endl;
					StateData::GetInstance()->getActiveCharacter()->getActiveFollower()->loseHP(tot);
					//enemyMsg += "\n" + enemies[i]->getName() + " HIT for " + std::to_string(tot) + " damage! ";
					//alpha2 = 255;
					//enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
					if (!StateData::GetInstance()->getActiveCharacter()->getActiveFollower()->isAlive()) {
						//cout << "YOU DIED!\n\n";
                        std::cout << "Follower died!" << std::endl;
						getActiveCharacter()->loseRep(enemies[i]->getSavedFaction(), 2);   ///TODO: Does this need to be all factions that lose rep??
						active = false;
						getData()->refreshFollowerList = true;
						break;
					}
					///}
				}
				else {
					//MISS
					///enemyMsg += "\n" + enemies[i]->getName() + " Missed! ";
					///alpha2 = 255;
					///enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
					///cout << "ENEMY MISSED!\n\n";
					enemyMissCounter++;
					std::cout << "ENEMY missed" << std::endl;
				}

				//return;
			}
			//END TURN
			 endTurn = true;
		}
        playerTurn = true;
		return;
    }
    ///**DEBUG END
}

const void Battle::enemyAttacks(){

    std::string enemyMsg = "";

//    if(moveTimer->getTicks() < 500){
//
//        //endTurn = true;
//        playerTurn = false;
//        return;
//    }

    if(enemies.size() <= 0){

        endTurn = true;
        textThreadRunning = false;
        active = false;
        return;
    }


    if(!playerTurn && !escape && !enemyDefeated){
			//ENEMY TURN
			for (size_t i = 0; i < enemies.size(); i++){    //TIMER NEEDS TO GO AROUND HERE....
				//combatTotal = enemies[i]->getAccuracy() + StateData::GetInstance()->getActiveCharacter()->getDefence();
				//enemyTotal = enemies[i]->getAccuracy() / (double)combatTotal * 100;
				//playerTotal = StateData::GetInstance()->getActiveCharacter()->getDefence() / (double)combatTotal * 100;

				enemyTotal = enemies[i]->getSkill(SKILLS::ACCURACY); //3 == ACCURACY
                combatTotal = StateData::GetInstance()->getActiveCharacter()->getSkill(SKILLS::DODGE); // 2 == DEFENCE

				seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
             generator.seed(seed);
             std::uniform_int_distribution<int> playerTotalDistribution(1, combatTotal);
             combatRollPlayer = playerTotalDistribution(generator);

             std::uniform_int_distribution<int> enemyTotalDistribution(1, enemyTotal);
             combatRollEnemy = enemyTotalDistribution(generator);


             int min = 1;
                int max = 5;

                int check = getRandomValue(min, max);

				if (enemies[i]->skillCheck(getActiveCharacter(), enemyTotal, combatTotal) || enemyMissCounter >= check) {
					//HIT
					///int chancetoSave = getRandomValue(0, getActiveCharacter()->getAttribute(6)); //PLAYERS LUCK == 6

					///if(chancetoSave > 0){

                        //MISS
///					enemyMsg += "\n" + enemies[i]->getName() + " Missed! ";
///					alpha2 = 255;
///					enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
///					cout << "ENEMY MISSED!\n\n";
///					enemyMissCounter++;

					///}
					///else{
                    enemyMissCounter = 0;
					damage = enemies[i]->getDamage();
					int defendRoll = getActiveCharacter()->getDefence();
                    int tot = 0;
                    if(damage >= defendRoll){

                        tot = damage - defendRoll;
                    }else{

                        tot = damage * 0.10;
                     }

                     if(tot <= 0){

                        tot = damage * 0.4;
                     }
					StateData::GetInstance()->getActiveCharacter()->loseHP(tot);
					enemyMsg += "\n" + enemies[i]->getName() + " HIT for " + std::to_string(tot) + " damage! ";
					alpha2 = 255;
					enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
					if (!StateData::GetInstance()->getActiveCharacter()->isAlive()) {
						//cout << "YOU DIED!\n\n";

						getActiveCharacter()->loseRep(enemies[i]->getSavedFaction(), 10);   ///TODO: Does this need to be all factions that lose rep??
						playerDefeated = true;
						break;
					}
					///}
				}
				else {
					//MISS
					enemyMsg += "\n" + this->enemies[i]->getName() + " Missed! ";
					alpha2 = 255;
					enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
					///cout << "ENEMY MISSED!\n\n";
					enemyMissCounter++;
				}
			}

            if(!debug){

            std::string msg = "You are attacked.\n\n";
            msg += "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHPMax());
            getMainText()->setString(msg, true);
            }
			//END TURN
			 endTurn = true;

			 moveTimer->restart();
		}
}

void Battle::updateEvents(SDL_Event& e){

    menu->updateEvents(e);
    enemyMenu->updateEvents(e);

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){

            if(enemyMenu->getActive()){

                menu->setActive(true);
                enemyMenu->setActive(false);
            }
            else{

                //RUN AWAY CODE
                runAway();
            }

            return;

    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){
        ///TODO: = Can check for key repeat and if quick battle is unlocked turn it off
        if(!endTurn){

            runMenuSelection();
        }
        if(endTurn && moveTimer->getTicks() > moveDelay){

                endTurn = false;
                playerTurn = true;
                menu->setActive(true);
            if(!textThreadRunning){

                    if(!winThreadRunning && !playerWins && !escape && !textThreadRunning){

                        if(enemyAttkTxt->getString() != "" && playerAttkTxt->getString() != ""){

                            startTextThread();
                        }
                        return;
                    }
                    else if(!winThreadRunning){

                            if(playerWins || escape){

                               // Engine::GetInstance()->PopState();
                                Engine::GetInstance()->PopState();
                                return;
                            }
                    }
                //getDynamicText()->setString("Choose action: ");
            }
        }
    }

    if(backButton->isActive() && backButton->isPressed(e.button) && playerTurn){

        runAway();

        return;
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){

        if(menu->isSelected()){

            runMenuSelection();

            return;
        }

        if(enemyMenu->isSelected()){

            runMenuSelection();

            return;
        }

        if(endTurn && moveTimer->getTicks() > moveDelay){

                 endTurn = false;
                playerTurn = true;
                menu->setActive(true);
            if(!textThreadRunning){

                    if(!winThreadRunning && !playerWins && !escape && !textThreadRunning){

                        if(enemyAttkTxt->getString() != "" && playerAttkTxt->getString() != ""){

                            startTextThread();
                        }
                        return;
                    }
                    else if(!winThreadRunning){

                            if(playerWins || escape){

                               // Engine::GetInstance()->PopState();
                                Engine::GetInstance()->PopState();
                                return;
                            }
                    }
                //getDynamicText()->setString("Choose action: ");
            }

            std::cout << "Must be...";
        }
    }



    //std::cout << "THE CHOICE IS CURRENTLY: " << std::to_string(choice) << "\n";
    if(e.type == SDL_MOUSEMOTION){

//        int x, y;
//        SDL_GetMouseState(&x, &y);
//        SDL_Rect r;

        for(size_t i = 0; i < enemies.size(); i++){


       /// r = enemyText[i]->getPositionRect();

        if(battleEyes->checkBounds(enemyText[i])){

                std::string msg = "HP: " + std::to_string(enemies[i]->getHP()) + "/" + std::to_string(enemies[i]->getHPMax())
                    + "\nAttack: ????\nDefence: ????";
                msg += "\nSkills: \nDefence Sk: " + std::to_string(enemies[i]->getSkill(2));
                msg += "\nMelee Sk: " + std::to_string(enemies[i]->getSkill(0));
                battleEyes->setDisplayText(msg);
                battleEyes->update();
                battleEyes->setHidden(false);

                return;
           }
           else{

                battleEyes->setHidden(true);
           }
        }
    }
}

void Battle::runAway(){

     /** THIS IS THE RUN AWAY FROM BATTLE CODE         */




                    if(enemyMenu->getActive()){

                        menu->setActive(true);
                        enemyMenu->setActive(false);

                        return;
                    }

                    int coinToss = rand() % 2 + 1;
                        if (coinToss == 2){
                            //getDynamicText()->setString("Ran away!!");
                            escape = true;
                            //return;
                        }
                        else{
                            escape = false;
                        }

                    if(!escape){
                        alpha = 255;
                        playerAttkTxt->setString("Failed to escape");
                        playerTurn = false;
                        enemyAttacks();

                        backButton->setActive(false);
                        return;
                    }
                    else{

                            if(textThread.joinable()){

                                textThread.join();
                            }

                        alpha = 255;
                        getDynamicText()->setString("Got away safely");
                        ///getDynamicText()->render();
                        //SDL_Delay(100);
                      //  Engine::GetInstance()->PopState();
                        Engine::GetInstance()->PopState();
                        return;
                    }

                //}


                /*  END OF RUNNING FROM BATTLE  */
}

void Battle::runMenuSelection(){

            if(menu->isSelected() && playerTurn){


        ///RUN MENU OPTIONS START
        int choice = menu->getChoice();

        if(menu->getChoice() == 0){     ///ATTACK

            std::vector<std::string> ops;

            for(size_t i = 0; i < enemies.size(); i++){

                ops.push_back(enemies[i]->getName());
            }

            enemyMenu->setMenuOptions(ops, true);
            enemyMenu->setActive(true);
            menu->setActive(false);

            if(enemies.size() > 1){

                return;
            }

            }
        }

        if(menu->getChoice() == 1){ ///DEFEND

            std::cout << "Defence does nothing\n";
        }

        if(menu->getChoice() == 2){ ///MAGIC

            if(playerTurn){

                playerTurn = false;
                magicAttack();
            }
            //menu->setActive(false);
            if(enemies.size() > 1){

                return;
            }
        }

        if(menu->getChoice() == 3){ ///THIRD EYE

            std::cout << "Third eye does nothing\n";
        }

        if(enemyMenu->isSelected() && playerTurn){

            playerTurn = false;
            enemyMenu->setActive(false);
            choice = enemyMenu->getChoice();
            ///THIS GOES IN THE SELECTED ENEMY
            playerAttacks();
            //TODO: Should go below so defence, items etc work
            menu->setActive(true);
        }
            ///END RUN MENU s
}

void Battle::render(){

    if(debug){

        return;
    }

    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    getMainText()->render();

    SDL_Rect bgR1 = {0, 0, GUI::p2pXi(3), GUI::p2pYi(100)};
    SDL_Rect bgR2 = { GUI::p2pXi(97), 0, GUI::p2pXi(3), GUI::p2pYi(100) };
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), bg2->getTexture(), NULL, &bgR2);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), bg1->getTexture(), NULL, &bgR1);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 192, 192, 192, 255);
    SDL_RenderDrawLine(Engine::GetInstance()->GetRenderer(), GUI::p2pX(3), 0, GUI::p2pX(3), GUI::p2pY(100));
    SDL_RenderDrawLine(Engine::GetInstance()->GetRenderer(), GUI::p2pX(97), 0, GUI::p2pX(97), GUI::p2pY(100));
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 255, 0, 255);


    getEnemyText()->render();

    worldTimerText->render();

    if(playerWins){

        if(!battleCloseMsg->getActive()){
            //SDL_Delay(600);
            endGameTimer->restart();
            battleCloseMsg->setAlpha(winAlpha);
            SDL_SetTextureAlphaMod(battleCloseMsg->getTexture(), winAlpha);
            SDL_SetTextureAlphaMod(battleCloseMsg->getHeaderTexture(), winAlpha);
            battleCloseMsg->setActive(true);
        }

        int w, h;
        SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &w, &h);
//        SDL_Rect overlay = { 0, 0, w, h };
//        SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);
//        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 211, 211, 211, winAlpha);
//        SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &overlay);
//        SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_NONE);
        battleCloseMsg->render();

        if(winAlpha != 255){

            endTurn = false;
        }
        else{

            endTurn = true;

        }
        endGameTimer->restart();
        return;
    }

    if(alpha2 > 10 && moveTimer->getTicks() > moveDelay){
        SDL_SetTextureAlphaMod(enemyAttkTxt->getTexture(), alpha);
        enemyAttkTxt->render();
    }
    if(alpha > 10){

        SDL_SetTextureAlphaMod(playerAttkTxt->getTexture(), alpha);
        playerAttkTxt->render();
    }

    if(endTurn || menu->getActive()){
        menu->render();
    }
    else if(enemyMenu->getActive()){
        enemyMenu->render();
    }

    for(size_t i = 0; i < enemies.size(); i++){

        enemyText[i]->render();
    }

    battleEyes->render();

    backButton->renderButtons();
}


void Battle::itemRoll(){


            double baseSuccessRate = 0.2; //Base success rate of 20%
            double successRateModifier = static_cast<double>(getActiveCharacter()->getLevel()) / 10.0; //Increase in success rate per skill point difference

            //calc probability of success rate
            double probability = baseSuccessRate + (successRateModifier * 1/*ONE TO CHANGE BASED ON ???*/);


            //generate a random number between 0 and 1 to determine success
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0, 1);
            double randomValue = dis(gen);


    ///TODO THIS NEEDS TO BE IT'S OWN FUNCTION!!!!
						//ITEM ROLL
						seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

                        generator.seed(seed);

                        std::uniform_int_distribution<int> itemDistribution(1, 100);
                        int r = itemDistribution(generator);


						//int r = rand() % 100 + 1;
						int rarity = -1;
						if (r <= 70) {
							//GET ITEM
							rarity = 0; //COMMON ITEM
							//int newRoll = rand() % 100 + 1;
                        }
                        else if (r > 70 && r <= 80) {
								rarity = 1; //UNCOMMON ITEM
                        }

                        else if(r > 80 && r <= 85 && StateData::GetInstance()->getActiveCharacter()->getLevel() > 20) {
                            rarity = 2; //RARE
                        }

                        else if(r > 85 && r < 95 && StateData::GetInstance()->getActiveCharacter()->getLevel() > 35){
                            rarity = 3;
                        }
                        else if(r > 95 && StateData::GetInstance()->getActiveCharacter()->getLevel() >= 50){

                            rarity = 4;
                        }

                        seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
                        generator.seed(seed);
                        r = itemDistribution(generator);

                        int low = getActiveCharacter()->getLevel() - 1;
                        if(low <= 0){

                            low = 1;
                        }
                        int high = getActiveCharacter()->getLevel() + 2;
                        int lvl = getRandomValue(low, high);

							if (r >= 50) {

								if (r <= 75) {
///									int lvl = StateData::GetInstance()->getActiveCharacter()->getLevel();
									Weapon tempW(lvl, rarity);
									auto tempWe = make_shared<Weapon>(tempW);
									StateData::GetInstance()->getActiveCharacter()->addItem(tempWe);
									endMsg += "\nWeapon dropped: ";
									endMsg +=  tempWe->getName() + " " + tempWe->getTypeStr() + "\n";
								}
								else {
									Armour tempA(lvl, rarity);
									auto tempAw = make_shared<Armour>(tempA);
									StateData::GetInstance()->getActiveCharacter()->addItem(tempAw);
									endMsg += "\nArmour dropped: ";
									endMsg += tempAw->getName() + " " + tempAw->getTypeStr() + "\n";
								}
							}
							else{

                                ///TODO
                                Resource tempr(lvl, rarity);
                                //tempr.setName("Scrap Metal");
                                tempr.setItemType(itemTypes::RESOURCE);
                                auto tempRe = std::make_shared<Resource>(lvl, rarity);
                                StateData::GetInstance()->getActiveCharacter()->addItem(tempRe);
                                endMsg += "\nResource dropped: ";
                                endMsg += tempRe->getTypeStr() + " " + tempRe->getName() + "\n";


                                ///DEBUG:: MOVE KEY TO IT'S OWN ROLL, MAKE A FUNCTION THAT TAKES A FLOAT AS PERCENT CHANCE AND RETURNS TRUE/FALSE FOR DROP
                                 Key tempk(lvl, rarity);
                                //tempr.setName("Scrap Metal");
                                tempk.setItemType(itemTypes::KEY);
                                auto tempKe = std::make_shared<Key>(lvl, rarity);
                                StateData::GetInstance()->getActiveCharacter()->addItem(tempKe);
                                endMsg += "\Key dropped: ";
                                endMsg += tempKe->getName() + " " + tempKe->getTypeStr() + "\n";
							}
}
