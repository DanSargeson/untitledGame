#include "State.h"
#include "Engine.h"
#include "NPC.h"
#include "stdafx.h"
#include "Battle.h"
#include "Resource.h"
#include "Key.h"

//Input* Input::s_Instance = nullptr;
StateData* StateData::s_Instance = nullptr;
std::atomic<bool> StateData::battleThreadRunning = false;
std::atomic<bool> StateData::battleThreadPaused = false;

void StateData::initFonts(){

    try{

        ///TODO:- Does nothing
        font = TTF_OpenFont("Fonts/Roboto.ttf", 24);

    }
    catch(std::exception &e){

        std::ofstream outFile;

        outFile.open("errorLog.txt");

        if(outFile.is_open()){

            outFile << e.what() << std::endl;

            outFile.close();
        }
    }
}

State::State() {

    if(timerText == nullptr){

        timerText = std::make_shared<GUI::Text>();
        timerText->setPosition(GUI::p2pX(55), GUI::p2pY(20));
    }
    this->quit = false;
    keyTimeMax = 0.5f;
    keyTime = 0.f;
    getData()->mainText = std::make_shared<GUI::Text>(5, 5, 89, 60, true);

    if(getDynamicText() == nullptr){

    getData()->dynamicText = std::make_shared<GUI::Text>(false);
    getDynamicText()->setPosition(GUI::p2pX(20), GUI::p2pY(50));
    getDynamicText()->clearText();
    }

    if(getEnemyText() == nullptr){

    getData()->enemyText = std::make_shared<GUI::Text>(false);
    getEnemyText()->setPosition(GUI::p2pX(20), GUI::p2pY(50));
    getEnemyText()->clearText();
    getEnemyText()->setColour(255, 0, 0, 0);
    }

    if(getFollowerText() == nullptr){

        getData()->followerScreenText = std::make_shared<GUI::Text>(false);
        getFollowerText()->setPosition(GUI::p2pX(55), GUI::p2pY(40));
        getFollowerText()->setColour(0, 255, 0, 0);
    }
//    getFollowerText()->setString("");

    getMainText()->setFontSize(20);
    getDynamicText()->setFontSize(20);
    getEnemyText()->setFontSize(20);
    getFollowerText()->setFontSize(20);

    getEnemyText()->setPosition(GUI::p2pX(55), GUI::p2pY(40));
    getDynamicText()->setPosition(GUI::p2pX(55), GUI::p2pY(30));

    menu = std::make_shared<GUI::Menu>();

    unsigned int charSize = GUI::calcCharSize(125);
    backButton = std::make_shared<GUI::Button>(12.f, 59.5f, 11.8f, 5.1f, charSize);
    backButton->setBackgroundTexture("Assets/Background/button2.png");
    backButton->setRenderText("Back");
    backButton->setActive(false);

    confirmationBox = std::make_shared<GUI::textBox>();
    confirmationBox->setConfirm(true);
    confirmationBox->setActive(false);
    confirmationBox->setSize(50, 20);
    confirmationBox->centreTextBox();
    confirmationBox->setHeader("Exit to main menu");
    confirmationBox->setText("Return to title screen?");
    confirmationBox->setAlpha(200);

    refreshGUI();
};

State::~State(){

    //getData()->dynamicText->clearText();
    //getData()->enemyText->clearText();
//    if(getActiveCharacter() != nullptr){
//
//        getMainText()->setString(getActiveCharacter()->getStatsAttributeScreen(), true, GUI::p2pY(120));
//    }
}

void State::setData(StateData& stateData){

    StateData::GetInstance()->currentState = 0;
}

bool State::getQuit(){

    return this->quit;
}

