#include "Emesh.h"

Emesh::Emesh() : State(){

    Yam = std::make_shared<NPC>(1, 100, 1);
    Yam->setName("Aranyani");

    backButton->setActive(false);

    unsigned int charSize = GUI::calcCharSize(125);
    mButtons["BACK"] = std::make_shared<GUI::Button>(5.f, 93.f, 11.8f, 6.1f, charSize);
    mButtons["BACK"]->setRenderText("Back");

    for (auto button : mButtons) {

		button.second->setBackgroundTexture("Assets/Background/button2.png");
	}

    randomNPC = std::make_shared<NPC>(0, getActiveCharacter()->getLevel(), getRandomValue(2, 8));
}

Emesh::~Emesh(){

    backButton->setActive(true);
}




void Emesh::update(const float& dt){

    std::string msg = "";

    if(getData()->isDay){

        msg = Yam->getName() + " peers out through the thicket of trees.";
    }
    else{

        msg = "The stillness of the forest is unsettling at night.";
    }
    getMainText()->setString(msg, true);

    mButtons["BACK"]->update();

    getActiveCharacter()->getWorldTimer()->update(dt);
    calcWorldTime();
}

void Emesh::updateEvents(SDL_Event& e){

    if(mButtons["BACK"]->isPressed(e.button)){

        Engine::GetInstance()->PopState();
    }

    State::updateEvents(e);
}



void Emesh::render(){

    getMainText()->render();

    for(auto button : mButtons){

        button.second->renderButtons();
    }

    worldTimerText->render();
}
