#include "followerMenu.h"
#include "Engine.h"
#include "Input.h"
#include "Texture.h"

FollowerMenu::FollowerMenu(){

    ops.clear();
    invMenu2 = std::make_shared<GUI::Menu>();
    int t = getActiveCharacter()->getFollowers().size();
    for(size_t i = 0; i < getActiveCharacter()->getFollowers().size(); i++){

        std::string temp = getActiveCharacter()->getFollowers()[i]->getName();
        ops.push_back(temp);
    }
    //ops = StateData::GetInstance()->getActiveCharacter()->getFollowers();

    menu->setActive(false);

    /*
        START NEW GUI
    */


    followerIcons = std::make_unique<Texture>();
    followerIcons->loadFromFile("Assets/icons.png", Engine::GetInstance()->GetRenderer());
    bardRect = { 0, 0, 100, 100 };
    doctorRect = {106, 0, 100, 100};
    innkeeperRect = {206, 0, 100, 100};
    blacksmithRect = {309, 0, 100, 100};
    alchemistRect = {0, 101, 100, 100};
    mummerRect = { 106, 101, 100, 100 };
    prospectorRect = {206, 101, 100, 100};

    initFollowerList();




//    for(int i = 0; i < followerText.size(); i++){
//
//        followerText[i]->setPosition(180, (i+1)*78);
//    }

    ///getMainText()->setString(getActiveCharacter()->printFollowers(), true);
    ///std::cout << getData()->getActiveCharacter()->getInvAsString() << endl;

    backButton->setActive(true);
    initButtons();

    getMainText()->setFontSize(20);
    if(!ops.empty()){

        if(ops[0] == "You have no items"){

            menu->setMenuOptions(ops, true, true);
            //menu->setActive(true);
        }
        else{
        std::cout << ops[0] <<std::endl;
        menu->setMenuOptions(ops, true);
        //menu->setActive(true);
        }
    }

    ///std::string mmm = StateData::GetInstance()->getActiveCharacter()->printFollowers();
    ///getMainText()->setString(mmm, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
    invMenu2->setActive(false);
    choice = -1;
    //getMainText()->setPosition(GUI::p2pXi(5), GUI::p2pYi(5), GUI::p2pXi(80), GUI::p2pYi(80));
    ///getMainText() = std::make_shared<GUI::Text>(5, 5, 89, 60, true);
    ///getMainText()->setString(StateData::GetInstance()->getActiveCharacter()->printPlayerDetails(), true, GUI::p2pY(120));
    ///mButtons["ATTRIBUTES"]->setSelected(true);
}

void FollowerMenu::initFollowerList(){

    invSlotVec.clear();
    if(getActiveCharacter()->getFollowers().empty()){

        getMainText()->setString("You have no followers!");

        return;
    }
    followerText = getActiveCharacter()->getFollowersAsStrVec();

    std::cout << followerText[0]->getString();
    battleButton = std::make_unique<GUI::Button>(37.f, 10.f, 9.f, 5.f, 20);
    battleButton->setRenderText("Send into Battle");
    battleButton->setBackgroundTexture("Assets/Background/button2.png");
    for(size_t i = 0; i < 5; i++){

        invSlotVec.push_back(std::make_unique<GUI::InvSlot>());
        invSlotVec[i]->setPosition(GUI::p2pX(6), (i+1)*GUI::p2pY(9));
        invSlotVec[i]->setDimensions(GUI::p2pX(30), GUI::p2pY(7));
        if(i < followerText.size()){

            invSlotVec[i]->setText(followerText[i]->getString());
            int c = getActiveCharacter()->getFollowers()[i]->getType();
            switch(c){

            case 0:
                //followerIcons->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, &doctorRect, &invSlotVec[i]);
                invSlotVec[i]->setTileSheet("Assets/icons.png", &doctorRect);
                break;

            case 1:
                //followerIcons->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, &blacksmithRect, &invSlotVec[i]);
                invSlotVec[i]->setTileSheet("Assets/icons.png", &blacksmithRect);
                break;

            case 2:
                //followerIcons->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, &prospectorRect, &invSlotVec[i]);
                invSlotVec[i]->setTileSheet("Assets/icons.png", &prospectorRect);
                break;

            case 3:
                //followerIcons->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, &mummerRect, &invSlotVec[i]);
                invSlotVec[i]->setTileSheet("Assets/icons.png", &mummerRect);
                break;

            case 4:
                //followerIcons->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, &alchemistRect, &invSlotVec[i]);
                invSlotVec[i]->setTileSheet("Assets/icons.png", &alchemistRect);
                break;

            case 5:
                //followerIcons->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, &innkeeperRect, &invSlotVec[i]);
                invSlotVec[i]->setTileSheet("Assets/icons.png", &innkeeperRect);
                break;

            case 6:
                //followerIcons->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, &bardRect, &invSlotVec[i]);
                invSlotVec[i]->setTileSheet("Assets/icons.png", &bardRect);
                break;

            }
        }

        ///SET CORRECT TEXT FOR ACTIVE BUTTON:
        int ii = getActiveCharacter()->getActiveFollower()->getType();
        switch(ii){

            case 0:
                ///DOCTOR
                battleButton->setRenderText("Send for health");
                break;

            case 1:
                ///BLACKSMITH
                battleButton->setRenderText("Send for Iron");
                break;

            case 2:
                ///LOCKSMITH
                battleButton->setRenderText("Search for keys");
                break;

            case 3:
                ///MUMMER
                battleButton->setRenderText("Search for maps");
                break;

            case 4:
                ///ALCHEMIST
                battleButton->setRenderText("Search for potions");
                break;

            case 5:
                ///INNKEEPER
                battleButton->setRenderText("Search for booze");
                break;

            case 6:
                ///BARD
                battleButton->setRenderText("Send into battle");
                break;
        }
    }


}

