#include "Game.h"
#include "Engine.h"
#include "Event.h"
#include "Settings.h"
#include "Battle.h"
#include "FactionEncounter.h"
#include "RandomEncounter.h"
#include "GraphicRandomEncounter.h"
#include "IncreaseAttributes.h"
#include "CharacterMenu.h"
#include "FollowerMenu.h"
#include "LoadGame.h"

Game::Game() : State(){


  ///TODO: Game timer should be loaded in mainMenu....
  getData()->worldTimer->start();

  ///  Mix_HaltMusic();

//  b = std::make_shared<Battle>(true);

    worldRect = { GUI::p2pXi(85), GUI::p2pYi(7), 60, 60 };
    worldIcon = std::make_shared<Texture>();

    exitingBattles = false;

    worldIcon->loadFromFile("Assets/world.png", Engine::GetInstance()->GetRenderer());
    worldIcon->setTextureRect(worldRect.x, worldRect.y, worldRect.w, worldRect.h);

    menu = std::make_shared<GUI::Menu>();

    StateData::GetInstance()->followerTimer = std::make_shared<GameTimer>();
    getData()->battleThreadRunning.store(false);
    mainScreen = true;
    lastScreen = 0;

    tutorialCount = 0;
	textBox = std::make_shared<GUI::textBox>();
    refreshGUI();

    bg1 = std::make_unique<Texture>();
    bg2 = std::make_unique<Texture>();

    bgTexture = std::make_unique<Texture>();

    if(!bgTexture->loadFromFile("Assets/mainBG.png", Engine::GetInstance()->GetRenderer())){

        printf("Error loading background texture");
    }

    if(!bg1->loadFromFile("Assets/Background/wood.png", Engine::GetInstance()->GetRenderer())){

        printf("Error loading wood. Lol");
    }

    if(!bg2->loadFromFile("Assets/Background/wood.png", Engine::GetInstance()->GetRenderer())){

        printf("Error loading wood. Lol");
    }

    getMainText()->setString(getActiveCharacter()->getStatsAttributeScreen(), true, GUI::p2pY(120));
    //getMainText()->setPosition(GUI::p2pX(20), GUI::p2pY(20));

    levelUpText = std::make_shared<GUI::Text>();

    levelUpText->setPosition(GUI::p2pX(60), GUI::p2pY(10));
    levelUpText->setString("");

    getEnemyText()->setString("");


    getDynamicText()->setString("");

	//std::vector<std::string> menuOptions;


    initButtons();
	testNpc = std::make_shared<Entity>();
    file = std::make_shared<LoadFiles>("Assets/factionDiag.txt");
}

Game::~Game(){

///    getData()->followerTimer.reset();
//    getData()->b.reset();
//    getData()->battleCounter = 0;
//
//    if(getData()->battleThread.joinable()){
//
//        getData()->battleThread.join();
//    }
}

void Game::refreshGUI(){

    State::refreshGUI();
//    getData()->mainText->setString("Select an option.");
	ops.clear();
	std::string msg3 = "Increase Attributes";
	if(getActiveCharacter()->getAttributePoints() > 0){

        msg3 += " **";
	}

	///ops.push_back("Visit Civilisation");    //1
	///ops.push_back("Explore Wilderness");      //GONE
	ops.push_back("Open World Map");  ///2
	ops.push_back("Rest");   //3
	///ops.push_back("Inventory");        //4
	ops.push_back("Settings");//5
	///ops.push_back("Help");     //6
	ops.push_back("Quit to Title"); //7

	menu->setMenuOptions(ops, true);
	textBox->refreshGUI();
	initButtons();

	getEnemyText()->setPosition(GUI::p2pX(55), GUI::p2pY(40));
    getDynamicText()->setPosition(GUI::p2pX(55), GUI::p2pY(30));
}