void State::refreshGUI(){

        getData()->mainText->refreshGUI();
        getDynamicText()->refreshGUI();

        //getData()->enemyText = std::make_shared<GUI::Text>();
        getEnemyText()->refreshGUI();
        getEnemyText()->setPosition(GUI::p2pX(20), GUI::p2pY(50));
        getDynamicText()->setPosition(GUI::p2pX(20), GUI::p2pY(50));

        getMainText()->setFontSize(20);
        getDynamicText()->setFontSize(20);
        getEnemyText()->setFontSize(20);
        //getEnemyText()->clearText();

        getEnemyText()->setPosition(GUI::p2pX(55), GUI::p2pY(40));
        getDynamicText()->setPosition(GUI::p2pX(55), GUI::p2pY(30));

        initButtons();
        menu->refreshGUI();

        confirmationBox->refreshGUI();
        confirmationBox->setSize(50, 25);
        confirmationBox->centreTextBox();
        confirmationBox->setAlpha(200);

    //TODO Add buttons & menu to state to allow GUI refresh.... OR override
}

void State::initButtons(){

    unsigned int charSize = GUI::calcCharSize(125);
    backButton = std::make_shared<GUI::Button>(12.f, 59.5f, 11.8f, 5.1f, charSize);
    backButton->setRenderText("Back");
    backButton->setBackgroundTexture("Assets/Background/button2.png");
 ///   backButton->setActive(false);
}


const bool State::getKeyTime(){

    if(keyTime > keyTimeMax){

        keyTime = 0.f;

        return true;
    }

    return false;
}


void StateData::push_state(std::shared_ptr<State> s){

    this->states->push_back(s);
    currentState++;
}

void StateData::pop_state(){

    states->pop_back();
    currentState--;
}

int State::loadRandomFaction(){

     /*** BEGIN RANDOM VALUE **/
               std::vector<int> numbers = {2, 3, 4};
                int randomValue = getRandomValue(numbers[0], numbers.back());
                /*** END RANDOM VALUE **/


                if(getData()->getActiveCharacter()->getRep(randomValue) >= 255){

                ///TODO Bring this back, this is unlocking the secondary
                    switch(randomValue){

                        case 2:
                            ///RED
                            if(getData()->getActiveCharacter()->getRep(4) < 100){

                                numbers.push_back(7);   ///YELLOW Broker a peace between green + red
                            }
                            break;

                        case 3:
                            ///BLUE
                            if(getData()->getActiveCharacter()->getRep(2) < 110){

                                numbers.push_back(6);   ///Magenta brokeer a peace between blue + red
                            }

                            break;

                        case 4:
                            ///GREEN;
                            if(getData()->getActiveCharacter()->getRep(3) < 100){

                                numbers.push_back(5);   ///AQUA broker peace between blue + green
                            }
                            break;
                    }

                    int randomIndex = getRandomValue(0, numbers.size() - 1);
                    randomValue = numbers[randomIndex];
                }

                return randomValue;
}

void State::updateButtons(){

    for(auto &it : mButtons){

        if (it.second != nullptr && it.second->isActive()) {

            it.second->update();
        }


        //TODO: REMOVE ALL RAW POINTERS...
    }
}

void State::update(const float &dt){

    if(getData()->battleThreadRunning){

        float t = (getData()->followerTimer->getTicks() / 1000.f);
        std::stringstream ss;
        ss << t;
        std::string m = ss.str();

        timerText->setString(m);
    }
}

void State::updateEvents(SDL_Event& e){


    //updateButtons();
    /*if (backButton != nullptr && backButton->isActive()) {

        backButton->update();
    }*/

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){

        std::cout << std::to_string(Engine::GetInstance()->getCurrentState()) << std::endl;
        if(Engine::GetInstance()->getCurrentState() == 1){

            confirmationBox->setActive(true);
            if(getData()->battleThreadRunning.load() /*&& !getData()->battleThreadPaused.load()*/){
                //getData()->battleThreadPaused.store(true);
                exitingBattles = true;
            }
            else{

                ///TODO
                confirmationBox->setActive(true);
                //Engine::GetInstance()->PopState();
            }
        }
        else{

            Engine::GetInstance()->PopState();
        }


        return;
    }

    /*if(e.type == SDL_MOUSEBUTTONDOWN){


        if(backButton->isActive() && backButton->isPressed(e.button)){


            backButton->setActive(false);
            Engine::GetInstance()->PopState();

            return;
        }
    }*/

