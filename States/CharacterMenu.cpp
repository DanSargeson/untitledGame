#include "CharacterMenu.h"
#include "Engine.h"
#include "Input.h"

CharacterMenu::CharacterMenu(){

    invMenu2 = std::make_shared<GUI::Menu>();
    ops = StateData::GetInstance()->getActiveCharacter()->getInvAsVec();

    std::cout << getData()->getActiveCharacter()->getInvAsString() << endl;

    backButton->setActive(true);
    initButtons();

    getMainText()->setFontSize(20);
    if(!ops.empty()){

        if(ops[0] == "You have no items"){

            menu->setMenuOptions(ops, true, true);
            menu->setActive(true);
        }
        else{
        std::cout << ops[0] <<std::endl;
        checkItemStrength();
        menu->setMenuOptions(ops, true, true);
        menu->setActive(true);
        }
    }

    std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
    getMainText()->setString(mmm, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
    invMenu2->setActive(false);
    choice = -1;
    //getMainText()->setPosition(GUI::p2pXi(5), GUI::p2pYi(5), GUI::p2pXi(80), GUI::p2pYi(80));
    ///getMainText() = std::make_shared<GUI::Text>(5, 5, 89, 60, true);
    ///getMainText()->setString(StateData::GetInstance()->getActiveCharacter()->printPlayerDetails(), true, GUI::p2pY(120));
    ///mButtons["ATTRIBUTES"]->setSelected(true);
}

void CharacterMenu::checkItemStrength(){

    getActiveCharacter()->sortItems();
    for(size_t i = 0; i < ops.size(); i++){

        std::shared_ptr<Item> wv;
        if(mButtons["WEAPONS"]->getSelected()){

            wv = getData()->getActiveCharacter()->findWeapon(i);
        }
        else if(mButtons["ARMOURS"]->getSelected()){

            wv = getData()->getActiveCharacter()->findArmour(i);
        }
        else{

            wv = getData()->getActiveCharacter()->findItem(i);
        }

        if(wv->getItemType() == WEAPON){
            if(getActiveCharacter()->getActiveWeapon() != nullptr){

                if(dynamic_cast<Weapon&>(*wv).getDamageMax() > getData()->getActiveCharacter()->getActiveWeapon()->getDamageMax()){ ///TODO: CHECK MIN AS WELL

                    ops[i] += " *";
                }
            }
            else {
                    ops[i] += " *";
            }
        }
        else if(wv->getItemType() == ARMOUR){

            int itemType = dynamic_cast<Armour&>(*wv).getType();

            switch(itemType){

            case armourType::HEAD:

                if(getData()->getActiveCharacter()->getActiveHead() != nullptr){

                if(dynamic_cast<Armour&>(*wv).getDefenceMax() > getData()->getActiveCharacter()->getActiveHead()->getDefenceMax()){

                        ops[i] += " *";
                    }
                }
                else{

                    ops[i] += " *";
                }
                    break;


            case armourType::CHEST:

                if(getData()->getActiveCharacter()->getActiveChest() != nullptr){


                if(dynamic_cast<Armour&>(*wv).getDefenceMax() > getData()->getActiveCharacter()->getActiveChest()->getDefenceMax()){

                        ops[i] += " *";
                    }
                }
                else{

                    ops[i] += " *";
                }
                    break;


            case armourType::ARMS:

                  if(getData()->getActiveCharacter()->getActiveArms() != nullptr){


                if(dynamic_cast<Armour&>(*wv).getDefenceMax() > getData()->getActiveCharacter()->getActiveArms()->getDefenceMax()){

                        ops[i] += " *";
                    }
                  }
                  else{

                    ops[i] += " *";
                }
                    break;

            case armourType::LEGS:

                if(getData()->getActiveCharacter()->getActiveLegs() != nullptr){

                if(dynamic_cast<Armour&>(*wv).getDefenceMax() > getData()->getActiveCharacter()->getActiveLegs()->getDefenceMax()){

                        ops[i] += " *";
                    }
                }
                else{

                    ops[i] += " *";
                }
                    break;

            default:
                ops[i] += " *";
                break;
            }
        }   //EMD ARMOUR CHECK
    }
}

CharacterMenu::~CharacterMenu(){

//    State::~State();
//    menu.reset();

    ops.clear();
    State::refreshGUI();
    //getMainText()->setFontSize(24);
//    invMenu2.reset();
}

void CharacterMenu::refreshGUI(){

    State::refreshGUI();
    invMenu2->refreshGUI();
    initButtons();
}

void CharacterMenu::update(const float& dt){

    ///checkItemStrength();
    menu->update();
    invMenu2->update();
    backButton->update();

    for(auto button : mButtons){

        button.second->update();
    }
}

void CharacterMenu::craft(){

}

void CharacterMenu::runMenuSelection(){

    std::vector<std::string> ops2;
     ///RUN MENU SELECTION
        if(menu->isSelected() && menu->getActive() && ops[0] != "You have no items"){

            if(ops[0] == "You have no armour" || ops[0] == "You have no weapons"){

                return;
            }

                choice = menu->getChoice();

                switch(getActiveCharacter()->getItem(choice)->getItemType()){

            case itemTypes::WEAPON:
                ops2.push_back("Equip Item");
                ops2.push_back("Equip on follower");
                break;

            case itemTypes::ARMOUR:
                ops2.push_back("Equip Item");
                ops2.push_back("Equip on follower");
                break;

            case itemTypes::RESOURCE:
                ops2.push_back("Craft");
                break;

            case itemTypes::KEY:
                ops2.push_back("Use");
                break;

            case itemTypes::POTION:
                ops2.push_back("Use");
                ops2.push_back("Use on follower");
                break;

                default:
                    break;
                }

//                if(getActiveCharacter()->getItem(choice)->getItemType() == itemTypes::WEAPON || getActiveCharacter()->getItem(choice)->getItemType() == itemTypes::ARMOUR){
//
//                    ops2.push_back("Equip Item");
//                }
                ops2.push_back("Drop Item");

                menu->setActive(false);
                invMenu2->setMenuOptions(ops2, true);
                invMenu2->setActive(true);


                std::string msg;
                if(mButtons["ARMOURS"]->getSelected()){

                        msg = getActiveCharacter()->getArmAsString(choice);
                        //initButtons();
                }
                else if(mButtons["WEAPONS"]->getSelected()){
                    //getActiveCharacter()->sortWepByStr();
                    msg = getActiveCharacter()->getWepAsString(choice);
                    //initButtons();
                }
                else{
                    //getActiveCharacter()->sortWepByStr();
                    msg = StateData::GetInstance()->getActiveCharacter()->getInvItemAsString(choice);
                }

                getMainText()->setString(msg, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                //mStateData::getInstane
        ///            std::cout << invMenu->getChoice() << std::endl;

            return;

        }   //FIRST MENU ENDS HERE



    ///THIS IS THE ONE111 else{

     //INV MENU2 STARTS HERE


        if(invMenu2->isSelected() && invMenu2->getActive()){
            std::cout << "CHOICE: " << choice << std::endl;
            auto wv = StateData::GetInstance()->getActiveCharacter()->findItem(choice);
            int cc = invMenu2->getChoice();
            //if(invMenu2->getChoice() == 0){

                //if(wv->getItemType() == WEAPON){

//                if(wv->getItemType() == itemTypes::WEAPON || wv->getItemType() == itemTypes::ARMOUR){
//
//
//
//
//
////                if(cc == 0){        ///Equip item
////
////                    if(mButtons["WEAPONS"]->getSelected()){
////
////                        getActiveCharacter()->equipWeapon(choice);
////
////                        mButtons["WEAPONS"]->setSelected(false);
////                        mButtons["ARMOURS"]->setSelected(false);
////                        mButtons["ALL"]->setSelected(true);
////                    }
////                    else if(mButtons["ARMOURS"]->getSelected()){
////
////                        getActiveCharacter()->equipArmour(choice);
////                        mButtons["WEAPONS"]->setSelected(false);
////                        mButtons["ARMOURS"]->setSelected(false);
////                        mButtons["ALL"]->setSelected(true);
////                    }
////                    else{
////
////                        StateData::GetInstance()->getActiveCharacter()->equipItem(choice);
////                    }
////                }
//                if(cc == 1){ ///USE ON FOLLOWER
//
//
//                }
//
//                if(cc == 2){
//
//                    getData()->getActiveCharacter()->removeItem(wv);
//                }
//
//
//                    ///ENDS WEAPON/ARMOUR CHECK
//                }
                //else{

                    if(cc == 0){

                    switch(wv->getItemType()){

                    case itemTypes::WEAPON:
                        if(mButtons["WEAPONS"]->getSelected()){

                            getActiveCharacter()->equipWeapon(choice);

                            mButtons["WEAPONS"]->setSelected(false);
                            mButtons["ARMOURS"]->setSelected(false);
                            mButtons["ALL"]->setSelected(true);
                        }
                        else{

                            StateData::GetInstance()->getActiveCharacter()->equipItem(choice);
                        }
                        break;

                    case itemTypes::ARMOUR:

                        if(mButtons["ARMOURS"]->getSelected()){

                            getActiveCharacter()->equipArmour(choice);
                            mButtons["WEAPONS"]->setSelected(false);
                            mButtons["ARMOURS"]->setSelected(false);
                            mButtons["ALL"]->setSelected(true);
                        }
                        else{

                            StateData::GetInstance()->getActiveCharacter()->equipItem(choice);
                        }
                    break;


                        case itemTypes::KEY:
                            getDynamicText()->setString("Use keys on the world map when you find a chest");
                            break;

                        case itemTypes::RESOURCE:
                            getDynamicText()->setString("Developer needs to work on empty craft function...");
                            break;

                        default:
                            getDynamicText()->clearText();
                            break;
                        }
                    }

                    if(cc == 1){  ///Drop item

                        if(wv->getItemType() == itemTypes::WEAPON || wv->getItemType() == itemTypes::ARMOUR){

                            getDynamicText()->setString("EQUIP FOLLOWER GEAR AT SOME POINT");
                        }
                        else{

                            getData()->getActiveCharacter()->removeItem(wv);
                        }
                    }


                getActiveCharacter()->sortItems();
                if(mButtons["WEAPONS"]->getSelected()){

                    ops = getActiveCharacter()->getWepAsVec();
                }
                else if(mButtons["ARMOURS"]->getSelected()){

                    ops = getActiveCharacter()->getArmAsVec();
                }
                else{

                    ops = StateData::GetInstance()->getActiveCharacter()->getInvAsVec();
                }
                checkItemStrength();
                menu->setMenuOptions(ops, true, true);
                std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
                getMainText()->setString(mmm, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));


            if(ops[0] == "You have no items" || ops[0] == "You have no weapons" || ops[0] == "You have no armour"){

                menu->setMenuOptions(ops, false, false);
            }
            else{

                menu->setMenuOptions(ops, true, true);
            }
            menu->setActive(true);
            invMenu2->setActive(false);
    }

    ///END RUN MENU SELECTION
}

void CharacterMenu::updateEvents(SDL_Event& e){

    if(menu->getActive()){

        menu->updateEvents(e);
    }
    if(invMenu2->getActive()){

        invMenu2->updateEvents(e);
    }

    if(backButton->isActive() && backButton->isPressed(e.button)){

        if(invMenu2->getActive()){

            invMenu2->setActive(false);
            menu->setActive(true);
        }
        else{

            Engine::GetInstance()->PopState();
        }


        return;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN) && e.key.repeat == 0){

        if(getDynamicText()->getString() != ""){
            getDynamicText()->clearText();
        }
        runMenuSelection();
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){

        if(!menu->cursorDetached() || !SDL_ShowCursor(SDL_QUERY)){

            runMenuSelection();
        }
//        if(!invM->cursorDetached() || !SDL_ShowCursor(SDL_QUERY)){
//
//            runMenuSelection();
//        }
        //BUTTONS START HERE
        if (mButtons["WEAPONS"]->isPressed(e.button)) {

            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));

            menu->setActive(true);
            invMenu2->setActive(false);

            mButtons["WEAPONS"]->setSelected(true);
            mButtons["ARMOURS"]->setSelected(false);
            mButtons["ALL"]->setSelected(false);

            getActiveCharacter()->sortWepByStr();
            ops = getActiveCharacter()->getWepAsVec();
            if(ops[0] != "You have no weapons"){

                checkItemStrength();
                menu->setMenuOptions(ops, true, true, true);
            }
            else{

                menu->setMenuOptions(ops, false, false);
            }
        }

        if (mButtons["ALL"]->isPressed(e.button)) {

            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));

            mButtons["WEAPONS"]->setSelected(false);
            mButtons["ARMOURS"]->setSelected(false);
            mButtons["ALL"]->setSelected(true);

            menu->setActive(true);
            invMenu2->setActive(false);
            getActiveCharacter()->sortWepByStr();
            ops = getActiveCharacter()->getInvAsVec();
            if(ops[0] != "You have no items"){

                checkItemStrength();
                menu->setMenuOptions(ops, true, true);
            }
            else{
                menu->setMenuOptions(ops, false, false);
            }
        }

        if (mButtons["ARMOURS"]->isPressed(e.button)) {

            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));

            mButtons["WEAPONS"]->setSelected(false);
            mButtons["ARMOURS"]->setSelected(true);
            mButtons["ALL"]->setSelected(false);

            menu->setActive(true);
            invMenu2->setActive(false);
            getActiveCharacter()->sortWepByStr();
            ops = getActiveCharacter()->getArmAsVec();
            if(ops[0] != "You have no armour"){

                checkItemStrength();
                menu->setMenuOptions(ops, true, true, false, true);
            }
            else{

                menu->setMenuOptions(ops, false, false);
            }
        }
        //BUTTONS END HERE
    }

    if(invMenu2->getActive() == false){
        State::updateEvents(e);
    }
    else{

        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){

            mButtons["WEAPONS"]->setSelected(false);
            mButtons["ARMOURS"]->setSelected(false);
            mButtons["ALL"]->setSelected(true);
            invMenu2->setActive(false);
            menu->setActive(true);
            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
            getActiveCharacter()->sortItems();
            ops = getActiveCharacter()->getInvAsVec();
            checkItemStrength();
            menu->setMenuOptions(ops, true, true);
        }
    }
}