//void Game::startBattleThread(){
//
//    std::lock_guard<std::mutex> lock(mtx);
//    if(!battleThreadRunning){
//    b = std::make_shared<Battle>(true);
//    battleCounter = 0;
//    battleThreadRunning.store(true);
//    battleThread = std::thread(&Game::runFollowerBattles, this);
//    }
//}
//
//void Game::runFollowerBattles(){
//
//        std::cout << "TOP OF RUN FOLLOWER BATTLE" << std::endl;
//
//        bool death = false;
//        int loopCounter = 0;
//
//        while (battleThreadRunning.load()) {
//
//
//                std::unique_lock<std::mutex> lock(mtx);
//
//                if(battleThreadPaused.load()){
//
//                    followerTimer->pause();
//                    cv.wait(lock, [this]{return !battleThreadPaused.load();});
//                    followerTimer->unpause();
//                }
//
//
//                ///Replaces the sleep_for functionality...
//                if(cv.wait_for(lock, std::chrono::milliseconds(1000), [this] { return !battleThreadRunning; })){
//                    break;
//                }
//        bool battleFinished = false;
//        int timeToAdventure = 120000;  ///2 MINUTES FOR ADVENTURING...
//
//        if(followerTimer->getTicks() <= timeToAdventure){  ///
//
//        int test = getActiveCharacter()->getActiveFollower()->getLevel();
//
//            if(getActiveCharacter()->getActiveFollower()->isAlive()){
//
//                    if(b->getEnemies().size() <= 0){
//
//                    std::string msg = "Follower defeated all enemies. New battle begins!";
//                    battleCounter++;
//                    std::cout << msg << std::endl;
//                    std::cout << std::to_string(battleCounter) << std::endl;
//                    if(followerTimer->getTicks() <= timeToAdventure){
//
//                        b->spawnEnemies();
//                    }
//                }
//                else{
//                        if (battleCounter >= 5) {
//                            battleFinished = true;
//                            battleThreadRunning.store(false);
//
//                            return;
//                        }
//                    b->followersAutoBattle();
//                }
//            }
//
//                if(!getActiveCharacter()->getActiveFollower()->isAlive()){   ///FOLLOWER DIED
//                    battleThreadRunning.store(false);
//                    cv.notify_all();
//                    battleFinished = true;
//                    followerTimer->stop();
//                    battleCounter = 0;
//                    std: string s = getFollowerText()->getString();
//                    s += "\nA brave soul returns to the void. Follower Lost.";
//                    getFollowerText()->setString(s, true);
//                    getActiveCharacter()->removeFollower();
//                    battleCounter++;
//                    death = true;
//                    std::cout << "THIS IT THE FOLLOWE DIES" << std::endl;
//                    ///return;
//                }
//            }   ///ND IF TICKS < timetoAdventure
//            else{       ///TIME RAN OUT (BattleCounter
//
//                    ///EXIT BATTLE
//                    //battleCounter++;
//                    battleThreadRunning.store(false);
//                    battleFinished = true;
//                    followerTimer->stop();
//                    std::string s = "";
//                    if(getFollowerText()->getString() != ""){
//
//                        s = getFollowerText()->getString();
//                    }
//                    std::string msg = "\nTime ran out. Your follower won " + std::to_string(battleCounter);
//                    msg += (battleCounter == 1) ? " battle" : " battles!";
//                    s += msg;
//                    getFollowerText()->setString(s, true);
//                    //HITS AFTER FOLLOWER DIES...
//                    std::cout << "TIME RAN OUT: BROKE FIRST LOOP" << std::endl;
//                    battleCounter = 0;
//                }
//        //HITS HERE WHEN FOLLOWER FIRST DIES>......
//                loopCounter++;
//                if (loopCounter == 2) {
//
//                    int check = 0;
//                }
//                std::cout << std::to_string(loopCounter) << " LOOP OF BATTLETHREADRUNNING!" << std::endl;
//            //}
//        }
//
//        std::cout << "EXITING BATTLE THREAD" << std::endl;
//        followerTimer->stop();
//}


