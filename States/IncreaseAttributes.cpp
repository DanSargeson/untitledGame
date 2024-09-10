#include "IncreaseAttributes.h"
#include "Game.h"
#include "AttributeComponent.h"

//void IncreaseAttributes::initFonts(){
//
//    try{
//
//        font = TTF_OpenFont("Assets/Fonts/SF Atarian System.ttf", 24);
//
//    }
//    catch(exception e){
//
//        std::ofstream outFile;
//
//        outFile.open("errorLog.txt");
//
//        if(outFile.is_open()){
//
//            outFile << e.what() << endl;
//
//            outFile.close();
//        }
//    }
//}

void IncreaseAttributes::initKeyBinds(){


    std::ifstream ifs("Config/gameStateKeyBinds.ini");

    if(ifs.is_open()){

        std::string key = " ";
        std::string key2 = " ";

        while(ifs >> key >> key2){

            //this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void IncreaseAttributes::initGUI(){

    pointsMessage = std::make_unique<GUI::Text>(60, 20, 0, 0, false);

    this->spriteAddTexture = std::make_shared<Texture>();
    spriteAddTexture->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());

    spriteMinusTexture = std::make_shared<Texture>();
    spriteMinusTexture->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());


    this->spriteAddAgility= std::make_shared<Texture>();
    spriteAddAgility->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusAgility = std::make_shared<Texture>();
    spriteMinusAgility->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());

    this->spriteAddCha = std::make_shared<Texture>();
    spriteAddCha->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusCha = std::make_shared<Texture>();
    spriteMinusCha->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());

    this->spriteAddDex = std::make_shared<Texture>();
    spriteAddDex->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusDex = std::make_shared<Texture>();
    spriteMinusDex->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());

    this->spriteAddInt = std::make_shared<Texture>();
    spriteAddInt->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusInt = std::make_shared<Texture>();
    spriteMinusInt->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());

    this->spriteAddLuck= std::make_shared<Texture>();
    spriteAddLuck->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusLuck = std::make_shared<Texture>();
    spriteMinusLuck->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());

    this->spriteAddStrength = std::make_shared<Texture>();
    spriteAddStrength->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusStrength = std::make_shared<Texture>();
    spriteMinusStrength->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());

    this->spriteAddVit = std::make_shared<Texture>();
    spriteAddVit->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusVit = std::make_shared<Texture>();
    spriteMinusVit->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());


    menuPos = MENU_POS::ATTRIBUTES;

    SDL_Window* vm = Engine::GetInstance()->GetWindow();

    unsigned int charSize = GUI::calcCharSize(80);

    this->buttons["BACK"] = std::make_unique<GUI::Button>(4.f, 4.f, 18.8f, 8.3f, charSize);
    this->buttons["BACK"]->setRenderText("Back");
    buttons["BACK"]->setBackgroundTexture("Assets/Background/button2.png");

    this->buttons["DONE"] = std::make_unique<GUI::Button>(44.f, 4.f, 18.8f, 8.3f, charSize);
    this->buttons["DONE"]->setRenderText("Done");
    buttons["DONE"]->setBackgroundTexture("Assets/Background/button2.png");

    this->buttons["SKILLS"] = std::make_unique<GUI::Button>(24.f, 4.f, 18.8f, 8.3f, charSize);
    this->buttons["SKILLS"]->setRenderText("Skills");
    buttons["SKILLS"]->setBackgroundTexture("Assets/Background/button2.png");

    mSpritesPlus["AGILITY_PLUS"] = spriteAddAgility;
    mSpritesMinus["AGILITY_MINUS"] = spriteMinusAgility;
    mSpritesPlus["CHA_PLUS"] = spriteAddCha;
    mSpritesMinus["CHA_MINUS"] = spriteMinusCha;
    mSpritesPlus["DEX_PLUS"] = spriteAddDex;
    mSpritesMinus["DEX_MINUS"] = spriteMinusDex;
    mSpritesPlus["INT_PLUS"] = spriteAddInt;
    mSpritesMinus["INT_MINUS"] = spriteMinusInt;
    mSpritesPlus["LUCK_PLUS"] = spriteAddLuck;
    mSpritesMinus["LUCK_MINUS"] = spriteMinusLuck;
    mSpritesPlus["STR_PLUS"] = spriteAddStrength;
    mSpritesMinus["STR_MINUS"] = spriteMinusStrength;
    mSpritesPlus["VIT_PLUS"] = spriteAddVit;
    mSpritesMinus["VIT_MINUS"] = spriteMinusVit;


    mSpritesPlus["AGILITY_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(31.f));
    mSpritesMinus["AGILITY_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(31.f));

    mSpritesPlus["CHA_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(40.f));
    mSpritesMinus["CHA_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(40.f));

    mSpritesPlus["DEX_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(50.f));
    mSpritesMinus["DEX_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(50.f));

    mSpritesPlus["INT_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(59.f));
    mSpritesMinus["INT_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(59.f));

    mSpritesPlus["LUCK_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(69.f));
    mSpritesMinus["LUCK_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(69.f));

    mSpritesPlus["STR_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(78.f));
    mSpritesMinus["STR_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(78.f));

    mSpritesPlus["VIT_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(87.f));
    mSpritesMinus["VIT_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(87.f));

//    for(auto button : buttons){
//
//        button.second->setBackgroundTexture("Assets/Background/button.png");
//    }
}

void IncreaseAttributes::initText(){

    unsigned charSize = GUI::calcCharSize(80);

    this->charCreatorText = std::make_unique<GUI::Text>(18, 22, 0, 0, false);

    //charCreatorText->setPositionF(18, 22);

    strengthText->setString("STRENGTH : " + to_string(getActiveCharacter()->getAttribute(STRENGTH)) + "  (+" + to_string(getActiveCharacter()->getBonus(STRENGTH)) + ")" );

    std::string msg = strengthText->getString();
    dexText->setString("DEXTERITY : " + to_string(getActiveCharacter()->getAttribute(DEXTERITY))+ "  (+" + to_string(getActiveCharacter()->getBonus(DEXTERITY)) + ")" );
    agiText->setString("AGILITY : " + to_string(getActiveCharacter()->getAttribute(AGILITY)) + "  (+" + to_string(getActiveCharacter()->getBonus(AGILITY)) + ")" );
    intText->setString("INTELLIGENCE : " + to_string(getActiveCharacter()->getAttribute(INTELLIGENCE)) + "  (+" + to_string(getActiveCharacter()->getBonus(INTELLIGENCE)) + ")" );
    charText->setString("CHARISMA : " + to_string(getActiveCharacter()->getAttribute(CHARISMA)) + "  (+" + to_string(getActiveCharacter()->getBonus(CHARISMA)) + ")" );
    luckText->setString("LUCK : " + to_string(getActiveCharacter()->getAttribute(LUCK)) + "  (+" + to_string(getActiveCharacter()->getBonus(LUCK)) + ")" );
    vitText->setString("VITALITY : " + to_string(getActiveCharacter()->getAttribute(VITALITY)) + "  (+" + to_string(getActiveCharacter()->getBonus(VITALITY)) + ")" );

    strengthText->setPositionF(18, 78);
    agiText->setPositionF(18, 31);
    charText->setPositionF(18, 40);
    dexText->setPositionF(18, 50);
    intText->setPositionF(18, 59);
    vitText->setPositionF(18, 87);
    luckText->setPositionF(18, 69);
}

IncreaseAttributes::IncreaseAttributes() : State(){


    strengthText = std::make_shared<GUI::Text>();
    dexText = std::make_shared<GUI::Text>();
    agiText = std::make_shared<GUI::Text>();
    intText = std::make_shared<GUI::Text>();
    charText = std::make_shared<GUI::Text>();
    luckText = std::make_shared<GUI::Text>();
    vitText = std::make_shared<GUI::Text>();

    attributeInfo = std::make_shared<GUI::Tooltip>();


    agiIncreased = false;
    chaIncreased = false;
    dexIncreased = false;
    intelIncreased = false;
    luckIncreased = false;
    strengthIncreased = false;
    vitIncreased = false;


    agiCounter = 0;
    chaCounter = 0;
    dexCounter = 0;
    intelCounter = 0;
    luckCounter = 0;
    strengthCounter = 0;
    vitCounter = 0;

    lastMenuPos = MENU_POS::ATTRIBUTES;

    maxPoints = getActiveCharacter()->getAttributePoints();
    pointsToSpend = maxPoints;

    const char* fontFile = "Assets/Fonts/SF Atarian System.ttf";

    this->font = TTF_OpenFont(fontFile, 26);


 //   initFonts();
    this->initGUI();
    this->initText();

    pointsMessage->setString("POINTS AVAILABLE:  " + std::to_string(pointsToSpend));

    menuPos = lastMenuPos;

///    SDL_SetTextInputRect(&textBox);

///    StateData::GetInstance()->currentMap->LoadFromFile("Data/Map1.txt");
}

IncreaseAttributes::~IncreaseAttributes(){

   /// State::~State();
   getEnemyText()->setPosition(GUI::p2pX(55), GUI::p2pY(40));
    getDynamicText()->setPositionF(GUI::p2pX(55), GUI::p2pY(30));
    getDynamicText()->clearText();
    getEnemyText()->clearText();
   mainScreen = true;
}

void IncreaseAttributes::updateButtons(const float &dt){

    for(auto &it : this->buttons){

        it.second->update();
    }
}

void IncreaseAttributes::updateInput(const float& dt){


        //DECREASE
        if(pointsToSpend > getActiveCharacter()->getAttributePoints()){

            pointsToSpend = getActiveCharacter()->getAttributePoints();
        }
        if(pointsToSpend <= 0){

            pointsToSpend = 0;
//            textInput = true;
        }
}

void IncreaseAttributes::updateText(const float& dt){

    if(this->menuPos == MENU_POS::ATTRIBUTES){

        std::string msg = " ";
//        msg = getAttributeSheet();

        charCreatorText->setString(msg, true, 250);

        pointsMessage->setString("Points available: " + std::to_string(pointsToSpend));
    }
}

void IncreaseAttributes::update(const float& dt){


    if(pointsToSpend > 0 || maxPoints == 0){

        buttons["DONE"]->setActive(false);
    }
    else{

        buttons["DONE"]->setActive(true);
    }

    updateButtons(dt);
    updateInput(dt);
    updateText(dt);
}

void IncreaseAttributes::updateEvents(SDL_Event& e){

//    if(textInput){
//
//       /// if(e.key.keysym.sym == SDLK_BACKSPACE && e.key.repeat != 0 && name.length() > 0){
//
//        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_BACKSPACE) && name.length() > 0){
//
//            name.pop_back();
//            ///SDL_Delay(60);
//
//            return;
//        }
//       /// }
//        if(e.key.keysym.sym == SDLK_RETURN){
//
//
//        }
//
//        if(e.type == SDL_TEXTINPUT){
//
//            this->updateTextInput(e);
//        }
//    }




    ///MOUSE EVENTS
    if(e.type == SDL_MOUSEMOTION){

            if(menuPos == MENU_POS::ATTRIBUTES){

         if(attributeInfo->checkBounds(agiText)){

                 std::string msg = "Agility increases your chance to dodge attacks and your stealth skill.";
                attributeInfo->setDisplayText(msg);
                attributeInfo->update();
                attributeInfo->setHidden(false);
            }
            else if(attributeInfo->checkBounds(dexText)){

                std::string msg = "Dexterity increases your chance to steal and your chance to land an attack.";
                attributeInfo->setDisplayText(msg);
                attributeInfo->update();
                attributeInfo->setHidden(false);
            }
            else if(attributeInfo->checkBounds(charText)){

                std::string msg = "Charisma increases your chance to charm others and improves your barter skill.";
                attributeInfo->setDisplayText(msg);
                attributeInfo->update();
                attributeInfo->setHidden(false);
            }
            else if(attributeInfo->checkBounds(intText)){

                std::string msg = "Intelligence increases your magic and perception skills.";
                attributeInfo->setDisplayText(msg);
                attributeInfo->update();
                attributeInfo->setHidden(false);
            }
            else if(attributeInfo->checkBounds(strengthText)){

                std::string msg = "Strength increases your attack power and your critical hit chance.";
                attributeInfo->setDisplayText(msg);
                attributeInfo->update();
                attributeInfo->setHidden(false);
            }
            else if(attributeInfo->checkBounds(vitText)){

                std::string msg = "Vitality increases your defensive power.";
                attributeInfo->setDisplayText(msg);
                attributeInfo->update();
                attributeInfo->setHidden(false);
            }
            else if(attributeInfo->checkBounds(luckText)){

                std::string msg = "Luck has a little bit of an effect on everything.";
                attributeInfo->setDisplayText(msg);
                attributeInfo->update();
                attributeInfo->setHidden(false);
            }

            else{

                attributeInfo->setHidden(true);
            }
            }
    }





    if(e.type == SDL_MOUSEBUTTONDOWN){

        if(buttons["BACK"]->isPressed(e.button)){

            Engine::GetInstance()->PopState();

            return;
        }

        if(buttons["SKILLS"]->isPressed(e.button) && menuPos == MENU_POS::ATTRIBUTES){

            std::string msg = StateData::GetInstance()->getActiveCharacter()->displaySkills();
            getDynamicText()->setPositionF(18, 31);
            getDynamicText()->setString(msg, true);
            menuPos = MENU_POS::SKILLS;
            buttons["SKILLS"]->setRenderText("Attributes");

            return;
        }
        if(buttons["SKILLS"]->isPressed(e.button) && menuPos == MENU_POS::SKILLS){

            menuPos = MENU_POS::ATTRIBUTES;
            buttons["SKILLS"]->setRenderText("Skills");

            return;
        }

        if(buttons["DONE"]->isPressed(e.button)){

            getActiveCharacter()->setAttributePoints(0);
            getActiveCharacter()->updateStats(true);
            getActiveCharacter()->calculateSkills();
            saveCharacters();
            Engine::GetInstance()->PopState();

            return;
        }

        if(menuPos == MENU_POS::ATTRIBUTES && pointsToSpend > 0){          ///TODO Took this out

            int x, y;

            SDL_GetMouseState(&x, &y);

            if(e.button.button == SDL_BUTTON_LEFT){

                if(mSpritesPlus["AGILITY_PLUS"]->intersects(x, y)){

                    //Increase Skill
                        getActiveCharacter()->increaseAttribute(AGILITY);
                        pointsToSpend--;
                        std::string m = "AGILITY : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::AGILITY));
                        agiText->setString(m);
                        agiIncreased = true;
                        agiCounter++;
                }

                if(mSpritesPlus["CHA_PLUS"]->intersects(x, y)){

                    //Increase Skill


                        getActiveCharacter()->increaseAttribute(CHARISMA);
                        pointsToSpend--;
                        std::string m = "CHARISMA : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::CHARISMA));
                        charText->setString(m);
                        chaIncreased = true;
                        chaCounter++;
                }

                if(mSpritesPlus["DEX_PLUS"]->intersects(x, y)){

                        getActiveCharacter()->increaseAttribute(DEXTERITY);
                        pointsToSpend--;
                        std::string m = "DEXTERITY : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::DEXTERITY));
                        dexText->setString(m);
                        dexIncreased = true;
                        dexCounter++;
                }

                if(mSpritesPlus["INT_PLUS"]->intersects(x, y)){

                        getActiveCharacter()->increaseAttribute(INTELLIGENCE);
                        pointsToSpend--;
                        std::string m = "INTELLIGENCE : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::INTELLIGENCE));
                        intText->setString(m);
                        intelIncreased = true;
                        intelCounter++;
                }

                if(mSpritesPlus["LUCK_PLUS"]->intersects(x, y)){

                        getActiveCharacter()->increaseAttribute(LUCK);
                        pointsToSpend--;
                        std::string m = "LUCK : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::LUCK));
                        luckText->setString(m);
                        luckIncreased = true;
                        luckCounter++;
                }

                if(mSpritesPlus["STR_PLUS"]->intersects(x, y)){

                        getActiveCharacter()->increaseAttribute(STRENGTH);
                        pointsToSpend--;
                        std::string m = "STRENGTH : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::STRENGTH));
                        strengthText->setString(m);
                        strengthIncreased = true;
                        strengthCounter++;
                }

                if(mSpritesPlus["VIT_PLUS"]->intersects(x, y)){

                        getActiveCharacter()->increaseAttribute(VITALITY);
                        pointsToSpend--;
                        std::string m = "VITALITY : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::VITALITY));
                        vitText->setString(m);
                        vitIncreased = true;
                        vitCounter++;
                }
            }
        }

        //DECREASE
        if(pointsToSpend < maxPoints){

            int x, y;

            SDL_GetMouseState(&x, &y);

            if(e.button.button == SDL_BUTTON_LEFT){

                if(mSpritesMinus["AGILITY_MINUS"]->intersects(x, y)){

                    //Increase Skill
                    if(getActiveCharacter()->getAttribute(AGILITY) > 0 && agiIncreased){

                        getActiveCharacter()->decreaseAttribute(AGILITY);
                        pointsToSpend++;
                        std::string m = "AGILITY : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::AGILITY));
                        agiText->setString(m);
                        agiCounter--;
                        if(agiCounter <= 0){

                            agiIncreased = false;
                        }
                    }
                }

                if(mSpritesMinus["CHA_MINUS"]->intersects(x, y)){

                    //Increase Skill
                    if(getActiveCharacter()->getAttribute(CHARISMA) > 0 && chaIncreased){

                        getActiveCharacter()->decreaseAttribute(CHARISMA);
                        pointsToSpend++;
                        std::string m = "CHARISMA : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::CHARISMA));
                        charText->setString(m);
                        chaCounter--;
                        if(chaCounter <= 0){

                            chaIncreased = false;
                        }
                    }
                }

                if(mSpritesMinus["DEX_MINUS"]->intersects(x, y)){

                    if(getActiveCharacter()->getAttribute(DEXTERITY) > 0 && dexIncreased){

                        getActiveCharacter()->decreaseAttribute(DEXTERITY);
                        pointsToSpend++;
                        std::string m = "DEXTERITY : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::DEXTERITY));
                        dexText->setString(m);
                        dexCounter--;
                        if(dexCounter <= 0){

                            dexIncreased = false;
                        }
                    }
                }

                if(mSpritesMinus["INT_MINUS"]->intersects(x, y)){

                    if(getActiveCharacter()->getAttribute(INTELLIGENCE) > 0 && intelIncreased){

                        getActiveCharacter()->decreaseAttribute(INTELLIGENCE);
                        pointsToSpend++;
                        std::string m = "INTELLIGENCE : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::INTELLIGENCE));
                        intText->setString(m);
                        intelCounter--;
                        if(intelCounter <= 0){

                            intelIncreased = false;
                        }
                    }
                }

                if(mSpritesMinus["LUCK_MINUS"]->intersects(x, y)){

                    if(getActiveCharacter()->getAttribute(LUCK) > 0 && luckIncreased){

                        getActiveCharacter()->decreaseAttribute(LUCK);
                        pointsToSpend++;
                        std::string m = "LUCK : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::LUCK));
                        luckText->setString(m);
                        luckCounter--;
                        if(luckCounter <= 0){

                            luckIncreased = false;
                        }
                    }
                }

                if(mSpritesMinus["STR_MINUS"]->intersects(x, y)){

                    if(getActiveCharacter()->getAttribute(STRENGTH) > 0 && strengthIncreased){

                        getActiveCharacter()->decreaseAttribute(STRENGTH);
                        pointsToSpend++;
                        std::string m = "STRENGTH : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::STRENGTH));
                        strengthText->setString(m);
                        strengthCounter--;
                        if(strengthCounter <= 0){

                            strengthIncreased = false;
                        }
                    }
                }

                if(mSpritesMinus["VIT_MINUS"]->intersects(x, y)){

                    if(getActiveCharacter()->getAttribute(VITALITY) > 0 && vitIncreased){

                        getActiveCharacter()->decreaseAttribute(VITALITY);
                        pointsToSpend++;
                        std::string m = "VITALITY : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::VITALITY));
                        vitText->setString(m);
                        vitCounter--;
                        if(vitCounter <= 0 ){

                            vitIncreased = false;
                        }
                    }
                } //END MINUS???
            }
        }
    }

    State::updateEvents(e);
}

void IncreaseAttributes::updateMouseEvents(SDL_MouseButtonEvent& e){


}

void IncreaseAttributes::updateTextInput(SDL_Event& e){

//    if(textInput && !textEditDone){
//
//       /// name += e.text.text;
//        name.push_back(*e.text.text);
//        std::cout << name << std::endl;
//        SDL_Delay(10);
//    }
}

void IncreaseAttributes::updateGUI(){

    initGUI();
}

void IncreaseAttributes::render(){


SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
 SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    for(auto &it : buttons){

        if(it.second->isActive()){

            it.second->renderButtons();
        }
    }

    if(menuPos == MENU_POS::ATTRIBUTES){


        if(pointsToSpend > 0){

            pointsMessage->render();
            for(auto &it : mSpritesPlus){

            it.second->render(Engine::GetInstance()->GetRenderer(), it.second->getTextureRect().x, it.second->getTextureRect().y);
        }
        }
        std::string name = charCreatorText->getString();
        strengthText->render();
        agiText->render();
        dexText->render();
        intText->render();
        charText->render();
        vitText->render();
        luckText->render();

        if(agiIncreased){

            mSpritesMinus["AGILITY_MINUS"]->render(Engine::GetInstance()->GetRenderer(), mSpritesMinus["AGILITY_MINUS"]->getTextureRect().x, mSpritesMinus["AGILITY_MINUS"]->getTextureRect().y);
        }
        if(dexIncreased){

            mSpritesMinus["DEX_MINUS"]->render(Engine::GetInstance()->GetRenderer(), mSpritesMinus["DEX_MINUS"]->getTextureRect().x, mSpritesMinus["DEX_MINUS"]->getTextureRect().y);
        }
        if(intelIncreased){

            mSpritesMinus["INT_MINUS"]->render(Engine::GetInstance()->GetRenderer(), mSpritesMinus["INT_MINUS"]->getTextureRect().x, mSpritesMinus["INT_MINUS"]->getTextureRect().y);
        }
        if(strengthIncreased){

            mSpritesMinus["STR_MINUS"]->render(Engine::GetInstance()->GetRenderer(), mSpritesMinus["STR_MINUS"]->getTextureRect().x, mSpritesMinus["STR_MINUS"]->getTextureRect().y);
        }
        if(luckIncreased){

            mSpritesMinus["LUCK_MINUS"]->render(Engine::GetInstance()->GetRenderer(), mSpritesMinus["LUCK_MINUS"]->getTextureRect().x, mSpritesMinus["LUCK_MINUS"]->getTextureRect().y);
        }
        if(chaIncreased){

            mSpritesMinus["CHA_MINUS"]->render(Engine::GetInstance()->GetRenderer(), mSpritesMinus["CHA_MINUS"]->getTextureRect().x, mSpritesMinus["CHA_MINUS"]->getTextureRect().y);
        }
        if(vitIncreased){

            mSpritesMinus["VIT_MINUS"]->render(Engine::GetInstance()->GetRenderer(), mSpritesMinus["VIT_MINUS"]->getTextureRect().x, mSpritesMinus["VIT_MINUS"]->getTextureRect().y);
        }
    }

    if(menuPos == MENU_POS::SKILLS){

        getDynamicText()->render();
    }

     if(!attributeInfo->getHidden()){

        attributeInfo->render();
    }
}