void CharacterMenu::render(){

    getMainText()->render();

    if(getDynamicText()->getString() != ""){

        getDynamicText()->render();
    }

    if(menu->getActive()){
        menu->render();
    }
    if(invMenu2->getActive()){
        invMenu2->render();
    }

    for (auto i : mButtons) {

		i.second->renderButtons();
	}



    backButton->renderButtons();
}

void CharacterMenu::initButtons(){

    unsigned int charSize = GUI::calcCharSize(125);


    mButtons["WEAPONS"] = new GUI::Button(27.f, 65.5f, 11.8f, 4.1f, charSize);
    mButtons["WEAPONS"]->setRenderText("Weapons");

    mButtons["ARMOURS"] = new GUI::Button(42.f, 65.5f, 11.8f, 4.1f, charSize);
    mButtons["ARMOURS"]->setRenderText("Armour");

    mButtons["ALL"] = new GUI::Button(57.f, 65.5f, 11.8f, 4.1f, charSize);
    mButtons["ALL"]->setRenderText("All");

    mButtons["WEAPONS"]->setSelected(false);
    mButtons["ARMOURS"]->setSelected(false);
    mButtons["ALL"]->setSelected(true);

     mButtons["WEAPONS"]->setBackgroundTexture("Assets/Background/button2.png");
    mButtons["ARMOURS"]->setBackgroundTexture("Assets/Background/button2.png");
    mButtons["ALL"]->setBackgroundTexture("Assets/Background/button2.png");
}