//    if(e.type == SDL_MOUSEMOTION){
//
//        if(!SDL_ShowCursor(SDL_QUERY)){
//
//            SDL_ShowCursor(SDL_ENABLE);
//        }
//    }
}

void StateData::startBattleThread()

    {

    std::lock_guard<std::mutex> lock(mtx);
    if(!battleThreadRunning){

      battleThreadRunning.store(true);
      battleThread = std::thread(&StateData::startFollowerAction, this);
    }
}


///TODO: Need a folower action manager function which determines follower type and runs appropriate thing.. Battle/Search for items etc.

void StateData::startFollowerAction(){

    int type = getActiveCharacter()->getActiveFollower()->getType();

    switch(type){

    case NPC_TYPE::ALCHEMIST:   ///ALCHEMIST IS ACTUALLY DOCTOR...(search for health)
        dynamicText->setString("Search for potions here");
        battleThreadRunning.store(false);
        battleThread.detach();
        break;

    case NPC_TYPE::SCOUT:
        runFollowerBattles();
        break;


    case NPC_TYPE::BARD:
        dynamicText->setString("This is BARD npc type...");
        battleThreadRunning.store(false);
        battleThread.detach();
        break;

    case NPC_TYPE::BLACKSMITH:  ///SEARCH FOR ORES
        dynamicText->setString("This is BLACKSMITH npc type...");
        battleThreadRunning.store(false);
        battleThread.detach();
        break;

    case NPC_TYPE::COOK:        ///COOK IS LOCKSMITH... (SEARCH FOR KEYS)
        dynamicText->setString("This is COOK npc type...");
        battleThreadRunning.store(false);
        battleThread.detach();
        break;

    case NPC_TYPE::INNKEEPER:
        dynamicText->setString("This is INNKEEPER npc type...");
        battleThreadRunning.store(false);
        battleThread.detach();
        break;

    case NPC_TYPE::LIBRARIAN:   ///THIS IS ALCEMIST... (Search for potions)
        dynamicText->setString("This is LIBRARIAN npc type...");
        battleThreadRunning.store(false);
        battleThread.detach();
        break;

    default:
        battleThreadRunning.store(false);
        battleThread.detach();
        break;
    }
}

