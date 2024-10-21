#include "DialogueComponent.h"


///Completely useless for now I believe? Doesn't get called at all as far as I am aware??

DialogueComponent::DialogueComponent(std::shared_ptr<Entity> owner) : Component(owner){

    this->text = std::make_unique<GUI::textBox>();

    text->setSize(400, 400);
    text->setActive(true);
    text->setHeader("I AM TEXTBOX!");
    text->setText("Here is a standard textbox\n\nWhat do you want me to  say?");
    text->setPosition(20, 20);
}


DialogueComponent::~DialogueComponent(){

//    text.release();
}

void DialogueComponent::render(){

    if(text->getActive()){
        text->render();
    }
}

void DialogueComponent::setDialogueText(std::string txt){

    text->setText(txt);
}

