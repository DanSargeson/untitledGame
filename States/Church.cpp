#include "Church.h"

int Church::basinLevel = 4;  ///Basin starts full and gets 4 uses..
int Church::timeBasinEmptied = 0; ///Not used for now..
int Church::dayBasinEmptied = 0;


Church::Church() : State(){

    ///HERE BE Dialogue stuff..

    inDialogue = false;
    m_fileName = "Assets/factionQuests.txt";

    ///"Assets/newDialogue.txt"

    if(getActiveCharacter()->getBasinLevel() != basinLevel){

        basinLevel = getActiveCharacter()->getBasinLevel();
        dayBasinEmptied = getActiveCharacter()->getDayBasinEmptied();
    }

    json_file = "Assets/diag.json";

    file = std::make_shared<LoadFiles>(m_fileName, 1);

    /*This bit is the first bit of text... I think*/
    file->readJsonFile2(json_file);

    /*
        HERE ENDETH THE DIALOGUE
    */

    firstFlag = false;
    satan = std::make_shared<NPC>(1, 100, 1);
    satan->setName("Lucifer");
//    atPulpit = false;
//    atBasin = false;

    currentArea = AREA::entrance;

    mainMsg = "You enter the church, dominating the front of the room is a pulpit adorned with some kind of animal horns."
                "\n\nThere is a basin near the entrance, it seems to be filled with a dark red, viscous liquid."
                "\n\nMetallic benches fill the main hall. The floor seems to writhe as you step on it.";
    getMainText()->setString(mainMsg, true);
    ///

    ///TODO BRING THESE BACK...
    ops.clear();
    ops.push_back("Approach the pulpit");
    ops.push_back("Approach the basin");
    menu->setMenuOptions(ops, true);

    backButton->setActive(true);

    unsigned int charSize = GUI::calcCharSize(125);

    randomNPC = std::make_shared<NPC>(0, getActiveCharacter()->getLevel(), getRandomValue(2, 8));
}

Church::~Church(){

    backButton->setActive(true);
}




void Church::update(const float& dt){

    //mButtons["BACK"]->update();

    if(basinLevel == 0 && getActiveCharacter()->getDaysPassed() > dayBasinEmptied){ //Basin level resets at midnight

        basinLevel = 4;
        dayBasinEmptied = 0;
        getActiveCharacter()->setChurchBasinLevels(4, 0);
    }

    if(currentArea == AREA::pulpit && !inDialogue){

        std::string msg = "";
        if (!getData()->isDay) {
            msg = satan->getName() + " sits at the front of the church looking bored.";
        }
        else{
            msg = "No one is around, maybe you should try at night??";
        }
        getMainText()->setString(msg, true);

        ///HERE == THIS SHOULD DEFINITELY OO INTO SOME KIND OF DAY/NIGHT CLASS, take 2 integers to check if it is currently X time....
        // Check if it's midnight and increment the day counter
            if (static_cast<int>(getData()->hours) == 18 && getData()->minutes == 0) {
                if (!firstFlag) {  // First encounter with night

                    firstFlag = true; // Flag to prevent multiple increments
                    updatePulpitOptions();
                }
            }
            else if(static_cast<int>(getData()->hours) == 6 && getData()->minutes == 0){

                if (!firstFlag) {  // First encounter with day

                    firstFlag = true; // Flag to prevent multiple increments
                    updatePulpitOptions();
                }
            }
            else {
                firstFlag = false; // Reset flag when time moves past 00:00
            }
        ///HERE
    }

    if(currentArea == AREA::basin){

        std::string msg = "The basin is filthy, there is a red viscous liquid shimmering in the bowl.\nThe Basin is";
        switch(basinLevel){

        case 0:
            msg += " empty";
            break;

        case 1:
            msg += " nearly empty";
            break;

        case 2:
            msg += " about half full";
            break;

        case 3:
            msg += " mostly full";
            break;

        case 4:
            msg += " full to the brim";
            break;
        }
        getMainText()->setString(msg, true);
    }

    backButton->update();
    getActiveCharacter()->getWorldTimer()->update(dt);
    calcWorldTime();
    menu->update();
}

void Church::updateEvents(SDL_Event& e){

    if(backButton->isPressed(e.button)){

        Engine::GetInstance()->PopState();
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){

            getDynamicText()->clearText();
            getEnemyText()->clearText();

        if(menu->isSelected() && menu->getActive()){

            runMenuSelection();
        }
    }

    if(menu->getActive()){

        menu->updateEvents(e);
    }
    State::updateEvents(e);
}