void StateData::runFollowerBattles(){

        std::cout << "TOP OF RUN FOLLOWER BATTLE" << std::endl;


        b = std::make_shared<Battle>(true);
        battleCounter = 0;

        bool death = false;
        int loopCounter = 0;

        while (battleThreadRunning.load()) {

                std::unique_lock<std::mutex> lock(mtx);

                if(battleThreadPaused.load()){

                    followerTimer->pause();
                    cv.wait(lock, [this]{return !battleThreadPaused.load();});
                    followerTimer->unpause();
                }


                ///Replaces the sleep_for functionality...
                if(cv.wait_for(lock, std::chrono::milliseconds(1000), [this] { return !battleThreadRunning; })){
                    break;
                }
        bool battleFinished = false;
        int timeToAdventure = 30000;  ///

        if(followerTimer->getTicks() <= timeToAdventure){  ///

        int test = getActiveCharacter()->getActiveFollower()->getLevel();

            if(getActiveCharacter()->getActiveFollower()->isAlive()){

                    if(b->getEnemies().size() <= 0){

                    std::string msg = "Follower defeated all enemies. New battle begins!";
                    battleCounter++;
                    std::cout << msg << std::endl;
                    std::cout << std::to_string(battleCounter) << std::endl;
                    if(followerTimer->getTicks() <= timeToAdventure){

                        b->spawnEnemies();
                    }
                }
                else{
                        if (battleCounter >= 5) {
                            battleFinished = true;
                            battleThreadRunning.store(false);

                            return;
                        }
                    b->followersAutoBattle();
                }
            }

                if(!getActiveCharacter()->getActiveFollower()->isAlive()){   ///FOLLOWER DIED
                    battleThreadRunning.store(false);
                    cv.notify_all();
                    battleFinished = true;
                    followerTimer->stop();
                    battleCounter = 0;
                    std: string s = followerScreenText->getString();
                    s += "\nA brave soul returns to the void. Follower Lost.";
                    followerScreenText->setString(s, true);
                    getActiveCharacter()->removeFollower();
                    battleCounter++;
                    death = true;
                    std::cout << "THIS IT THE FOLLOWE DIES" << std::endl;
                    ///return;
                }
            }   ///ND IF TICKS < timetoAdventure
            else{       ///TIME RAN OUT (BattleCounter

                    ///EXIT BATTLE
                    //battleCounter++;
                    battleThreadRunning.store(false);
                    battleFinished = true;
                    followerTimer->stop();
                    std::string s = "";
                    if(followerScreenText->getString() != ""){

                        s = followerScreenText->getString();
                    }
                    std::string msg = "\nTime ran out. Your follower won " + std::to_string(battleCounter);
                    msg += (battleCounter == 1) ? " battle" : " battles!";
//                    if(battleCounter == 0){
//
//                        msg += " Try using EXP potions to level the follower!";
//                    }
                    s += msg;
                    followerScreenText->setString(s, true);
                    //HITS AFTER FOLLOWER DIES...
                    std::cout << "TIME RAN OUT: BROKE FIRST LOOP" << std::endl;
                    battleCounter = 0;
                }
        //HITS HERE WHEN FOLLOWER FIRST DIES>......
                loopCounter++;
                if (loopCounter == 2) {

                    int check = 0;
                }
                std::cout << std::to_string(loopCounter) << " LOOP OF BATTLETHREADRUNNING!" << std::endl;
            //}
        }

        std::cout << "EXITING BATTLE THREAD" << std::endl;
        followerTimer->stop();
}

void StateData::clearCharacters(){

    ///characters.clear();
}

int State::getRandomValue(int low, int high){

    // Use std::random_device to obtain a seed for the random number generator
                std::random_device rd;

                // Use std::mt19937 as the random number generator
                std::mt19937 gen(rd());

                // Use std::uniform_int_distribution to generate random indices
                std::uniform_int_distribution<> dis(low, high);

                // Generate a random index
                int randomIndex = dis(gen);

                // Access the corresponding element in the set
//                int randomValue = numbers[randomIndex];

                return randomIndex;
}

