#include "Church.h"

Church::Church() : State(){

    satan = std::make_shared<NPC>(1, 100, 1);
    satan->setName("Satan");

    backButton->setActive(false);

    unsigned int charSize = GUI::calcCharSize(125);
    mButtons["BACK"] = std::make_shared<GUI::Button>(5.f, 93.f, 11.8f, 6.1f, charSize);
    mButtons["BACK"]->setRenderText("Back");

    for (auto button : mButtons) {

		button.second->setBackgroundTexture("Assets/Background/button2.png");
	}

    randomNPC = std::make_shared<NPC>(0, getActiveCharacter()->getLevel(), getRandomValue(2, 8));
}

Church::~Church(){

    backButton->setActive(true);
}




void Church::update(const float& dt){

    std::string msg = "";
    if(!getData()->isDay){

        msg = satan->getName() + " sits at the front of the church looking bored.";
    }
    else{

        msg = "No one is around, maybe you should try at night??";
    }
    getMainText()->setString(msg, true);

    mButtons["BACK"]->update();
    calcWorldTime();
}

void Church::updateEvents(SDL_Event& e){

    if(mButtons["BACK"]->isPressed(e.button)){

        Engine::GetInstance()->PopState();
    }

    State::updateEvents(e);
}



void Church::render(){

    getMainText()->render();

    for(auto button : mButtons){

        button.second->renderButtons();
    }

    worldTimerText->render();
}