void Game::update(const float& dt){

    State::update(dt);
    menu->update();

    if(exitingBattles && getData()->battleThreadRunning.load()){


            // Calculate the time remaining
            float timeRemaining = 31.0f - (getData()->followerTimer->getTicks() / 1000.0f);

            // Use stringstream to format the time to two decimal places
            std::stringstream ss;
            ss << std::fixed << std::setprecision(3) << timeRemaining;

        std::string msg = "Exiting enemy battles: " + ss.str();
        msg += "\n\n\nQuitting will cancel battles. Are you sure?";
        //std::string msg = "Exiting enemy battles: " + std::to_string(30 - (followerTimer->getTicks() / 1000.f));
        confirmationBox->setText(msg);

        confirmationBox->update();

        return;
    }
    else{

        confirmationBox->setText("Are you sure?");

        confirmationBox->update();
    }

//    if (exitingBattles) {
//        if (!getData()->battleThreadRunning.load() && getData()->battleThread.joinable()) {
//
//            getData()->battleThread.join();
//            exitingBattles = false;  // Reset the flag
//            Engine::GetInstance()->PopState();
//        }
//    }

    if(confirmationBox->getActive()){

        SDL_ShowCursor(SDL_ENABLE);
        confirmationBox->update();


        return;
    }



    std::lock_guard<std::mutex> lock(getData()->mtx);
    menu->update();
    float timeRemaining = (getData()->followerTimer->getTicks() / 1000.0f);
    std::stringstream ss;
    ss << std::fixed << std::setprecision(4) << timeRemaining;
    std::string msg = ss.str();
    timerText->setString(msg, true);
    if (!getData()->battleThreadRunning.load()) {

        if(getData()->battleThread.joinable()){

            getData()->battleThread.join();

            return;
        }
    }

    int x, y;
    SDL_GetMouseState(&x, &y);

    if(x > worldRect.x && x < worldRect.x + worldRect.w && y > worldRect.y && y < worldRect.y + worldRect.h){

        worldIcon->loadFromFile("Assets/worldSelected.png", Engine::GetInstance()->GetRenderer());
    }
    else{

        worldIcon->loadFromFile("Assets/world.png", Engine::GetInstance()->GetRenderer());
    }

    backButton->setActive(false);
    //Play the music
    if(!skipIntro()){
                        ///TODO: Create a questEncounter function which takes faction and questID.
        Engine::GetInstance()->AddState(std::make_shared<FactionEncounter>(1)); ///WHITE FACTION ENCOUNTER

        setSkipIntro(true);

        return;
    }

        if(Mix_PlayingMusic() == 0){

                        if( Mix_PlayMusic( music, -1) == -1 )
                        {
                            printf("ERROR PLAYING MUSIC Game.cpp line 57.");
                        }
        }


    if(getActiveCharacter()->getAttributePoints() > 0){

        levelUpText->setString("Attribute upgrade available!");
    }
    else{

        levelUpText->setString("");
    }

    ///
    if(StateData::GetInstance()->getTutorial() == true){

        runTutorial();
    }

    if(textBox->getActive() || testNpc->getDialogueActive()){

        menu->setActive(false);
    }
//    else{
//
//        menu->setActive(true);
//    }

    if(getData()->getActiveCharacter()->getExp() >= getData()->getActiveCharacter()->getExpNext()){

        getActiveCharacter()->levelUp();
        levelUpText->setString("Level Up Available!!");
    }


            //getMainText()->clearText();


            getMainText() = std::make_shared<GUI::Text>(5, 5, 89, 60, true);
            if(lastScreen == LAST_SCREEN::character){

                getMainText()->setString(getActiveCharacter()->getStatsAttributeScreen(), true, GUI::p2pY(120));
            }
            else if(lastScreen == LAST_SCREEN::faction){

                //menu->setMenuOptions(ops);
                std::string fact = StateData::GetInstance()->getActiveCharacter()->getFactionStr();
                getMainText()->setString(fact, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                getEnemyText()->setString("");
                getDynamicText()->setString("");
                mainScreen = false;
            }
            else if(lastScreen == LAST_SCREEN::skills){

                //menu->setMenuOptions(ops);
                std::string msg = StateData::GetInstance()->getActiveCharacter()->displaySkills();
                getMainText()->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                mainScreen = false;
            }
            else if(lastScreen == LAST_SCREEN::followers){

               /// getMainText()->setString(getActiveCharacter()->printFollowers(), true);
                //
                lastScreen = LAST_SCREEN::character;
                mainScreen = true;
            }


            for (auto button : mButtons) {

                button.second->update();
            }

    saveCharacters();

//    if(battleThreadRunning){
//
//        processBattles();
//    }
}

void Game::runTutorial(){
///RUN TUTORIAL
        switch(tutorialCount){

        case 0:
            textBox->setSize(70, 30);
            textBox->setActive(true);
            textBox->setHeader("Welcome to the tutorial!");
            textBox->setText("Here I will explain some of the screens.\n\nPress ENTER to continue...");
            textBox->setPosition(GUI::p2pX(20), GUI::p2pY(20));
            break;

        case 1:
            //textBox->setSize(50, 50);
            textBox->setActive(true);
            textBox->setHeader("Main Menu");
            textBox->setText("Here is your main menu, scroll using the UP and DOWN arrow buttons\n\nPress ENTER to continue...");
            textBox->setPosition(GUI::p2pX(40), GUI::p2pY(10));
            break;

        case 2:
            textBox->setActive(true);
            textBox->setHeader("Information Screen");
            textBox->setText("The main screen will show you your character stats. Selecting an option from the menu or one of the quick buttons will change the information displayed here.\n\nPress ENTER to continue...");
            textBox->setPosition(GUI::p2pX(40), GUI::p2pY(30));
            break;

        case 3:
            textBox->setActive(true);
            textBox->setHeader("SCREEN NAVIGATION");
            textBox->setText("You can see your character overview, faction standings and skill levels by selecting the corresponding button.\n\nPress ENTER to close...");
            textBox->setPosition(GUI::p2pX(20), GUI::p2pY(1));
            break;

        default:
            break;
        }
        ///END TUTORIAL
}

void Game::runMenuSelection(){

            //GAME LOOP HERE
        if(menu->isSelected()){

            getDynamicText()->setString("");
            getEnemyText()->setString("");

//            if(menu->getChoice() == 0){ ///Civilisation
//
//                getMainText()->setString("You travel into parts unknown...");
//                SDL_Delay(200);
//                StateData::GetInstance()->getActiveCharacter()->travel();
//                Engine::GetInstance()->AddState(std::make_shared<GraphicRandomEncounter>());
//
//            }

//            if(menu->getChoice() == 1){ ///BATTLE
//
//                    Engine::GetInstance()->AddState(std::make_shared<Battle>());
//            }

            if(menu->getChoice() == 0){

                                SDL_Delay(200);
                StateData::GetInstance()->getActiveCharacter()->travel();
                Engine::GetInstance()->AddState(std::make_shared<GraphicRandomEncounter>());
            }

            if(menu->getChoice() == 1){

                getEnemyText()->setPosition(GUI::p2pX(55), GUI::p2pY(40));
                getDynamicText()->setPosition(GUI::p2pX(55), GUI::p2pY(30));
                int injuredCost = 0;
                if(!getActiveCharacter()->fullHealth()){

                    injuredCost += 10;
                }

                if(!getActiveCharacter()->getFollowers().empty()){

                for(size_t i = 0; i < getActiveCharacter()->getFollowers().size(); i++){

                        if(!getActiveCharacter()->getFollowers()[i]->fullHealth()){

                            injuredCost += 10;
                        }
                    }
                }

                std::string msg = "";
                if(StateData::GetInstance()->getActiveCharacter()->getGold() >= injuredCost){

                    if(!getActiveCharacter()->getFollowers().empty()){
                            for(size_t i = 0; i < getActiveCharacter()->getFollowers().size(); i++){

                        if(!getActiveCharacter()->getFollowers()[i]->fullHealth()){

                           // injuredCost += 10;
                            getActiveCharacter()->getFollowers()[i]->resetHP();
                            injuredCost -= 10;
                            getActiveCharacter()->gainGold(-injuredCost);
                            msg += getActiveCharacter()->getFollowers()[i]->getName() + " healed!\n";
                        }
                    }
                        if(msg == ""){

                           msg += "Followers all have full health!\n";
                        }
                    }

                    if(!getActiveCharacter()->fullHealth()){

                    StateData::GetInstance()->getActiveCharacter()->resetHP();
                    StateData::GetInstance()->getActiveCharacter()->gainGold(-injuredCost);

                    msg += "You awake feeling well rested";
                    getDynamicText()->setString(msg, true);
                    getEnemyText()->setColour(255, 0, 0, 0);
                    //getEnemyText()->setString("Lost 10 gold");

                        return;
                    }
                    else{
                        msg += "Your health is full!";
                        getDynamicText()->setString(msg, true);
                    }
                }
                else{

                    getEnemyText()->setColour(255, 0, 0, 0);
                    getEnemyText()->setString("You don't have enough gold.");
                }
            }

//            if(menu->getChoice() == 3){
//
//                Engine::GetInstance()->AddState(std::make_shared<CharacterMenu>());
//            }

            if(menu->getChoice() == 2){

                Engine::GetInstance()->AddState(std::make_shared<Settings>());
            }

//            if(menu->getChoice() == 3){
//
//                tutorialCount = 0;
//                StateData::GetInstance()->setTutorial(true);
//            }

            if(menu->getChoice() == 3){

                confirmationBox->setActive(true);
                std::lock_guard<std::mutex> lock(getData()->mtx);
                getData()->battleThreadPaused.store(true);
            }
        }
}

void Game::initButtons(){

    unsigned int charSize = GUI::calcCharSize(125);


    mButtons["CHARACTER"] = std::make_shared<GUI::Button>(13.f, 58.5f, 11.8f, 6.1f, charSize);
    mButtons["CHARACTER"]->setRenderText("Character");

    mButtons["FACTIONS"] = std::make_shared<GUI::Button>(27.f, 58.5f, 11.8f, 6.1f, charSize);
    mButtons["FACTIONS"]->setRenderText("Factions");

    mButtons["SKILLS"] = std::make_shared<GUI::Button>(41.f, 58.5f, 11.8f, 6.1f, charSize);
    mButtons["SKILLS"]->setRenderText("Attributes");

    mButtons["FOLLOWERS"] = std::make_shared<GUI::Button>(55.f, 58.5f, 11.8f, 6.1f, charSize);
    mButtons["FOLLOWERS"]->setRenderText("Followers");

    mButtons["INVENTORY"] = std::make_shared<GUI::Button>(69.f, 58.5f, 11.8f, 6.1f, charSize);
    mButtons["INVENTORY"]->setRenderText("Inventory");

    for (auto button : mButtons) {

		button.second->setBackgroundTexture("Assets/Background/button2.png");
	}
}

void Game::updateEvents(SDL_Event& e){

    menu->updateEvents(e);
    if(confirmationBox->getActive()){

        confirmationBox->updateEvents(e.button);

        if(!getData()->battleThreadRunning.load()){

            exitingBattles = false;
        }

         if(confirmationBox->yesPressed(e.button)){

            if(!exitingBattles){


            //confirmationBox->setConfirm(false);
            //confirmationBox->setActive(false);
            if(getData()->battleThreadRunning.load() && getData()->battleThread.joinable()){
                std::lock_guard<std::mutex> lock(getData()->mtx);
                if(getData()->battleThreadPaused.load()){

                    getData()->battleThreadPaused.store(false);
                    getData()->cv.notify_all();
                }
                getEnemyText()->setString("Exiting follower battles!");
                exitingBattles = true;
                ///battleThread.join();
                //confirmationBox->setActive(false);
                return;
            }
            ///THIS SHOULD BE SETTING IT BACK TO QUIT + FALSE OR SOMETHING...
            confirmationBox->setChoice(false);
            Engine::GetInstance()->PopState();

            return;
            }
            else{

                if(getData()->battleThreadRunning.load() && getData()->battleThread.joinable()){

                    getData()->battleThreadRunning.store(false);
                    getData()->battleThread.detach();
                    exitingBattles = false;

                    confirmationBox->setChoice(false);
                    Engine::GetInstance()->PopState();

                    return;
                }
            }
        }   ///END YES PRESSED
        else if(confirmationBox->noPressed(e.button)){

            if(!exitingBattles){

                if(getData()->battleThreadPaused.load()){

                    std::lock_guard<std::mutex> lock(getData()->mtx);
                    getData()->battleThreadPaused.store(false);
                    getData()->cv.notify_all();
                }
            }
            else{

                exitingBattles = false;
                confirmationBox->setActive(false);
            }
        }

        return;
    }

    if(e.type == SDL_MOUSEBUTTONDOWN && !getData()->getTutorial()){

        int x, y;
        SDL_GetMouseState(&x, &y);

         if(x > worldRect.x && x < worldRect.x + worldRect.w && y > worldRect.y && y < worldRect.y + worldRect.h){

            getMainText()->setString("You travel into parts unknown...");
            SDL_Delay(200);
            StateData::GetInstance()->getActiveCharacter()->travel();
            Engine::GetInstance()->AddState(std::make_shared<GraphicRandomEncounter>());
         }

         //BUTTONS START HERE
        if (mButtons["SKILLS"]->isPressed(e.button)) {

            refreshGUI();
            //menu->setMenuOptions(ops);
            std::string msg = StateData::GetInstance()->getActiveCharacter()->displaySkills();
            getMainText()->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
            Engine::GetInstance()->AddState(std::make_shared<IncreaseAttributes>());
            mainScreen = false;

            lastScreen = LAST_SCREEN::character;
            return;
        }

        if (mButtons["FACTIONS"]->isPressed(e.button)) {

            refreshGUI();
            //menu->setMenuOptions(ops);
            std::string fact = StateData::GetInstance()->getActiveCharacter()->getFactionStr();
            getMainText()->setString(fact, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
            mainScreen = false;


            lastScreen = LAST_SCREEN::faction;
            return;
        }

        if (mButtons["CHARACTER"]->isPressed(e.button)) {
            refreshGUI();
            //menu->setMenuOptions(ops);
            mainScreen = true;
            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));

            lastScreen = LAST_SCREEN::character;
            return;
        }

        if (mButtons["FOLLOWERS"]->isPressed(e.button)) {
            refreshGUI();
            //menu->setMenuOptions(ops);
            mainScreen = true;
            getMainText()->clearText();
            getDynamicText()->clearText();
            std::string mmm = StateData::GetInstance()->getActiveCharacter()->printFollowers();
            getMainText()->setString(mmm, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));

            lastScreen = LAST_SCREEN::followers;
            Engine::GetInstance()->AddState(std::make_shared<FollowerMenu>());
            //lastScreen = LAST_SCREEN::character;
            return;
        }

        if(mButtons["INVENTORY"]->isPressed(e.button)){

            Engine::GetInstance()->AddState(std::make_shared<CharacterMenu>());

            return;
        }

        if(menu->isSelected()){

            runMenuSelection();
            return;
        }

        if(getEnemyText()->getString() != ""){

            getEnemyText()->setString("");
        }

        if(getDynamicText()->getString() != ""){

            getDynamicText()->setString("");
        }

    }   ///END MOUSEBUTTONDOWN

    ///START KEYBOARD CHECKS
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){

        std::string msg = "Corruption: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getCorruption());
        getEnemyText()->setString(msg);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)){

        getMainText()->setString("You travel into parts unknown...");
        SDL_Delay(200);
        StateData::GetInstance()->getActiveCharacter()->travel();
        Engine::GetInstance()->AddState(std::make_shared<GraphicRandomEncounter>());

        return;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_I)){

        Engine::GetInstance()->AddState(std::make_shared<CharacterMenu>());
        return;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_F)){

        Engine::GetInstance()->AddState(std::make_shared<FollowerMenu>());

        return;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_G)){

        refreshGUI();
            //menu->setMenuOptions(ops);
            std::string fact = StateData::GetInstance()->getActiveCharacter()->getFactionStr();
            getMainText()->setString(fact, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
            mainScreen = false;


            lastScreen = LAST_SCREEN::faction;
            return;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_H)){

        refreshGUI();
            //menu->setMenuOptions(ops);
            mainScreen = true;
            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));

            lastScreen = LAST_SCREEN::character;
            return;
    }


    if(e.type == SDL_KEYDOWN){

        if(!getDynamicText()->isEmpty() || !getEnemyText()->isEmpty()){


            getEnemyText()->clearText();
            getDynamicText()->clearText();

            return;
        }
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN) && e.key.repeat == 0){


            if(textBox->getActive()){

            textBox->setActive(false);

            if(StateData::GetInstance()->getTutorial() == true){

                if(tutorialCount < 3){

                    tutorialCount++;

                    return;
                }
                StateData::GetInstance()->setTutorial(false);
            }
        }

        if(!getDynamicText()->isEmpty() || !getEnemyText()->isEmpty()){


            getEnemyText()->clearText();
            getDynamicText()->clearText();

            ///return;
        }

        if(!menu->cursorDetached() || !SDL_ShowCursor(SDL_QUERY)){

            runMenuSelection();
            return;
        }
        else{

            menu->cursorDetached();
        }



        if(testNpc->getDialogueActive()){

            testNpc->setDialogueActive(false);
        }


        if(!menu->getActive()){

            menu->setActive(true);
        }
        ///TODO Need to run the same code to check the menu as above.... DEfinitely split that into it's own function
    }

     State::updateEvents(e);
}

