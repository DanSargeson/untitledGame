#pragma once
#include "Component.h"

class DialogueComponent : public Component{

    public:

        DialogueComponent(std::shared_ptr<Entity> owner);
        virtual ~DialogueComponent();

        bool getTextBoxActive(){ if(text != nullptr) { return text->getActive(); } else return false; }

        void setTextBoxActive(bool n) { text->setActive(n); }

        void setDialogueText(std::string txt);

        void setHeader(std::string n) { if(text != nullptr) { text->setHeader(n); } }

        void render();

    private:

        std::unique_ptr<GUI::textBox> text;
};
