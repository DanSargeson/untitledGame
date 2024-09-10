#include "PlayerDeath.h"
#include "Timer.h"
#include "Engine.h"

PlayerDeath::PlayerDeath() : State(){

    textTimer = std::make_unique<GameTimer>();
    alpha = 0;
    alpha2 = 0;


    deathMsg = std::make_shared<GUI::Text>(false);
    deathMsg2 = std::make_shared<GUI::Text>(false);
    deathMsg3 = std::make_shared<GUI::Text>(false);

    refreshGUI();

    //HERE SAVEGAME
    textTimer->start();
   // std::cout << deathMsg->getColour() << std::endl;
}

PlayerDeath::~PlayerDeath(){

//    State::~State();
    getEnemyText()->setString("");
    getDynamicText()->setString("");

    getEnemyText()->setPosition(GUI::p2pX(55), GUI::p2pY(40));
    getDynamicText()->setPosition(GUI::p2pX(55), GUI::p2pY(30));
}

void PlayerDeath::refreshGUI(){

    State::refreshGUI();
    int w;
    SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &w, NULL);

    SDL_RenderClear(Engine::GetInstance()->GetRenderer());

   // int w = getMainText()->getTextWidth();
    deathMsg->setFontSize(GUI::calcCharSize(40));
    deathMsg->setColour(255, 0, 0, 0);
    //deathMsg->setBorder(false);
    deathMsg->setString("Gift of Death received");
    int dmX = (w / 2) - (deathMsg->getTextWidth() / 2);
    deathMsg->setPosition(dmX, GUI::p2pY(40));
   // deathMsg->clearText();
    SDL_SetTextureAlphaMod(deathMsg->getTexture(), alpha);

    deathMsg2->setString("Continue...");
    int dynaX = (w / 2) - (deathMsg2->getTextWidth() / 2);
    deathMsg2->setPosition(dynaX, GUI::p2pY(80));
    deathMsg2->setColour(0, 255, 0, 0);

    StateData::GetInstance()->getActiveCharacter()->increaseCorruption();

    deathMsg3->setString("Corruption has increased");
    SDL_SetTextureAlphaMod(deathMsg3->getTexture(), alpha);
    int enemX = (w / 2) - (deathMsg3->getTextWidth() / 2);
    deathMsg3->setPosition(enemX, GUI::p2pY(55));
}

void PlayerDeath::update(const float& dt){

//    Timer::GetInstance()->Tick();
    if(textTimer->getTicks() <= 15000){
        alpha += 1;

        if(alpha > 255){
            alpha = 255;
            //textTimer->stop();
        }

        if(textTimer->getTicks() > 1500){

            alpha2 += 2;
        }


        if(alpha2 > 255){

            alpha2 = 255;
        }

        SDL_SetTextureAlphaMod(deathMsg->getTexture(), alpha);
        SDL_SetTextureAlphaMod(deathMsg3->getTexture(), alpha2);
    }
}

void PlayerDeath::updateEvents(SDL_Event& e){


    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        if(textTimer->getTicks() > 3000){

            StateData::GetInstance()->getActiveCharacter()->resetHP(); //resets maxHP
            saveCharacters();
            Engine::GetInstance()->PopState();
        }
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){

        if(textTimer->getTicks() > 3000){

            StateData::GetInstance()->getActiveCharacter()->resetHP(); //resets maxHP
            saveCharacters();
            Engine::GetInstance()->PopState();
        }
    }
}

void PlayerDeath::render(){

//    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 200, 127, 0, 25);
   /// SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    ///SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    if(textTimer->getTicks() > 50){
        deathMsg->render();

        if(textTimer->getTicks() > 1500){

            deathMsg3->render();
        }
    }

    if(textTimer->getTicks() > 4000){

            deathMsg2->render();
        }
//    std::cout << deathMsg->getColour() << std::endl;
}