void State::loadCharacters(){
    std::string fileName = "characters.txt";
    ifstream inFile(fileName);
    StateData::GetInstance()->characters.clear();


    string name = "";
    int disTravel = 0;
    int gold = 0;
    int level = 0;
    int exp = 0;
    //int str = 0;
    //int vit = 0;
    //int dex = 0;
    //int intel = 0;
    int hp = 0;
    int stamina = 0;
    int statPoints = 0;
    int skillPoints = 0;
    int corrupt = 0;

	//ITEMS
	Inventory tempItems;

	int itemType = -1;
	int defenceMin = 0;
	int defenceMax = 0;
	int type = 0;
	int damageMin = 0;
	int damageMax = 0;
	string itemName = "";
	int itemLevel = 0;
	int buyValue = 0;
	int sellValue = 0;
	int rarity = 0;

	//Factions
	int black = 0;
    int white = 0;
    int red = 0;
    int orange = 0;
    int yellow = 0;
    int green = 0;
    int blue = 0;
    int indigo = 0;
    int violet = 0;

    int vit;
    int str;
    int dex;
    int agi;
    int intel;
    int charis;
    int luck;

    int attriPoint;

    string line = "";
    stringstream strs;

    ///std::string followerName = "";
    int followerType = 0;
	int followerFaction = 0;
	int followerLevel = 0;
	int followerEXP = 0;
	int followerHP = 0;


    if(inFile.is_open()){
		while (getline(inFile, line)) {
			strs.str(line);
			strs >> name;
			strs >> disTravel;
			strs >> level;
			strs >> hp;
			strs >> exp;
			strs >> gold;
			strs >> corrupt;
			strs >> vit;
			strs >> str;
			strs >> dex;
			strs >> agi;
			strs >> intel;
			strs >> charis;
			strs >> luck;
			strs >> attriPoint;

			auto temp = std::make_shared<Player> (name, disTravel, gold, level, exp,
				vit, str, dex, agi, intel, charis, luck, hp,
                corrupt, attriPoint, true);

            ////create components here...
            temp->createComponents();
            temp->setAttributes(vit, str, dex, agi, intel, charis, luck);
            temp->setAttributePoints(attriPoint);
            temp->calculateSkills();
            temp->updateStats(false);
            temp->setHP(hp);
            temp->setExp(exp);
			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);

			while (

				strs >> black
				>> white
				>> red
				>> orange
				>> yellow
				>> green
				>> blue
				>> indigo
				>> violet
				)

				///HERE FAC
				temp->loadFactions(black, white, red, orange, yellow, green, blue, indigo, violet);

            strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);

			while (strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> damageMin
				>> damageMax
				>> type) {

				if (itemType == itemTypes::WEAPON) {
					Weapon activeWeapon(type, damageMin, damageMax, itemName, itemLevel, 0, 0, rarity);
					auto awv = make_shared<Weapon>(activeWeapon);
					temp->setWeapon(awv);
				}
			}


			//ACTIVE ITEMS
			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);
			while (strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> defenceMin
				>> defenceMax
				>> type) {
				if (itemType == itemTypes::ARMOUR) {
					Armour activeArm(type, defenceMin, defenceMax, itemName, itemLevel, 0, 0, rarity);
					auto avv = make_shared<Armour>(activeArm);
					int type = avv->getType();

					switch (type) {
					case HEAD:
						temp->setArmourHead(avv);
						break;

					case CHEST:
						temp->setArmourChest(avv);
						break;

					case ARMS:
						temp->setArmourArms(avv);
						break;

					case LEGS:
						temp->setArmourLegs(avv);
						break;

					default:
						break;
					}
				}

			}

			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);
			while (

				strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> damageMin
				>> damageMax
				>> type
				) {

				Weapon tempWeapon(type, damageMin, damageMax, itemName, itemLevel, 0, 0, rarity);
				auto wv = make_shared<Weapon>(tempWeapon);
				tempItems.addItemVectorSmart(wv);
				temp->addItem(wv);
			}


			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);
			while (
				strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> defenceMin
				>> defenceMax
				>> type
				) {
				Armour tempArmour(type, defenceMin, defenceMax, itemName, itemLevel, 0, 0, rarity);
				auto av = make_shared<Armour>(tempArmour);
				tempItems.addItemVectorSmart(av);
				temp->addItem(av);
			}
			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);

			while (
				strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> defenceMin
				>> defenceMax
				>> type
				) {
				Resource tempResource(type, defenceMin, defenceMax, itemName, itemLevel, 0, 0, rarity);
				auto rv = make_shared<Resource>(tempResource);
				tempItems.addItemVectorSmart(rv);
				temp->addItem(rv);
			}
			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);

			while (
				strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> type
				) {
				Key tempKey(type, itemName, itemLevel, 0, 0, rarity);
				auto kv = make_shared<Key>(tempKey);
				tempItems.addItemVectorSmart(kv);
				temp->addItem(kv);
			}
			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);

			while (
				strs >> followerType
				>> followerLevel
				>> followerFaction
				>> followerHP
				>> followerEXP
				) {
				//NPC tempFollower(followerName, followerLevel, followerFaction);
				//tempFollower.setName(followerName);
				auto av = make_shared<NPC>(followerType, followerLevel, followerFaction);
                av->createComponents();
                av->assignRandomAttributes(level, true);
                av->calculateSkills();
				av->setExp(followerEXP);
				av->setHP(followerHP);
				temp->addFollower(av);
			}

                ///TODO: Check this...
				///temp->setInv(tempItems);
                StateData::GetInstance()->characters.push_back(temp);

				///cout << "Character: " << temp->getName() << " loaded" << "\n";
				//cout << "Loaded Inv: " << temp.getInvAsString() << "\n";
				//cout << "tempItems: " << tempItems.getInvAsString() << "\n";
				strs.clear();
               /* for(int i = 0; i < characters.size(); i++){
                    cout << this->characters[i].getStatsAsString() << endl;
					cout << "Loaded Character: " << this->characters[i].getName() << endl;
                }*/

            }
    }
    else{

        Engine::GetInstance()->PopState();

        return;
    }
    inFile.close();

    if(StateData::GetInstance()->characters.size() < 0){
        throw "ERROR LOADING FILE!";
    }
}