void Church::runMenuSelection() {

    if(inDialogue){

        ///TODO: HANDLE DIALOGUE...
        file->selectResponse("Lucifer", 1, (menu->getChoice() + 1));

        if(file->getCurrDiagID() == 666){

            inDialogue = false;
            menu->reset();
            currentArea = AREA::pulpit;
            updatePulpitOptions();
            //handlePulpit();
        }
        else{


        std::string msg2 = file->getDialogue("Lucifer", file->getCurrDiagID());

        getMainText()->setString(msg2, true);
        menu->setMenuOptions(file->getPlayerOps(), true);

        }

    }
    else{


    switch (currentArea) {
        case AREA::entrance:
            handleEntrance();
            break;
        case AREA::pulpit:
            handlePulpit();
            break;
        case AREA::basin:
            handleBasin();
            break;
    }
    }
}

void Church::handleEntrance() {
    getMainText()->setString(mainMsg, true);
    std::vector<std::string> ops = {"Approach the pulpit", "Approach the basin"};
    menu->setMenuOptions(ops, true);
    if (menu->getChoice() == 0) { // Approach the pulpit
        currentArea = AREA::pulpit;
        menu->reset();  // Reset menu to avoid old choices affecting new area
        updatePulpitOptions();
    } else if (menu->getChoice() == 1) { // Approach the basin
        currentArea = AREA::basin;
        menu->reset();  // Reset menu for new area
        updateBasinOptions();
    }
}

void Church::handlePulpit() {

    if(!inDialogue){

            handleDialogue();
    }
    else{

        runMenuSelection();
    }
}

void Church::handleDialogue(){

    if (menu->getChoice() == 0) { // Speak or go to basin based on time of day
        if (!getData()->isDay) {

            inDialogue = true;
            getMainText()->setString(file->getDialogue("Lucifer", 1), true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
            menu->setMenuOptions(file->getFirstResponses("Lucifer", 1), true);

        } else {
            currentArea = AREA::basin;
            menu->reset();
            updateBasinOptions();
        }
    } else if (menu->getChoice() == 1) { // Back to entrance if DAY, otherwise goes to basin...
        if(getData()->isDay){

        currentArea = AREA::entrance;
        menu->reset();  // Reset menu for new area
        handleEntrance();
        }
        else{
            currentArea = AREA::basin;
            menu->reset();
            updateBasinOptions();
        }
    }
    else{
        ///DIALOGUE BIT HERE
        currentArea = AREA::entrance;
        menu->reset();
        handleEntrance();
    }
}

void Church::handleBasin() {
    updateBasinOptions();
    if(menu->getChoice() == 0){ ///DRINK THE LIQUID!!
        if(basinLevel > 0){

            if(chancePassed(25, getActiveCharacter()->getSkill(8))){   ///TODO, add skillModifier???

                    getDynamicText()->setString("You feel stronger (or some other thing that doesn't work yet)!");
            }
            else{
                getEnemyText()->setString("You feel weaker (or some other thing that doesn't work yet)!");
            }

            basinLevel--;
            if(basinLevel == 0){

                dayBasinEmptied = getActiveCharacter()->getDaysPassed();
            }

            getActiveCharacter()->setChurchBasinLevels(basinLevel, dayBasinEmptied);
        }
        else{

            getEnemyText()->setString("There is nothing left to drink");
        }

        menu->reset();
        updateBasinOptions();
    }

    if (menu->getChoice() == 1) { // Go to pulpit
        currentArea = AREA::pulpit;
        menu->reset();  // Reset menu for new area
        updatePulpitOptions();
    } else if (menu->getChoice() == 2) { // Back to entrance
        currentArea = AREA::entrance;
        menu->reset();  // Reset menu for new area
        handleEntrance();
    }
}

void Church::updatePulpitOptions() {
    std::string speak;
    std::vector<std::string> ops;

    if (!getData()->isDay) {

        speak = "Speak to " + satan->getName();
        ops.push_back(speak);
    }
    ops.push_back("Approach the basin");
    ops.push_back("Back to entrance");
    menu->setMenuOptions(ops, true);
}

void Church::updateBasinOptions() {


    //std::vector<std::string> ops = {"Drink the liquid", "Approach the pulpit", "Back to entrance"};
    ops.clear();
    std::string o1 = "Drink the liquid (" + std::to_string(25 + getActiveCharacter()->getSkill(8)) + "%)";
    ops.push_back(o1);
    ops.push_back("Approach the pulpit");
    ops.push_back("Back to the entrance");
    menu->setMenuOptions(ops, true);
}

void Church::render(){

    getMainText()->render();
    getDynamicText()->render();
    getEnemyText()->render();

//    for(auto button : mButtons){
//
//        button.second->renderButtons();
//    }

    backButton->renderButtons();
    menu->render();
    worldTimerText->render();
}