FollowerMenu::~FollowerMenu(){

//    State::~State();
//    menu.reset();

    ops.clear();
    State::refreshGUI();
    //getMainText()->setFontSize(24);
//    invMenu2.reset();
}

void FollowerMenu::refreshGUI(){

    State::refreshGUI();
    invMenu2->refreshGUI();
    initButtons();
    initFollowerList();
}

void FollowerMenu::update(const float& dt){

    State::update(dt);
    battleButton->update();
    ///checkItemStrength();
    invMenu2->update();
    menu->update();

    if(getData()->refreshFollowerList){

        getData()->refreshFollowerList = false;
        initFollowerList();
    }

    for(size_t i = 0; i < invSlotVec.size(); i++){

        invSlotVec[i]->update();
    }

    backButton->update();

    getActiveCharacter()->getWorldTimer()->update(dt);
    calcWorldTime();

    if(!getActiveCharacter()->getFollowers().empty()){


        followerText = getActiveCharacter()->getFollowersAsStrVec();
        invSlotVec[0]->setText(followerText[0]->getString());
    }
}

void FollowerMenu::runMenuSelection(){

     ///RUN MENU SELECTION
        if(menu->isSelected() && menu->getActive() && ops[0] != "You have no followers"){

                choice = menu->getChoice();
                std::vector<std::string> ops2;
                ops2.push_back("Make Active Follower");
                ops2.push_back("Dismiss Follower");

                menu->setActive(false);
                invMenu2->setMenuOptions(ops2, true);
                invMenu2->setActive(true);


                std::string msg;
                msg = getActiveCharacter()->getFollowers()[choice]->getStatsAttributeScreen();
                getMainText()->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));

            return;

        }   //FIRST MENU ENDS HERE



    ///THIS IS THE ONE111 else{

     //INV MENU2 STARTS HERE

        std::lock_guard<std::mutex> lock(StateData::GetInstance()->mtx);
        if(invMenu2->getActive() && invMenu2->isSelected()){
            std::cout << "CHOICE: " << choice << std::endl;
            ///auto wv = StateData::GetInstance()->getActiveCharacter()->findItem(choice);
            int cc = invMenu2->getChoice();
            //if(invMenu2->getChoice() == 0){

                //if(wv->getItemType() == WEAPON){

                if(cc == 0){        ///swap

                    if(!getData()->battleThreadRunning.load()){

                        getActiveCharacter()->swapActiveFollower(choice);
                        int i = getActiveCharacter()->getActiveFollower()->getType();
                        switch(i){

                             case 0:
                                ///DOCTOR
                                battleButton->setRenderText("Send for health");
                                break;

                            case 1:
                                ///BLACKSMITH
                                battleButton->setRenderText("Send for Iron");
                                break;

                            case 2:
                                ///PROSPECTOR
                                battleButton->setRenderText("Send for gold");
                                break;

                            case 3:
                                ///MUMMER
                                battleButton->setRenderText("Search for maps");
                                break;

                            case 4:
                                ///ALCHEMIST
                                battleButton->setRenderText("Search for potions");
                                break;

                            case 5:
                                ///INNKEEPER
                                battleButton->setRenderText("Search for booze");
                                break;

                            case 6:
                                ///BARD
                                battleButton->setRenderText("Send into battle");
                                break;
                        }
                        ops.clear();
                    }
                    else{

                        getEnemyText()->setString("You already have a follower in battle!");
                        ops.clear();
                    }
                }
                if(cc == 1){  ///Dismiss follower

                    if(!getData()->battleThreadRunning.load()){

                        getActiveCharacter()->removeFollower(getActiveCharacter()->getFollowers()[choice]);
                        ops.clear();
                    }
                    else{

                        if(choice != 0){

                            getActiveCharacter()->removeFollower(getActiveCharacter()->getFollowers()[choice]);
                            ops.clear();
                        }
                        else{

                            getEnemyText()->setString("Follower is currently in battle!");
                            ops.clear();
                        }
                    }
                }

                if(cc == 2){ ///HEAL FOLLOWER

                    if(!getActiveCharacter()->getFollowers()[choice]->fullHealth()){


                        std::string msg = "";
                        if(getActiveCharacter()->getGold() >= 10){
                            getActiveCharacter()->gainGold(-10);
                            msg += getActiveCharacter()->getFollowers()[choice]->getName() + " healed!";
                            getActiveCharacter()->getFollowers()[choice]->resetHP();
                        }
                        else{
                            msg += "You do not have enough gold!";
                        }
                        getDynamicText()->setString(msg, true);
                        ops.clear();
                    }
                    else{

                        std::string msg = getActiveCharacter()->getFollowers()[choice]->getName() + " already has full health!";
                        getEnemyText()->setString(msg, true);
                        ops.clear();
                    }
                }

                if(cc == 3){ ///EQUIP ITEM

                    getEnemyText()->setString("DOESN'T WORK YET!");
                    ops.clear();
                }

                for(size_t i = 0; i < getActiveCharacter()->getFollowers().size(); i++){

                    std::string temp = getActiveCharacter()->getFollowers()[i]->getName();
                    ops.push_back(temp);
                }

                initFollowerList();
                menu->setMenuOptions(ops, true);
               // std::string mmm = StateData::GetInstance()->getActiveCharacter()->printFollowers();
                //getMainText()->setString(mmm, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));


            if(ops[0] == "You have no followers"){

                menu->setMenuOptions(ops, false, false);
            }
            else{

                menu->setMenuOptions(ops, true);
            }
            //menu->setActive(true);
            initFollowerList();
            invMenu2->setActive(false);
    }

    ///END RUN MENU SELECTION
}

