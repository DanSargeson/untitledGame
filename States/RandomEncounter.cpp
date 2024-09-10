#include "RandomEncounter.h"
#include "SkillComponent.h"
#include "AttributeComponent.h"


RandomEncounter::RandomEncounter(int faction){

    firstEncounter = true;
    caught = false;
    backButton->setActive(true);

    filename = "Assets/newDialogue.txt";

    getEnemyText()->setString("");

    getDynamicText()->setString("");

    textThreadRunning = true;

    buying = false;
    selling = false;

    textTimer = std::make_shared<GameTimer>();
    textTimer->start();
    builderText = "";
    copyText = "";
    textMsg = "";

    getEnemyText()->setColour(255, 0, 0, 0);
    textBuildCounter = 0;

    choice = -1;

    int playerLvlMin = getActiveCharacter()->getLevel();

    playerLvlMin -= 3;

    if(playerLvlMin <= 0){

        playerLvlMin = 1;
    }

    int npcLevel = getRandomValue(playerLvlMin, (getActiveCharacter()->getLevel()));

    npc = std::make_shared<NPC>(npcLevel, faction);
    npc->createComponents();

    switch(faction){

    case 2: ///RED
        getMainText()->setBgColour(200, 0, 0, 200);
        break;

    case 3: ///ORANGE
        getMainText()->setBgColour(255, 165, 0, 255);
        break;

    case 4: ///YELLOW
        getMainText()->setBgColour(200, 200, 0, 255);
        break;

    case 5: ///GREEN
        getMainText()->setBgColour(0, 200, 0, 255);
        break;

    case 6: ///BLUE
        getMainText()->setBgColour(0, 0, 200, 255);
        break;

    case 7: ///INDIGO
        getMainText()->setBgColour(75, 0, 130, 255);
        break;

    case 8: ///VIOLET
        getMainText()->setBgColour(127, 0, 255, 255);
        break;

    default:
        getMainText()->setBgColour(0, 0, 0, 255);
        break;
    }

    file = std::make_shared<LoadFiles>(filename, 0);

    npc->createInventory();
//    menu.reset();
    menu = std::make_shared<GUI::Menu>();
    buyMenu = std::make_shared<GUI::Menu>();
    buyMenu->setActive(false);

    copyText = "\"" + file->loadRandomDialogue() +  "\"";

    refreshGUI();

    std::cout << "NPC LEVEL: " << npcLevel << std::endl;
///    std::cout << npc->getStatsAttributeScreen();
    ///std::cout << "INT: " << npc->getAttribute(4) << std::endl;

    //getData()->mainText->setString("TESTING");
}

RandomEncounter::~RandomEncounter(){

    getMainText()->setBgColour(0, 0, 0, 255);
    if(textThread.joinable()){

        textThread.join();
    }

    getData()->dynamicText->clearText();
    getEnemyText()->clearText();
//    State::~State();
    State::refreshGUI();
}

