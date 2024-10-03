#include "Unk.h"

Unk::Unk() : State(){

    apep = std::make_shared<NPC>(1, 100, 1);
    apep->setName("Apep");

    backButton->setActive(false);

    unsigned int charSize = GUI::calcCharSize(125);
    mButtons["BACK"] = std::make_shared<GUI::Button>(5.f, 93.f, 11.8f, 6.1f, charSize);
    mButtons["BACK"]->setRenderText("Back");

    for (auto button : mButtons) {

		button.second->setBackgroundTexture("Assets/Background/button2.png");
	}

    randomNPC = std::make_shared<NPC>(0, getActiveCharacter()->getLevel(), getRandomValue(2, 8));
}

Unk::~Unk(){

    backButton->setActive(true);
}




void Unk::update(const float& dt){

    std::string msg = "";
    if(getData()->isDay){

     msg = apep->getName() + " looks at ease.";
    }
    else{

        msg = apep->getName() + " looks furious.";
    }
    getMainText()->setString(msg, true);

    mButtons["BACK"]->update();
    getActiveCharacter()->getWorldTimer()->update(dt);
    calcWorldTime();
}

void Unk::updateEvents(SDL_Event& e){

    if(mButtons["BACK"]->isPressed(e.button)){

        Engine::GetInstance()->PopState();
    }

    State::updateEvents(e);
}



void Unk::render(){

    getMainText()->render();

    for(auto button : mButtons){

        button.second->renderButtons();
    }

    worldTimerText->render();
}