void FollowerMenu::updateEvents(SDL_Event& e){

    invMenu2->updateEvents(e);
    menu->updateEvents(e);

    if(backButton->isActive() && backButton->isPressed(e.button)){

        if(invMenu2->getActive()){

            invMenu2->setActive(false);
            ///menu->setActive(true);
        }
        else{

            Engine::GetInstance()->PopState();
        }


        return;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN) && e.key.repeat == 0){


//        if(getFollowerText()->getString() != ""){
//
//            getFollowerText()->clearText();
//        }

        runMenuSelection();
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){

        int x, y = 0;
        SDL_GetMouseState(&x, &y);
//        for(int i = 0; i < invSlotVec.size(); i++){
//
//            if(invSlotVec[i]->getTexture()->intersects(x, y)){
//
//
//                std::vector<std::string> ops2;
//                ops2.push_back("Make Active Follower");
//                ops2.push_back("Dismiss Follower");
//
//                menu->setActive(false);
//                invMenu2->setMenuOptions(ops2, true);
//                invMenu2->setActive(true);
//                invMenu2->setActive(true);
//                std::string msg;
//                msg = getActiveCharacter()->getFollowers()[i]->getStatsAttributeScreen();
//                getMainText()->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
//                choice = i;
//                return;
//            }
//        }   ///END CHECKING TEXT VECTOR

        if(getDynamicText()->getString() != "" || getEnemyText()->getString() != ""){

            getDynamicText()->setString("");
            getEnemyText()->setString("");
        }

        for(size_t i = 0; i < invSlotVec.size(); i++){
            if(i < getActiveCharacter()->getFollowers().size()){

            if(invSlotVec[i]->isSelected()){

                std::vector<std::string> ops2;
                ops2.push_back("Make Active Follower");
                ops2.push_back("Dismiss Follower");
                ops2.push_back("Heal Follower");
                ops2.push_back("Equip item");

                menu->setActive(false);
                invMenu2->setMenuOptions(ops2, true);
                invMenu2->setActive(true);
                std::string msg;
                msg = getActiveCharacter()->getFollowers()[i]->getStatsAttributeScreen();
                getMainText()->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                choice = i;
                return;
            }
            }
        }

        if(!menu->cursorDetached() || !SDL_ShowCursor(SDL_QUERY)){

            runMenuSelection();
        }
        //BUTTONS START HERE

        if(battleButton->isPressed(e.button)){

            if(!getData()->battleThreadRunning){

                getData()->followerTimer->restart();
                getData()->startBattleThread();
            }
        }
    }

    if(invMenu2->getActive() == false){
        State::updateEvents(e);
    }
    else{

        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){


            if(invMenu2->getActive()){

                invMenu2->setActive(false);
                ///menu->setActive(true);
            }
            else{

                Engine::GetInstance()->PopState();
            }


            return;
//            invMenu2->setActive(false);
//            //menu->setActive(true);
//          //  std::string mmm = StateData::GetInstance()->getActiveCharacter()->printFollowers();
//           // getMainText()->setString(mmm, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
//            ///getActiveCharacter()->sortItems();
//            ops.clear();
//            for(size_t i = 0; i < getActiveCharacter()->getFollowers().size(); i++){
//
//                std::string temp = getActiveCharacter()->getFollowers()[i]->getName();
//                ops.push_back(temp);
//            }
//
//            menu->setMenuOptions(ops, true);
        }
    }

}