void Game::render(){

    SDL_RenderClear(Engine::GetInstance()->GetRenderer());

    int r = getActiveCharacter()->getRep(2) - 100; ///FACTIONS::RED == 2
    int g = getActiveCharacter()->getRep(5) - 100; ///FACTIONS::GREEN == 5
    int b = getActiveCharacter()->getRep(6) - 100; ///FACTIONS::BLUE == 6

    if(r < 0){

        r = 0;
    }

    if(g < 0){

        g = 0;
    }

    if(b < 0){

        b = 0;
    }

    if(r > 255){

        r = 255;
    }

    if(g > 255){

        g = 255;
    }

    if(b > 255){

        b = 255;
    }

///    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), r, g, b, 255);
///    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 0, 0, 255);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    getMainText()->setBgColour(r, g, b, 255);
    getMainText()->render();



    SDL_Rect bgR1 = {0, 0, GUI::p2pXi(3), GUI::p2pYi(100)};
    SDL_Rect bgR2 = { GUI::p2pXi(97), 0, GUI::p2pXi(3), GUI::p2pYi(100) };
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), bg2->getTexture(), NULL, &bgR2);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), bg1->getTexture(), NULL, &bgR1);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 215, 0, 255);
    SDL_RenderDrawLine(Engine::GetInstance()->GetRenderer(), GUI::p2pX(3), 0, GUI::p2pX(3), GUI::p2pY(100));
    SDL_RenderDrawLine(Engine::GetInstance()->GetRenderer(), GUI::p2pX(97), 0, GUI::p2pX(97), GUI::p2pY(100));
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 255, 0, 255);

    //SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), background->getTexture(), NULL, NULL);
    getDynamicText()->render();
    getEnemyText()->render();
    menu->render();

    levelUpText->render();

    if(getData()->battleThreadRunning){

        timerText->render();
    }