void State::saveCharacters()
{

    std::string fileName = "characters.txt";

    std::ofstream outFile(fileName);

 //   void Game::saveCharacters(){
    if(outFile.is_open()){
        for(unsigned i = 0; i < StateData::GetInstance()->characters.size(); i++){
            outFile << StateData::GetInstance()->characters[i]->getStatsAsString() << " ";
			outFile << getData()->characters[i]->saveAttributes() << "\n";
			outFile << StateData::GetInstance()->characters[i]->getFactionStrSave() << "\n";
			outFile << StateData::GetInstance()->characters[i]->getEquippedWeapon() << "\n";
			outFile << StateData::GetInstance()->characters[i]->getEquippedArmour() << "\n";
			outFile <<	StateData::GetInstance()->characters[i]->getInvAsStringSave() << "\n";
			outFile << StateData::GetInstance()->characters[i]->getFollowersStrSave() << "\n";
		}
    }

    outFile.close();
    //* NEW TEST *//

    std::ofstream newOut("characters2.save");




    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert to local time
///    std::tm* localTime = std::localtime(&currentTime);

    if(newOut.is_open()){

        for(unsigned i = 0; i < StateData::GetInstance()->characters.size(); i++){

            newOut << StateData::GetInstance()->characters[i]->getStatsAsString() << " ";
			newOut<< getData()->characters[i]->saveAttributes() << "\n";
			newOut << StateData::GetInstance()->characters[i]->getFactionStrSave() << "\n";
			newOut << StateData::GetInstance()->characters[i]->getEquippedWeapon() << "\n";
			newOut << StateData::GetInstance()->characters[i]->getEquippedArmour() << "\n";
			newOut << StateData::GetInstance()->characters[i]->getInvAsStringSave() << "\n";
			newOut << StateData::GetInstance()->characters[i]->getFollowersStrSave() << "\n";
			///newOut << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
        }
    }

    newOut.close();
}


void StateData::createCamera(int maxSize){

    int h = 0;
    int w = 0;

    SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &w, &h);

    this->camera = std::make_unique<Camera>(0,0,w,h, maxSize);
}

void StateData::moveCamera(int direction, int axis){


    switch(direction){

    case LEFT:
        camera->moveCamera(LEFT, axis);
        break;

    case RIGHT:
        camera->moveCamera(RIGHT, axis);
        break;

    case UP:
        camera->moveCamera(UP, axis);
        break;

    case DOWN:
        camera->moveCamera(DOWN, axis);
        break;

    default:
        camera->moveCamera(FREEZE, axis);
        break;
    }

}

void StateData::moveCam2(int dir, float time)
{
    switch(dir){

    case LEFT:
        camera->moveCam2(LEFT, time);
        break;

    case RIGHT:
        camera->moveCam2(RIGHT, time);
        break;

    case UP:
        camera->moveCam2(UP, time);
        break;

    case DOWN:
        camera->moveCam2(DOWN, time);
        break;

    default:
        camera->moveCam2(FREEZE, time);
        break;
    }
}

void StateData::stopCam2(int dir, float time){

    switch(dir){

    case LEFT:
        break;
    }
}

void StateData::setCamPosition(int x, int y){

    camera->setPosition(x, y);
}

SDL_Rect StateData::getCamera(){

    return camera->getCamera();
}

void StateData::updateCamera(float dt){

    this->camera->update(dt);
}