void FollowerMenu::render(){

    getMainText()->render();
    if(getDynamicText()->getString() != ""){

        getDynamicText()->render();
    }

    if(getEnemyText()->getString() != ""){

        getEnemyText()->render();
    }

    if(getFollowerText()->getString() != ""){

        getFollowerText()->render();
    }

    if(getData()->battleThreadRunning){

        timerText->render();
    }

    if(menu->getActive()){
        menu->render();
    }
    if(invMenu2->getActive()){
        invMenu2->render();
    }

    backButton->renderButtons();

    if(!invMenu2->getActive() && !menu->getActive()){

        battleButton->renderButtons();
    }

    if(!invMenu2->getActive()){

        getMainText()->setString("");



//        for(int i = 0; i < followerText.size(); i++){
//
//            followerText[i]->render();
//        }

    for(size_t i = 0; i < invSlotVec.size(); i++){

        invSlotVec[i]->render();
    }
    }

    if(!invMenu2->getActive() && !menu->getActive() && getActiveCharacter()->getFollowers().size() <= 0){

        getMainText()->setString("You have no followers", true);

        getMainText()->render();
        getFollowerText()->render();
        backButton->renderButtons();
    }

     worldTimerText->render();
}

void FollowerMenu::initButtons(){

    unsigned int charSize = GUI::calcCharSize(130);

    battleButton = std::make_unique<GUI::Button>(37.f, 10.f, 9.f, 5.f, charSize);
//    battleButton->setRenderText("Send into Battle");
    battleButton->setBackgroundTexture("Assets/Background/button2.png");

    ///SET CORRECT TEXT FOR ACTIVE BUTTON:

        if(getActiveCharacter()->getActiveFollower() != nullptr){

            int ii = getActiveCharacter()->getActiveFollower()->getType();
            switch(ii){

                case 0:
                    ///DOCTOR
                    battleButton->setRenderText("Send for health");
                    break;

                case 1:
                    ///BLACKSMITH
                    battleButton->setRenderText("Send for Iron");
                    break;

                case 2:
                    ///LOCKSMITH
                    battleButton->setRenderText("Search for keys");
                    break;

                case 3:
                    ///MUMMER
                    battleButton->setRenderText("Search for maps");
                    break;

                case 4:
                    ///ALCHEMIST
                    battleButton->setRenderText("Search for potions");
                    break;

                case 5:
                    ///INNKEEPER
                    battleButton->setRenderText("Search for booze");
                    break;

                case 6:
                    ///BARD
                    battleButton->setRenderText("Send into battle");
                    break;
            }
        }
}
