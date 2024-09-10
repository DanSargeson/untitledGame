#include "LoadGame.h"
#include "Engine.h"
#include "Game.h"

LoadGame::LoadGame() : State(){

    ///StateData::GetInstance()->clearCharacters();
    ///loadCharacters();

    setSkipIntro(true);
    ///State::loadCharacters();
    std::vector<std::string> ops;

//    menu.reset();
	menu = make_unique<GUI::Menu>();

	getData()->activeCharacter = 0;

	backButton->setActive(true);


	for (unsigned int i = 0; i < StateData::GetInstance()->characters.size(); i++) {

		ops.push_back(StateData::GetInstance()->characters[i]->getName());
	}

	//this->activeMenu->setDynamicMenu(ops, 0);
	menu->setMenuOptions(ops, true);
}

LoadGame::~LoadGame(){

 //   menu.reset();
//    State::~State();
}

void LoadGame::update(const float& dt){

    menu->update();
    backButton->update();
}

void LoadGame::updateEvents(SDL_Event& e){

    if(backButton->isActive() && backButton->isPressed(e.button)){

        Engine::GetInstance()->PopState();

        return;
    }

    menu->updateEvents(e);
//    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN) && e.key.repeat == 0){
//
//        menu->scrollText(0);
//    }
//
//      if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP) && e.key.repeat == 0){
//
//        menu->scrollText(1);
//    }

    if(e.type == SDL_MOUSEBUTTONDOWN){

        if(e.button.button == SDL_BUTTON_LEFT){

            if (this->menu->isSelected() /*&& !menu->cursorDetached()*/) {

				for (unsigned int i = 0; i < StateData::GetInstance()->characters.size(); i++) {

                        int c = menu->getChoice();
						StateData::GetInstance()->activeCharacter = c;
                        Engine::GetInstance()->PopState();
						Engine::GetInstance()->AddState(std::make_shared<Game>());

						return;

				}
            }
        }
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN) && e.key.repeat == 0){

            if (this->menu->isSelected()) {

				for (unsigned int i = 0; i < StateData::GetInstance()->characters.size(); i++) {

                        int c = menu->getChoice();
						StateData::GetInstance()->activeCharacter = c;
                        Engine::GetInstance()->PopState();
						Engine::GetInstance()->AddState(std::make_shared<Game>());

						return;

				}
            }
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){

        Engine::GetInstance()->PopState();

        return;
    }

    State::updateEvents(e);
}

void LoadGame::refreshGUI(){

    State::refreshGUI();

//    menu.reset();
	menu = make_unique<GUI::Menu>();

    std::vector<std::string> ops;

	for (unsigned int i = 0; i < StateData::GetInstance()->characters.size(); i++) {

		ops.push_back(StateData::GetInstance()->characters[i]->getName());
	}

	//this->activeMenu->setDynamicMenu(ops, 0);
	menu->setMenuOptions(ops, true);

}

void LoadGame::render(){

    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    menu->render();


    backButton->renderButtons();
}

/*
void LoadGame::loadCharacters(){

    std::string fileName = "characters.txt";
    ifstream inFile(fileName);
    StateData::GetInstance()->characters.clear();


    string name = "";
    int disTravel = 0;
    int gold = 0;
    int level = 0;
    int exp = 0;
    int str = 0;
    int vit = 0;
    int dex = 0;
    int intel = 0;
    int hp = 0;
    int stamina = 0;
    int statPoints = 0;
    int skillPoints = 0;
    int corrupt = 0;

	//ITEMS
	Inventory tempItems;

	int itemType = -1;
	int defence = 0;
	int type = 0;
	int damageMin = 0;
	int damageMax = 0;
	string itemName = "";
	int itemLevel = 0;
	int buyValue = 0;
	int sellValue = 0;
	int rarity = 0;

	//Factions
	int black = 0;
    int white = 0;
    int red = 0;
    int blue = 0;
    int green = 0;
    int brown = 0;
    int aqua = 0;
    int purple = 0;

    string line = "";
    stringstream strs;


    if(inFile.is_open()){
		while (getline(inFile, line)) {
			strs.str(line);
			strs >> name;
			strs >> disTravel;
			strs >> level;
			strs >> hp;
			strs >> exp;
			strs >> gold;
			//strs >> vit;
			//strs >> dex;
			//strs >> intel;
			//strs >> hp;
			//strs >> stamina;
			//strs >> statPoints;
			//strs >> skillPoints;
			strs >> corrupt;

			auto temp = std::make_shared<Player> (name, disTravel, gold, level, exp,
				str, vit, dex, intel, hp,
				stamina, statPoints, skillPoints, corrupt, false);

			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);

			while (

				strs >> black
				>> white
				>> red
				>> blue
				>> green
				>> brown
				>> aqua
				>> purple
				)

				///HERE FAC
				temp->loadFactions(black, white, red, blue, green, brown, aqua, purple);

            strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);

			while (strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> damageMin
				>> damageMax
				>> type) {

				if (itemType == itemTypes::WEAPON) {
					Weapon activeWeapon(type, damageMin, damageMax, itemName, itemLevel, 0, 0, rarity);
					auto awv = make_shared<Weapon>(activeWeapon);
					temp->setWeapon(awv);
				}
			}


			//ACTIVE ITEMS
			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);
			while (strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> defence
				>> type) {
				if (itemType == itemTypes::ARMOUR) {
					Armour activeArm(type, defence, itemName, itemLevel, 0, 0, rarity);
					auto avv = make_shared<Armour>(activeArm);
					int type = avv->getType();

					switch (type) {
					case HEAD:
						temp->setArmourHead(avv);
						break;

					case CHEST:
						temp->setArmourChest(avv);
						break;

					case ARMS:
						temp->setArmourArms(avv);
						break;

					case LEGS:
						temp->setArmourLegs(avv);
						break;

					default:
						break;
					}
				}

			}

			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);
			while (

				strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> damageMin
				>> damageMax
				>> type
				) {

				Weapon tempWeapon(type, damageMin, damageMax, itemName, itemLevel, 0, 0, rarity);
				auto wv = make_shared<Weapon>(tempWeapon);
				tempItems.addItemVectorSmart(wv);
				temp->addItem(wv);
			}


			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);
			while (
				strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> defence
				>> type
				) {
				Armour tempArmour(type, defence, itemName, itemLevel, 0, 0, rarity);
				auto av = make_shared<Armour>(tempArmour);
				tempItems.addItemVectorSmart(av);
				temp->addItem(av);
			}


                StateData::GetInstance()->characters.push_back(temp);

				///cout << "Character: " << temp->getName() << " loaded" << "\n";
				temp->setInv(tempItems);
				//cout << "Loaded Inv: " << temp.getInvAsString() << "\n";
				//cout << "tempItems: " << tempItems.getInvAsString() << "\n";
				strs.clear();
               /* for(int i = 0; i < characters.size(); i++){
                    cout << this->characters[i].getStatsAsString() << endl;
					cout << "Loaded Character: " << this->characters[i].getName() << endl;
                }*/

//            }
//    }
//    else{
//
//        Engine::GetInstance()->PopState();
//
//        return;
//    }
//    inFile.close();
//
//    if(StateData::GetInstance()->characters.size() <= 0){
//        throw "ERROR LOADING FILE!";
//    }
//}