void RandomEncounter::refreshGUI(){

    ///State::refreshGUI();

    initButtons();

    if(firstEncounter){
    std::string m = " a ";
            if(npc->getName() == "Alchemist" || npc->getName() == "Innkeeper"){

                m = " an ";
            }
    textMsg = "You are approached by" + m + npc->getName() + " of the " + npc->getFactionStr() + " faction.\n\n\n";
    //msg += "\"" + file->loadRandomDialogue() +  "\"";
    getData()->mainText->setString(textMsg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));

    unlockedCharm = false;

    std::vector<std::string> ops;
    ops.push_back("Chat");

    int check = npc->getFaction();
    int repCheck = getData()->getActiveCharacter()->getRep(check);
    if(getData()->getActiveCharacter()->getRep(npc->getFaction()) >= 110){

        ops.push_back("Charm");
        unlockedCharm = true;
    }


    ops.push_back("Steal");
    ops.push_back("Barter");
    ops.push_back("Recruit");

    menu->setMenuOptions(ops, true);


    }
    else{


    //###########################

    if(choice == 0){

                    getData()->getActiveCharacter()->gainRep(npc->getFaction(), 1);
                    std::string msg = "You have a pleasant chat with the stranger.\nFaction rep slightly increased.\nEXP Gained";
                    if(getData()->getActiveCharacter()->getRep(npc->getFaction()) == 110){

                        msg += "\n**New interaction unlocked!**";
                    }
                    getData()->dynamicText->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                getActiveCharacter()->gainXP();
                menu->setActive(false);
            }

            if(choice == 1){

            //Charm
                if(unlockedCharm){

                    if(charm()){

                        getData()->dynamicText->setString("The stranger is impressed by your wit. Faction rep gained.\nEXP Gained", true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                        getData()->getActiveCharacter()->gainRep(npc->getFaction(), 5);
                        getActiveCharacter()->gainXP();
                        menu->setActive(false);

                        return;
                    }
                    else{

                        std::string msg = "The stranger isn't fooled by false flattery";

                        if(getData()->getActiveCharacter()->getRep(npc->getFaction()) >= 112){

                            msg += "\nFaction rep decreased slightly.";
                            getData()->getActiveCharacter()->loseRep(npc->getFaction(), 1);
                        }

                        getDynamicText()->setString("nEXP Gained", true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                        getActiveCharacter()->gainXP();
                        getEnemyText()->setColour(255, 0, 0, 0);
                        getEnemyText()->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                        menu->setActive(false);

                        return;
                    }

                    menu->setActive(false);
                }
                else{

                    attemptSteal();
                    menu->setActive(false);

                    return;
                }

                menu->setActive(false);
            }

            if(choice == 2){

                if(unlockedCharm){

                    attemptSteal();
                    menu->setActive(false);

                    return;
                }
                else{

                    //barter
                    ///getEnemyText()->clearText();

                    npc->createInventory();

                    ops = npc->getInvAsVec();
                    for(size_t i = 0; i < ops.size(); i++){

                        std::string temp = ops[i];
                        ops[i] = temp + " - " + std::to_string(npc->getItem(i)->getBuyValue());
                    }
                    menu->setMenuOptions(ops);

                   /// getEnemyText()->setString("The stranger has no items...");
                    menu->setActive(false);
                    buyMenu->setActive(true);

                    return;
                }

            }
            if(choice == 3){

                if(unlockedCharm){

                    //barter
                    ///getEnemyText()->clearText();

                    npc->createInventory();
                    ops = npc->getInvAsVec();
                    for(size_t i = 0; i < ops.size(); i++){

                        std::string temp = ops[i];
                        ops[i] = temp + " - " + std::to_string(npc->getItem(i)->getBuyValue());
                    }
                    menu->setMenuOptions(ops);

                    menu->setActive(false);

                    return;
                    ///getEnemyText()->setString("The stranger has no items...");
                }
                else{

                    recruit();
                    return;
                }

            }

            if(choice == 4){

                recruit();

                return;
            }
        }

    getEnemyText()->setPosition(GUI::p2pX(30), GUI::p2pY(40));
    getDynamicText()->setPosition(GUI::p2pX(15), GUI::p2pY(40));
}


void RandomEncounter::update(const float& dt)
{

    if(menu->getActive()){

        menu->update();
    }
    if(buyMenu->getActive()){

        buyMenu->update();
    }

    backButton->update();

    if(textThreadRunning){

        updateText();
    }
    else{

        if(textThread.joinable()){

            textThread.join();
        }
    }

    if(buyMenu->getActive() && buyMenu->isSelected())
    {
        if(buying){

        std::string msg = npc->getItem(buyMenu->getChoice())->getInfo();
        msg += "\n\nYour Gold: " + std::to_string(getActiveCharacter()->getGold());

            getDynamicText()->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
        }

        else if(selling){

            std::string msg = getActiveCharacter()->getItem(buyMenu->getChoice())->getInfo();
            msg += "\n\nYour Gold: " + std::to_string(getActiveCharacter()->getGold());

            getDynamicText()->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
        }
    }
}

void RandomEncounter::runMenuSelection(){

   ///START runMenuSelection
        if(menu->isSelected() && menu->getActive()){

            choice = menu->getChoice();
            if(menu->getChoice() == 0){


                    getData()->getActiveCharacter()->gainRep(npc->getFaction(), 1);
                    std::string msg = "You have a pleasant chat with the stranger.\nFaction rep slightly increased.\nEXP Gained";
                    if(getData()->getActiveCharacter()->getRep(npc->getFaction()) == 110){

                        msg += "\n**New interaction unlocked!**";
                    }
                    getActiveCharacter()->gainXP();
                    getData()->dynamicText->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));

                menu->setActive(false);
            }

            if(menu->getChoice() == 1){

            //Charm
                if(unlockedCharm){
                    ///getData()->enemyText->clearText();
                    if(charm()){

                        int rando = getRandomValue(1, 5);
                        int totalXP = rando * (getActiveCharacter()->getAttribute(5) + getActiveCharacter()->getAttribute(6)); // 5 == CHARISMA, 6 == LUCK
                        std::string msg = "The stranger is impressed by your wit. Faction rep gained.\n" + std::to_string(totalXP) + " EXP gained.";
                        getData()->dynamicText->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                        getData()->getActiveCharacter()->gainRep(npc->getFaction(), 5);
                        getData()->getActiveCharacter()->gainXP(totalXP);
                        if(getData()->getActiveCharacter()->getExp() >= getData()->getActiveCharacter()->getExpNext()){

                            getData()->getActiveCharacter()->levelUp();
						}
                        //getData()->getActiveCharacter()->increaseSkill(7); //7 == SKILLS::PERSUASION

                        menu->setActive(false);
                    }
                    else{

                        std::string msg = "The stranger isn't fooled by false flattery.";

                        if(getData()->getActiveCharacter()->getRep(npc->getFaction()) >= 112){

                            msg += "\nFaction rep decreased slightly.";
                            getData()->getActiveCharacter()->loseRep(npc->getFaction(), 1);
                        }

                        getDynamicText()->setString("EXP Gained", true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));

                        getActiveCharacter()->gainXP();
                        getEnemyText()->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                        menu->setActive(false);
                    }
                }
                else{

                    attemptSteal();
                    menu->setActive(false);
                }

                menu->setActive(false);
            }

            if(menu->getChoice() == 2){

                if(unlockedCharm){

                    attemptSteal();
                    menu->setActive(false);
                }
                else{

                    //barter
                    ///getData()->enemyText->clearText();
                    getDynamicText()->setString("Take a look...");

                    ///getEnemyText()->setString("The stranger has no items...");
                    ops.clear();
                    ops.push_back("Buy");
                    ops.push_back("Sell");
                    buyMenu->setMenuOptions(ops, true);
                    menu->setActive(false);
                    buyMenu->setActive(true);

                    return;
                }

            }
            if(menu->getChoice() == 3){

                if(unlockedCharm){

                    //barter

                    npc->createInventory();

                    getDynamicText()->setString("Take a look...");
                    getEnemyText()->clearText();
                    ///getEnemyText()->setString("The stranger has no items...");
                    ops.clear();
                    ops.push_back("Buy");
                    ops.push_back("Sell");
                    buyMenu->setMenuOptions(ops, true);
                    buyMenu->setActive(true);
                    menu->setActive(false);

                    return;
                }
                else{

                    if(getActiveCharacter()->getFollowers().size() >= 5){

                        getDynamicText()->setString("Max followers. Level up to expand capactiy");
                    }
                    else{

                        recruit();
                        menu->setActive(false);
                    }
                    return;
                }
            }

            if(menu->getChoice() == 4){

                if(getActiveCharacter()->getFollowers().size() >= 5){

                        getDynamicText()->setString("Max followers. Level up to expand capactiy");
                    }
                    else{

                        recruit();
                        menu->setActive(false);
                    }

                return;
            }
        }
        ///

        if(buyMenu->getActive()){


//            std::string temp = "";
//            temp = "You have: " + " " + std::to_string(getActiveCharacter()->getGold()) + " gold!\n\n";
//            auto playerGold = std::make_shared<GUI::Text>(GUI::p2pXi(45), GUI::p2pYi(45), 200, 200, false);
//            playerGold->setString(temp);

                if(getEnemyText()->getString() != ""){

                    return;
                }


            if(buyMenu->isSelected()){

                if(!buying && !selling){
                    if(buyMenu->getChoice() == 0){

                        buying = true;
                        selling = false;
                        ops = npc->getInvAsVec();
                        for(size_t i = 0; i < ops.size(); i++){

                            std::string temp = ops[i];
                            ops[i] = temp + " - " + std::to_string(npc->getItem(i)->getBuyValue());
                        }
                        //menu->setMenuOptions(ops);
                        buyMenu->setMenuOptions(ops, true);
                        return;
                    }

                    if(buyMenu->getChoice() == 1){

                        selling = true;
                        buying = false;

                        ops = getActiveCharacter()->getInvAsVec();

                        if(ops[0] != "You have no items"){

                        for(size_t i = 0; i < ops.size(); i++){

                            std::string temp = ops[i];
                            ops[i] = temp + " - " + std::to_string(getActiveCharacter()->getItem(i)->getSellValue());
                        }

                        buyMenu->setMenuOptions(ops, true, true);

                        return;
                        }
                        else{

                            getDynamicText()->setString("You have no items");
                            selling = false;

                            ops.clear();
                            ops.push_back("Buy");
                            ops.push_back("Sell");
                            buyMenu->setMenuOptions(ops, true);

                            return;
                        }
                    }
                }

            }

            if(buying){

                int cc = buyMenu->getChoice();
                std::shared_ptr<Item> wv = npc->findItem(cc);

                if(getActiveCharacter()->getGold() >= wv->getBuyValue()){


                std::string msg = wv->debugPrint();
                npc->removeItem(cc);
                getActiveCharacter()->addItem(wv);
                getDynamicText()->setString("Item bought!");
                getActiveCharacter()->gainGold(-wv->getBuyValue());

                ops.clear();
                ops.push_back("Buy");
                ops.push_back("Sell");
                buyMenu->setMenuOptions(ops, true);
                buying = false;

                return;
                }
                else{

                    getEnemyText()->setString("You cannot afford this item..");
                    getDynamicText()->setString("");


                ops.clear();
                ops.push_back("Buy");
                ops.push_back("Sell");
                buyMenu->setMenuOptions(ops, true);
                buying = false;
//                buyMenu->setActive(true);
                return;
                }

            }
            if(selling){

                int cc = buyMenu->getChoice();
                std::shared_ptr<Item> wv = getActiveCharacter()->findItem(cc);

                getActiveCharacter()->removeItem(cc);
                getDynamicText()->setString("Item sold..." + std::to_string(wv->getSellValue()) + " gold gained!");
                getActiveCharacter()->gainGold(wv->getSellValue());

                ops.clear();
                ops.push_back("Buy");
                ops.push_back("Sell");
                buyMenu->setMenuOptions(ops, true);

                selling = false;
                //buyMenu->setActive(false);
                //menu->setActive(true);
            }

        }

}

