#include "FactionEncounter.h"
#include "LoadFiles.h"

int FactionEncounter::position = 1;

FactionEncounter::FactionEncounter(int faction){

    ///SHOULD DO SOMETHING LIKE.... LOAD ID == QUESTID, choices can be accept/refuse quest (or maybe a positive/negative choice for each quest?)
    ///This gets added to questComponent class (e.g player selected to follow negative for questID 0
    ///Would need to save all of quest component to a json file probably.

    firstEncounter = true;

    textBuildCounter = 0;

    textThreadRunning = true;

    getEnemyText()->setString("");

    getDynamicText()->setString("");

    m_fileName = "Assets/factionQuests.txt";

    ///"Assets/newDialogue.txt"

    json_file = "Assets/diag.json";

    npc = std::make_shared<NPC>(1, faction); // TODO:: NEED TO FIX THIS
    file = std::make_shared<LoadFiles>(m_fileName, 1);

    npc->createDialogueComponent();
    npc->createFactionComponent();
    file->readJsonFile2(json_file);
   // std::pair msg1 = file->getDialogueAndResponses(npc->getFactionStr(), 1, 0);

   textMsg = "You are approached by a brilliant white light.\n\n";
   std::string check = npc->getFactionStr();

    getMainText()->setString(file->getDialogue(check, 1), true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
    copyText = "\"" + getMainText()->getString() + "\"";
    menu = std::make_shared<GUI::Menu>();

    menu->setMenuOptions(file->getFirstResponses(check, 1), true);
}

void FactionEncounter::startTextThread(){

    textThreadRunning = true;
    textThread = std::thread(&FactionEncounter::updateText, this);
}

FactionEncounter::~FactionEncounter(){

    //getMainText()->setString("Select an option: ");
//    npc.reset();

    if(textThread.joinable()){

        textThread.join();
    }
    //State::~State();
}

void FactionEncounter::update(const float& dt){


    menu->update();
    if(textThreadRunning){

        updateText();
    }
    else{

        if(textThread.joinable()){

            textThread.join();
        }
    }

//    calcWorldTime();
}

void FactionEncounter::updateText(){

    if(builderText != copyText){

            menu->setActive(false);

    // loop through each character in the text
        // output one character
        // flush to make sure the output is not delayed
        builderText.push_back(copyText[textBuildCounter]);
        //mTextTexture->loadFromRenderedText(Engine::GetInstance()->GetRenderer(), copy_text, mTextColour, *mFont, true, 80);

        //mTextTexture->render(Engine::GetInstance()->GetRenderer(),  mOutline.x + offsetX, mOutline.y + offsetY);
        // sleep 60 milliseconds
        ///std::this_thread::sleep_for(std::chrono::milliseconds(600));

        std::string temp = textMsg;
        temp += builderText;
        getMainText()->setString(temp, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
        //getMainText()->render();
       // std::this_thread::sleep_for(std::chrono::milliseconds(60));
       //L_Deay(700);
        textBuildCounter++;
    }

    else{

        builderText = "";
        textBuildCounter = 0;
        textThreadRunning = false;
//        std::string msg2 = file->getDialogue(npc->getFactionStr(), file->getCurrDiagID());
//        copyText = "\"" + msg2 + "\"";
//        getMainText()->setString((textMsg + copyText), true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));

        menu->setActive(true);
    }
}

void FactionEncounter::runMenuSelection(){

 if(menu->isSelected()){

//            if(menu->getChoice() == 0){
//                Engine::GetInstance()->PopState();
//            }
           // else{

                firstEncounter = false;

                file->selectResponse(npc->getFactionStr(), 1, (menu->getChoice() + 1));
                std::string msg2 = file->getDialogue(npc->getFactionStr(), file->getCurrDiagID());
                if(file->getCurrDiagID() == 4){ ///4 is RED in json, 2 is FACTIONS::RED

                    getActiveCharacter()->gainRep(2, 10);
                }
                if(file->getCurrDiagID() == 5){ ///5 is BLUE in json,

                    getActiveCharacter()->gainRep(3, 10);
                }
                if(file->getCurrDiagID() == 6){ ///6 green in json

                    getActiveCharacter()->gainRep(4, 10);
                }
                std::string temp = textMsg;
                temp += msg2;
                getMainText()->setString(temp, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
                copyText = "\"" + msg2 + "\"";
                textThreadRunning = true;
                menu->setMenuOptions(file->getPlayerOps(), true);
 //           }
        }
}

void FactionEncounter::updateEvents(SDL_Event& e)
{

    menu->updateEvents(e);


    if(e.type == SDL_MOUSEBUTTONDOWN){


        if(textThreadRunning){

            textThreadRunning = false;
            menu->setActive(true);
            std::string msg2 = file->getDialogue(npc->getFactionStr(), file->getCurrDiagID());
            copyText = "\"" + msg2 + "\"";
            builderText = "";
            textBuildCounter = 0;
            getMainText()->setString((textMsg + msg2), true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
            return;
        }
        ///START run menu selection
        if(menu->isSelected()){

            runMenuSelection();
        }

        if(!textThreadRunning){

            if(file->getCurrDiagID() == 0){

                Engine::GetInstance()->PopState();
            }
        }

        return;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        if(textThreadRunning){

            textThreadRunning = false;
            menu->setActive(true);
            std::string msg2 = file->getDialogue(npc->getFactionStr(), file->getCurrDiagID());
            copyText = "\"" + msg2 + "\"";
            builderText = "";
            textBuildCounter = 0;
            getMainText()->setString((textMsg + msg2), true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
            return;
        }

        if(menu->isSelected()){

            runMenuSelection();

           /// return;
        }
        getEnemyText()->clearText();
        getDynamicText()->clearText();

        if(!textThreadRunning){

            if(file->getCurrDiagID() == 0){

                Engine::GetInstance()->PopState();
            }
        }

        return;
    }

    State::updateEvents(e);
}

void FactionEncounter::refreshGUI(){

    State::refreshGUI();

    if(firstEncounter){

    std::string check = npc->getFactionStr();
    getMainText()->setString(file->getDialogue(check, 1), true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
    copyText = "\"" + getMainText()->getString() + "\"";
    //textThreadRunning = true;
    menu->setMenuOptions(file->getFirstResponses(check, 1), true);
    }
    else{

        std::string msg2 = file->getDialogue(npc->getFactionStr(), file->getCurrDiagID());
        getMainText()->setString(msg2, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
        copyText = "\"" + msg2 + "\"";
      //  textThreadRunning = true;
        menu->setMenuOptions(file->getPlayerOps(), true);
    }
}

void FactionEncounter::render()
{

    if(textThreadRunning){

        std::string temp = textMsg;
        temp += builderText;
        getMainText()->setString(temp, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
        getMainText()->render();

        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        //return;
    }else{

        std::string temp = textMsg;
        temp += copyText;
        getMainText()->setString(temp, true, (getMainText()->getGlobalBounds().w - GUI::p2pXi(5)));
        getMainText()->render();
    }

    if(getEnemyText()->getString() != ""){

        getEnemyText()->render();
    }
    if(getDynamicText()->getString() != ""){

        getDynamicText()->render();
    }

    menu->render();
    worldTimerText->render();
}