///    background->render(Engine::GetInstance()->GetRenderer(), 0, 0);

    for (auto i : mButtons) {

///        initButtons();
		i.second->renderButtons();
	}

	worldIcon->renderToViewPort(Engine::GetInstance()->GetRenderer(), worldRect.x, worldRect.y, NULL, &worldRect);
    ///SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &worldRect);

       if(textBox->getActive()){

       if(StateData::GetInstance()->getTutorial() == true){
        getMainText()->setBgColour(0, 0, 0, 255);
        getMainText()->render();
        int w, h;
        SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &w, &h);
        SDL_Rect overlay = { 0, 0, w, h };
        SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 255, 255, 150);
        SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &overlay);
        SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_NONE);

        worldIcon->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, NULL, &worldRect);
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &worldRect);

        textBox->render();
        if(tutorialCount == 1){

            menu->render();
            textBox->render();
        }
        if(tutorialCount == 2){

            getMainText()->render();
            textBox->render();

        }
        if(tutorialCount == 3){

            SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 255, 255, 150);
            SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &overlay);
            SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_NONE);

            for(auto i : mButtons){

                i.second->renderButtons();
            }
            textBox->render();
        }
       } //END TUTORIAL
        ///textBox->render();
    }

///    followerTimer->tick();

    if(testNpc->getDialogueActive()){

        testNpc->renderDialogue();
    }


    if(confirmationBox->getActive()){

        confirmationBox->render();
    }

    worldTimerText->render();
}