void RandomEncounter::startTextThread(){

    textThreadRunning = true;
    textThread = std::thread(&RandomEncounter::updateText, this);
}


void RandomEncounter::updateText(){

    if(builderText != copyText){

        menu->setActive(false);

    // loop through each character in the text
        // output one character
        // flush to make sure the output is not delayed
        builderText.push_back(copyText[textBuildCounter]);
        //mTextTexture->loadFromRenderedText(Engine::GetInstance()->GetRenderer(), copy_text, mTextColour, *mFont, true, 80);

        //mTextTexture->render(Engine::GetInstance()->GetRenderer(),  mOutline.x + offsetX, mOutline.y + offsetY);
        // sleep 60 milliseconds
        ///std::this_thread::sleep_for(std::chrono::milliseconds(600));
        std::string temp = textMsg;
        temp += builderText;
        //temp += builderText;

        getMainText()->setString(temp, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
        //getMainText()->render();
       // std::this_thread::sleep_for(std::chrono::milliseconds(60));
       //L_Deay(700);
        textBuildCounter++;
    }

    else{

        builderText = "";
        textBuildCounter = 0;
        textThreadRunning = false;
        menu->setActive(true);
    }
}

void RandomEncounter::updateEvents(SDL_Event& e){



        if(menu->getActive()){

            menu->updateEvents(e);
        }
        if(buyMenu->getActive()){

           buyMenu->updateEvents(e);
        }

        if(backButton->isActive() && backButton->isPressed(e.button)){


            if(buying || selling){

                buying = false;
                selling = false;

                ops.clear();
                ops.push_back("Buy");
                ops.push_back("Sell");

                getDynamicText()->setString("Take a look...");

                buyMenu->setMenuOptions(ops, true);

                return;
            }


            if(buyMenu->getActive()){

                getDynamicText()->setString("");
                getEnemyText()->setString("");
                menu->setActive(true);
                buyMenu->setActive(false);

                return;
            }

            Engine::GetInstance()->PopState();  //1

            return;
        }

        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){

            if(buying || selling){

                buying = false;
                selling = false;

                ops.clear();
                ops.push_back("Buy");
                ops.push_back("Sell");

                getDynamicText()->setString("Take a look...");

                buyMenu->setMenuOptions(ops, true);

                return;
            }

            if(buyMenu->getActive()){


                getDynamicText()->setString("");
                getEnemyText()->setString("");
                menu->setActive(true);
                buyMenu->setActive(false);

                return;
            }
        }

        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP)){

            if(buyMenu->getActive()){

                getDynamicText()->setString("");
                getEnemyText()->setString("");
            }
        }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        if(textThreadRunning){

            textThreadRunning = false;
            menu->setActive(true);

            textTimer->restart();
            return;
        }

        if(!menu->getActive() && !buyMenu->getActive() && !textThreadRunning){

            SDL_Delay(100);
           // Engine::GetInstance()->PopState();
            Engine::GetInstance()->PopState();  //2

            return;
        }


        if(!textThreadRunning && menu->getActive() && textTimer->getTicks() > 500){

            if(!menu->cursorDetached() || !SDL_ShowCursor(SDL_QUERY)){

                runMenuSelection();
            }

            return;
        }

        if(!textThreadRunning && buyMenu->getActive() && textTimer->getTicks() > 500){

            getEnemyText()->setString("");

            runMenuSelection();

            return;
        }
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){

        std::string ss = getData()->getActiveCharacter()->printPlayerDetails();
        std::cout << ss << std::endl;
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){


        if(textThreadRunning){

            textThreadRunning = false;
            menu->setActive(true);

            textTimer->restart();
            return;
        }


        if(!menu->getActive() && !buyMenu->getActive() && !textThreadRunning){

            SDL_Delay(100);
            //Engine::GetInstance()->PopState();
            Engine::GetInstance()->PopState();  //3

            return;
        }

        if(menu->getActive()){
            if(!menu->cursorDetached() || !SDL_ShowCursor(SDL_QUERY)){

                runMenuSelection();
                return;
            }
        }

//        if(buyMenu->getActive()){
//
//            if(!buyMenu->cursorDetached() || !SDL_ShowCursor(SDL_QUERY)){
//
//                runMenuSelection();
//            }
//
//            return;
//        }
        if(!textThreadRunning && buyMenu->getActive() && textTimer->getTicks() > 500){

            getEnemyText()->setString("");

            runMenuSelection();

            return;
        }
    }



    State::updateEvents(e);
}

