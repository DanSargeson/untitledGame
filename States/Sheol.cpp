#include "Sheol.h"

Sheol::Sheol() : State(){

    Yam = std::make_shared<NPC>(1, 100, 1);
    Yam->setName("Yam");

    backButton->setActive(false);

    unsigned int charSize = GUI::calcCharSize(125);
    mButtons["BACK"] = std::make_shared<GUI::Button>(5.f, 93.f, 11.8f, 6.1f, charSize);
    mButtons["BACK"]->setRenderText("Back");

    for (auto button : mButtons) {

		button.second->setBackgroundTexture("Assets/Background/button2.png");
	}

    randomNPC = std::make_shared<NPC>(0, getActiveCharacter()->getLevel(), getRandomValue(2, 8));
}

Sheol::~Sheol(){

    backButton->setActive(true);
}




void Sheol::update(const float& dt){

    std::string msg = Yam->getName() + " stands in front of the crashing waves.";
    getMainText()->setString(msg, true);

    mButtons["BACK"]->update();
    getActiveCharacter()->getWorldTimer()->update(dt);
    calcWorldTime();
}

void Sheol::updateEvents(SDL_Event& e){

    if(mButtons["BACK"]->isPressed(e.button)){

        Engine::GetInstance()->PopState();
    }

    State::updateEvents(e);
}



void Sheol::render(){

    getMainText()->render();

    for(auto button : mButtons){

        button.second->renderButtons();
    }

    worldTimerText->render();
}