void RandomEncounter::render(){

    if(textThreadRunning){

        std::string temp = textMsg;
        temp += builderText;
        getMainText()->setString(temp, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
        getMainText()->render();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //return;
    }else{

        std::string temp = textMsg;
        temp += copyText;
        getMainText()->setString(temp, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
        getMainText()->render();
    }
    ///getData()->mainText->render();

    if(getData()->dynamicText->getString() != ""){

        getData()->dynamicText->render();
    }
    if(getEnemyText()->getString() != ""){

        getEnemyText()->render();
    }


        menu->render();

    if(buyMenu->getActive()){

        buyMenu->render();
    }

    backButton->renderButtons();
}

bool RandomEncounter::charm(){

///bool success = false;

//    int playerTotal = getData()->getActiveCharacter()->getAttribute(5);
//    int npcTotal = npc->getAttribute(4);
//
//    int luck = rand() % getData()->getActiveCharacter()->getAttribute(6) + 1;
//    playerTotal += luck;

    int playerPersuasion = getActiveCharacter()->getSkill(SKILLS::PERSUASION);    ///7 == PERSUASION
    int npcPerception = npc->getSkill(SKILLS::PERCEPTION);   /// 8 == PERCEPTION

    bool success = getActiveCharacter()->skillCheck(npc, playerPersuasion, npcPerception);

//    if(playerTotal > npcTotal){
//
//        success = true;
//    }

    return success;
}

void RandomEncounter::recruit(){


    int chance = getActiveCharacter()->getSkill(SKILLS::PERSUASION) * getActiveCharacter()->getAttribute(ATTRIBUTE::CHARISMA);
    int npcChance = npc->getSkill(SKILLS::PERCEPTION) * npc->getAttribute(ATTRIBUTE::LUCK);
    bool success = getActiveCharacter()->skillCheck(npc, chance, npcChance);

    if(success){

        getActiveCharacter()->addFollower(npc);
        std::string msg = npc->getName() + " recruited!";
        getDynamicText()->setString(msg, true);
    }
    else{

        getEnemyText()->setString("Recruiting failed!", true);
    }
}

bool RandomEncounter::rob(){


    int pickpocket = getActiveCharacter()->getSkill(SKILLS::PICKPOCKET);
    int npcPerception = npc->getSkill(SKILLS::PERCEPTION);

   bool success = getActiveCharacter()->skillCheck(npc, pickpocket, npcPerception);

    if(success == false){

        ///Chance to avoide detection:

//        int detectChance = getRandomValue(0, 100);
//
//        if(detectChance <= 50){
//
//            caught = true;
//        }
//        else{

            int stealth = getActiveCharacter()->getSkill(SKILLS::STEALTH);
            int luck = getActiveCharacter()->getSkill(6);    ///6 == LUCK
            int npcAccuracy = npc->getSkill(SKILLS::ACCURACY);
            caught = !npc->skillCheck(npc, stealth, npcAccuracy);
      ///  }
    }

    return success;
}

void RandomEncounter::attemptSteal(){

 //Steal HERE
                getData()->dynamicText->clearText();
                int gold = getRandomValue(1, (1+(npc->getLevel()*10)));
                if(rob()){

                    std::string msg = "You succeed in robbing the stranger, gold increased by " + std::to_string(gold) + "\nEXP Gained";
                    getActiveCharacter()->gainXP();
                    getData()->dynamicText->setString(msg, true);
                    getData()->getActiveCharacter()->gainGold(gold);
                }
                else{

                    std::string msg = "Attempt Failed.\n";

                    if(caught){

                        if((getData()->getActiveCharacter()->getGold() - gold) < 0){

                            double percentage = 0.20;
                            getData()->getActiveCharacter()->setGold(0);
                            double check = static_cast<int>(getData()->getActiveCharacter()->getHP() * percentage);
                            if(check < 1){

                                check = 1;
                            }
                            getData()->getActiveCharacter()->loseHP(check);
                            if(getData()->getActiveCharacter()->getHP() <= 0){

                                msg += "You don't have enough to pay the fine.\nYou lose what you have and are beaten to within an inch of your life.";
                                getData()->getActiveCharacter()->setHP(1);
                            }
                            else{
                                msg += "You don't have enough to pay the fine.\nYou lose what you have and are beaten. " + std::to_string(static_cast<int>(check)) + " HP lost.";
                            }

                            msg += "\n" + npc->getFactionStr() + " faction rep down";
                            getData()->getActiveCharacter()->loseRep(npc->getFaction(), 3);
                            getActiveCharacter()->gainXP();
                        }
                        else{
                            msg += "You are caught and lose " + std::to_string(gold) + " gold";
                            getData()->getActiveCharacter()->gainGold(-gold);
                            msg += "\n" + npc->getFactionStr() + " faction rep down";
                            getData()->getActiveCharacter()->loseRep(npc->getFaction(), 3);
                            getActiveCharacter()->gainXP();
                        }
                    }
                    else{

                        msg += "You avoid detection.";
                        getActiveCharacter()->gainXP();
                    }

                    getEnemyText()->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                    getDynamicText()->setString("EXP Gained", true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                }

}

void RandomEncounter::barter()
{

}

