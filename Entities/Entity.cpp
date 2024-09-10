#include "stdafx.h"
#include "Entity.h"
#include "Component.h"
#include "FactionComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"
#include "AttackComponent.h"
#include "DialogueComponent.h"
#include "QuestComponent.h"

vector<string> Entity::entityNames;

void Entity::initNames() {
//	Entity::entityNames.push_back("Goblin");
//	Entity::entityNames.push_back("Warlock");
//	Entity::entityNames.push_back("Wolf");
//	Entity::entityNames.push_back("Ghost");
//	Entity::entityNames.push_back("Skeleton");
//	Entity::entityNames.push_back("Rat");
//	Entity::entityNames.push_back("Harpy");
//	Entity::entityNames.push_back("Gremlin");
//	Entity::entityNames.push_back("Berserker");

	Entity::entityNames.push_back("Doctor"); //VITALITY - Collects Health potions/Vitality boosters
	Entity::entityNames.push_back("Blacksmith"); //STRENGTH - Collects construction materials for weapons/armour
	Entity::entityNames.push_back("Locksmith"); //DEXTERITY - Collects keys to open hidden chests
	Entity::entityNames.push_back("Scout"); //Agility - Collects map fragments, used to force an encounter of the specified type/faction (maybe one type and one faction that can be combined,,)
	Entity::entityNames.push_back("Alchemist"); //INTELLIGENCE - Gathers potions and spells to enchant weapons/armour
    Entity::entityNames.push_back("Innkeeper"); //CHARISMA - Gathers alcohol, temporary boost to Charisma/gain favour with NPCs quickly
	Entity::entityNames.push_back("Explorer");  //LUCK - BAttles enemies and can earn passive experience points
}

int Entity::getBonus(int type){

    return attributeComponent->getBonus(type);
}



void Entity::InitVariables(){

	this->attributeComponent = NULL;
	this->skillComponent = NULL;
	this->dialogueComponent = NULL;
	this->factionComponent = NULL;
}

Entity::Entity(){

    initNames();
	this->InitVariables();
	this->m_name = Entity::entityNames[rand() % Entity::entityNames.size()];

	this->inv = std::make_shared<Inventory>();
}

Entity::~Entity(){

}


//Component Functions

int Entity::getLevel(){

    if(attributeComponent != nullptr){

        int a = attributeComponent->getLevel();
        return a;
    }
    else{

        return m_level;
    }
}

int Entity::getHP(){

    return attributeComponent->getHP();
}

int Entity::getHPMax(){

    return attributeComponent->getHPMax();
}

void Entity::loseHP(int hp){

	this->attributeComponent->loseHP(hp);
}

void Entity::gainHP(int hp){

	this->attributeComponent->gainHP(hp);

}

void Entity::loseXP(float xp){

	this->attributeComponent->loseEXP(xp);
}

void Entity::gainXP(float xp){

    if(xp == -1){

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, (this->getLevel() * 20));
        xp = dis(gen);
    }
	this->attributeComponent->gainEXP(xp);
}

void Entity::loseRep(int faction, int rep){

	this->factionComponent->loseRep(faction, rep);
}

bool Entity::fullHealth(){

    if(attributeComponent->getHP() >= attributeComponent->getHPMax()){

        return true;
    }

    return false;
}

void Entity::gainRep(int faction, int rep){


	this->factionComponent->gainRep(faction, rep);
}

int Entity::getSkill(int skill){

	if (this->skillComponent) {

		return this->skillComponent->getSkill(skill);
	}

	return -1;
}

void Entity::setExp(int exp){

    this->attributeComponent->setXP(exp);
}

void Entity::levelUp(){

    bool levelled;

    attributeComponent->updateLevel();

//    if(this->exp >= this->expNext){
//        this->exp -= this->expNext;
//        this->level++;
//        this->expNext = static_cast<int>((50/3)*((pow(level,3) - 6*pow(level,2)) + 17*level - 12)) + 100;
//
//        this->statPoints++;
//        this->skillPoints++;
//
//        //return true;
//
//        std::string msg =  "You are now level " + std::to_string(this->level) + "!";
//        getMainText()->setString(msg);
//
//        updateStats();
//        this->hp = this->hpMax;
//    }
//    else{
//        getMainText()->setString("You do not have enough experience.");
//        //return false;
//    }
}

int Entity::getFaction(int faction) {

	if (this->factionComponent) {

		return this->factionComponent->getReputation(faction);
	}

	return -1;
}

int Entity::getAttribute(int attribute) {

	if (this->attributeComponent) {

		return this->attributeComponent->getAttribute(attribute);
	}

	return -1;
}

int Entity::checkDurability() {

//	if (this->activeTool != NULL) {
//
//		return this->activeTool->getDurability();
//	}
//	else {

		return -1;
	//}
}

void Entity::loseDurability(){

	//TODO - NEED TO ADD A CHECK TO WHICH ITEM IS BEING USED!!
//	if (this->activeWeapon != NULL) {
//
//		this->activeWeapon->use();
//	}
//
//	if (this->activeTool != NULL) {
//
//		this->activeTool->use();
//	}
//
//	if (this->activeArms != NULL) {
//
//		this->activeArms->use();
//	}
//
//	if (this->activeHead != NULL) {
//
//		this->activeHead->use();
//	}
//
//	if (this->activeLegs != NULL) {
//
//		this->activeLegs->use();
//	}
//
//	if (this->activeChest != NULL) {
//
//		this->activeChest->use();
//	}
}

std::shared_ptr<Weapon> Entity::getActiveWeapon(){

    if(this->activeWeapon != nullptr){

        return activeWeapon;
    }
    else{

        return nullptr;
    }
}

std::shared_ptr<Armour> Entity::getActiveHead(){

    if(this->activeHead != nullptr){

        return activeHead;
    }
    else{

        return nullptr;
    }
}

std::shared_ptr<Armour> Entity::getActiveChest(){

    if(this->activeChest != nullptr){

        return activeChest;
    }
    else{

        return nullptr;
    }
}

std::shared_ptr<Armour> Entity::getActiveArms(){

    if(this->activeArms != nullptr){

        return activeArms;
    }
    else{

        return nullptr;
    }
}

std::shared_ptr<Armour> Entity::getActiveLegs(){

    if(this->activeLegs != nullptr){

        return activeLegs;
    }
    else{

        return nullptr;
    }
}

int Entity::getExp(){

    return attributeComponent->getEXP();
}

int Entity::getExpNext(){

    return attributeComponent->getEXPNext();
}

float Entity::getAttributeFloat(int attribute){

	if (this->attributeComponent) {

		return this->attributeComponent->getAttribute(attribute);
	}
	else{

        return -1.f;
	}

}


bool Entity::skillCheck(std::shared_ptr<Entity> checkAgainst, int skill1, int skill2){

    bool success = false;

    int tot1 = skill1;
    int tot2 = skill2;

    if(skillComponent && checkAgainst->getSkillComponent()){

            tot1 += attributeComponent->getAttribute(ATTRIBUTE::LUCK);
            ///tot2 += checkAgainst->getAttribute(ATTRIBUTE::LUCK);

            int skillDifference = tot1 - tot2;

            int level = this->getLevel();

            ///*EASY MODE*/
            ///double baseSuccessRate = 0.7;
            ///TODO ADD THIS BACK
            double baseSuccessRate = 0.2;
            double successRateModifier = static_cast<double>(level) / 10.0; //Increase in success rate per skill point difference

            //calc probability of success rate
            double probability = baseSuccessRate + (successRateModifier * skillDifference);


            //generate a random number between 0 and 1 to determine success
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0, 1);
            double randomValue = dis(gen);

            if(randomValue <= probability){

                success = true;
            }
    }

    return success;
}

void Entity::calculateSkills(){

    if(attributeComponent){

        if(skillComponent){

            skillComponent->calculateSkills(attributeComponent);
        }
    }
}

void Entity::updateStats(bool s){

    if(attributeComponent){

        attributeComponent->updateStats(s);
    }
}

std::string Entity::getFactionStr() {

	return this->factionComponent->getFactionsStr();
}

std::string Entity::getInvItemAsString(int choice){

    return this->inv->getInvItemAsString(choice);
}

std::string Entity::getArmAsString(int choice){

    return this->inv->getArmAsString(choice);
}


std::string Entity::getWepAsString(int choice){

    return this->inv->getWepAsString(choice);
}

int Entity::getRep(int faction){

    if(factionComponent != nullptr){

        return factionComponent->getReputation(faction);
    }
    else{

        return -1;
    }
}

std::shared_ptr<Inventory> Entity::getInv(){

    return inv;
}

std::vector<std::string> Entity::getInvAsVec(){

    return this->inv->getInvAsVecOps();
}

std::string Entity::getFactionStrSave(){

    return this->factionComponent->getFactionsStrSave();
}

std::string Entity::getSavedFactionName(){

    return factionComponent->getFactionName(this->faction);
}

std::string Entity::getFactionName(int faction){

	return factionComponent->getFactionName(faction);
}

//std::vector<std::string> Entity::getDialogueOptions(){
//
//	return this->dialogueComponent->getDialogueOptions();
//}

std::string Entity::getItemString(int index){

	std::shared_ptr<Item> item = this->inv->findItemSmart(index);

	return item->getName();
	//return item->getTypeStr();
}

bool Entity::isAlive(){

	return this->attributeComponent->getHP() > 0;
}



void Entity::createAttributeComponent(const unsigned level, const bool reset, bool enemy){

	this->attributeComponent =  std::make_shared<AttributeComponent>(getPtr(), level, reset, enemy);
}

void Entity::createSkillComponent(){

	this->skillComponent = std::make_shared<SkillComponent>(getPtr());

	skillComponent->calculateSkills(attributeComponent);
}

void Entity::createComponents() {

    this->createAttributeComponent(this->m_level, true, true);
    this->createSkillComponent();
    this->createFactionComponent();
    createAttackComponent();

    /*mComponents.push_back(attributeComponent);
    mComponents.push_back(skillComponent);
    mComponents.push_back(factionComponent);
    mComponents.push_back(attackComponent);*/

    for (auto c : mComponents) {

        c->addOwner();
    }
}

void Entity::setHP(int hp){

    attributeComponent->setHP(hp);
}

void Entity::assignRandomAttributes(int level, bool npc){

    attributeComponent->assignRandomAttributes(level, npc);
}

void Entity::createFactionComponent(){

	this->factionComponent = std::make_shared<FactionComponent>(getPtr());
}

void Entity::createQuestComponent(){

    this->questComponent = std::make_shared<QuestComponent>(getPtr());
}

void Entity::createDialogueComponent(){

	this->dialogueComponent = std::make_shared<DialogueComponent>(getPtr());
}

void Entity::createAttackComponent(){

	this->attackComponent =  std::make_shared<AttackComponent>(getPtr());
}

int Entity::getDamage(){

	if (this->attackComponent) {


		//Calculate base damage
		this->attackComponent->calculateElementBonus();


		if (this->activeWeapon != NULL) {

			this->attackComponent->calculateWeaponModifier(dynamic_cast<Weapon&>(*this->activeWeapon));
		}
        return this->attackComponent->getTotalDamage();
	}

	return 0;
}

void Entity::spawnGear(){

    //ITEM ROLL
						unsigned seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

                        std::default_random_engine generator;

                        generator.seed(seed);

                        std::uniform_int_distribution<int> itemDistribution(1, 100);
                        int r = itemDistribution(generator);


						//int r = rand() % 100 + 1;
						int rarity = -1;
						if (r <= 70) {
							//GET ITEM
							rarity = 0; //COMMON ITEM
							//int newRoll = rand() % 100 + 1;
                        }
                        else if (r > 70 && r <= 80) {
								rarity = 1; //UNCOMMON ITEM
                        }

                        else if(r > 80) {
                            rarity = 2; //RARE
                        }

                        else if(r > 85 && r < 95){
                            rarity = 3;
                        }
                        else if(r > 95){

                            rarity = 4;
                        }

                        seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
                        generator.seed(seed);
                        r = itemDistribution(generator);

                        int low = StateData::GetInstance()->getActiveCharacter()->getLevel() - 1;
                        if(low <= 0){

                            low = 1;
                        }
                        int high = StateData::GetInstance()->getActiveCharacter()->getLevel() + 2;
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> dis(low, high);
                        int lvl = dis(gen);

							if (r >= 50) {

								if (r <= 75) {
///									int lvl = StateData::GetInstance()->getActiveCharacter()->getLevel();
									auto tempWe = make_shared<Weapon>(lvl, rarity);

									if(this->activeWeapon != nullptr){

                                        if(tempWe->getDamageMin() > activeWeapon->getDamageMin()){

                                            this->addItem(tempWe);
                                            this->equipWeapon(inv->size());
                                        }
                                        else{

                                            return;
                                        }
									}
									this->addItem(tempWe);
									this->equipWeapon(inv->size());
								}
								else {
									auto tempAw = make_shared<Armour>(lvl, rarity);

                                    switch(tempAw->getType()){

                                    case armourType::ARMS:

                                        if(this->activeArms != nullptr){

                                            if(tempAw->getDefenceMin() > this->activeArms->getDefenceMin()){

                                                this->addItem(tempAw);
                                                this->equipArmour(inv->size());
                                            }
                                        }
                                        this->addItem(tempAw);
                                        this->equipArmour(inv->size());
                                        break;

                                    case armourType::HEAD:

                                        if(this->activeHead != nullptr){

                                            if(tempAw->getDefenceMin() > this->activeHead->getDefenceMin()){

                                                this->addItem(tempAw);
                                                this->equipArmour(inv->size());
                                            }
                                        }
                                        this->addItem(tempAw);
                                        this->equipArmour(inv->size());
                                        break;

                                    case armourType::CHEST:

                                        if(this->activeChest != nullptr){

                                            if(tempAw->getDefenceMin() > this->activeChest->getDefenceMin()){

                                                this->addItem(tempAw);
                                                this->equipArmour(inv->size());
                                            }
                                        }
                                        this->addItem(tempAw);
                                        this->equipArmour(inv->size());
                                        break;

                                    case armourType::LEGS:

                                        if(this->activeLegs != nullptr){

                                            if(tempAw->getDefenceMin() > this->activeLegs->getDefenceMin()){

                                                this->addItem(tempAw);
                                                this->equipArmour(inv->size());
                                            }
                                        }
                                        this->addItem(tempAw);
                                        this->equipArmour(inv->size());
                                        break;

                                    default:
                                        this->addItem(tempAw);
                                        this->equipArmour(inv->size());
                                        break;

                                    }   ///END SWITCH
								}
							}
							///TODO THINK THIS IS END OF ITEM ROLL?????
}

std::string Entity::getStatsAttributeScreen(){

    std::string deets;

	int hp, hpMax;

	//gold = 0;
	hp = static_cast<int>(this->attributeComponent->getHP());
	hpMax = static_cast<int>(this->attributeComponent->getHPMax());

	int xp = static_cast<int>(this->attributeComponent->getEXP());
	int xpNext = static_cast<int>(this->attributeComponent->getEXPNext());

//	if(gold < 0){
//
//        gold = 0;
//	}

	deets += "Name: " + m_name + "\n";
	deets += "Level: " + std::to_string(this->attributeComponent->getLevel()) + "\n";
	deets += "HP: " + std::to_string(hp) + " / " + std::to_string(hpMax) + "\n";
	deets += "Exp: " + std::to_string(xp) + " / " + std::to_string(xpNext) + "\n";
	//deets += "Gold: " + std::to_string(gold) + "\n";

	//deets += " = EQUIPPED ITEMS = \n";

//	deets += "Tool: ";
//
//	if (this->activeTool != NULL) {
//
//		deets += this->activeTool->getTypeStr() + "\n";
//	}
//	else {
//
//		deets += "Empty\n";
//	}
//
	deets += "Weapon: ";

	if (this->activeWeapon != NULL) {

		deets += this->activeWeapon->getName() + " " + this->activeWeapon->getTypeStr() + "  (" + std::to_string(activeWeapon->getDamageMin()) + " - " + std::to_string(activeWeapon->getDamageMax()) + ")\n";
	}
	else {

		deets += "Empty\n";
	}

	deets += "Head Gear: ";
	if (this->activeHead != NULL) {

		deets +=this->activeHead->getName() + " " +  this->activeHead->getTypeStr() + "  (" + std::to_string(activeHead->getDefenceMin()) + " - " + std::to_string(activeHead->getDefenceMax()) + ")\n";
	}
	else {

		deets += "Empty\n";
	}

	deets += "Arms Gear: ";
	if (this->activeArms != NULL) {

		deets += this->activeArms->getName() + " " +  this->activeArms->getTypeStr() + "  (" + std::to_string(activeArms->getDefenceMin()) + " - " + std::to_string(activeArms->getDefenceMax()) + ")\n";
	}
	else {

		deets += "Empty\n";
	}

	deets += "Chest Gear: ";
	if (this->activeChest != NULL) {

		deets += this->activeChest->getName() + " " + this->activeChest->getTypeStr() + "  (" + std::to_string(activeChest->getDefenceMin()) + " - " + std::to_string(activeChest->getDefenceMax()) + ")\n";
	}
	else {

		deets += "Empty\n";
	}

	deets += "Legs Gear: ";
	if (this->activeLegs != NULL) {

		deets += this->activeLegs->getName() + " " + this->activeLegs->getTypeStr() + "  (" + std::to_string(activeLegs->getDefenceMin()) + " - " + std::to_string(activeLegs->getDefenceMax()) + ")\n";
	}
	else {

		deets += "Empty\n";
	}

	int minDefence = this->attackComponent->getMinDefence();
	int maxDefence = this->attackComponent->getMaxDefence();
//	int armour = this->getArmourRating();


	int minAttack = this->attackComponent->getBaseMinDamage();
	int maxAttack = this->attackComponent->getBaseMaxDamage();


	deets += "\nArmour Rating: " + std::to_string(minDefence) + " - " + std::to_string(maxDefence);

	if(getMinDefenceWithArmour() > 0){

        deets += "  (+" + std::to_string(getMinDefenceWithArmour()) + " - " + std::to_string(getMaxDefenceWithArmour()) + ")";
	}

//	if (armour > 0) {
//
//	 deets += "  (+" + std::to_string(armour) + ")";
//	}

    if(minAttack <= 0){

        minAttack = 1;      ///BATTLE ENSURES THAT A SUCCESSFUL ATTACK WILL ALWAYS DO AT LEAST 1 DMG
    }
	deets += "\nAttack Rating: " +  std::to_string(minAttack) + " - " + std::to_string(maxAttack);

	if (this->getMinDamageWithWeapon() > 0) {

		deets += "  (+" + std::to_string(this->getMinDamageWithWeapon()) + " - " + std::to_string(this->getMaxDamageWithWeapon()) + ")";
	}

	return deets;

}

SDL_Color Entity::getItemColour(int choice){

    return this->inv->getInvItemColour(choice);
}

SDL_Color Entity::getWepItemColour(int choice){

    return inv->getWepItemColour(choice);
}

SDL_Color Entity::getArmItemColour(int choice){

    return inv->getArmItemColour(choice);
}

void Entity::equipWeapon(int index){

    shared_ptr<Item> item = this->inv->findWeaponSmart(index);
		//auto wv = std::dynamic_pointer_cast<Weapon>(item);
		Weapon* w = nullptr;
		//w = dynamic_cast<Weapon*>(&this->inventory[index]);
		//IS WEAPON
		if (item->getItemType() == WEAPON) {
            auto wv = std::dynamic_pointer_cast<Weapon>(item);
			if (wv != nullptr) {
				if (this->activeWeapon != NULL) {
					this->addItem(this->activeWeapon);
				}
				//this->addItem(wv);
				this->activeWeapon = wv;
				this->inv->removeItemVectorSmart(wv);
			}
		}
}

void Entity::equipArmour(int index){

     //a = dynamic_cast<Armour*>(&this->inventory[index]);
   shared_ptr<Item> item = this->inv->findArmourSmart(index);
            auto wv = std::dynamic_pointer_cast<Armour>(item);
			if (wv != nullptr) {
				wv->getItemType();
				int type = dynamic_cast<Armour&>(*wv).getType();
				switch (type) {
				case armourType::HEAD:
					//this->addItem(wv);
					if (this->activeHead != NULL) {
						this->addItem(this->activeHead);
					}
					this->activeHead = wv;
					this->inv->removeItemVectorSmart(wv);
					break;

				case armourType::CHEST:
					//this->addItem(wv);
					if (this->activeChest != NULL) {
						this->addItem(this->activeChest);
					}
					this->activeChest = wv;
					this->inv->removeItemVectorSmart(wv);
					break;

				case armourType::ARMS:
					//this->addItem(wv);
					if (this->activeArms != NULL) {
						this->addItem(this->activeArms);
					}
					this->activeArms = wv;
					this->inv->removeItemVectorSmart(wv);
					break;

				case armourType::LEGS:
					//this->addItem(wv);
					if (this->activeLegs != NULL) {
						this->addItem(this->activeLegs);
					}
					this->activeLegs = wv;
					this->inv->removeItemVectorSmart(wv);

					/*	this->inventory.addItem(this->armourLegs);
						this->armourLegs = *a;
						this->inventory.removeItem(index);*/
					break;

				default:
					cout << "ERROR IN ARMOUR TYPE!\n\n";
					break;
				}
}
}

void Entity::resetHP(){

    attributeComponent->updateStats(true);
}

int Entity::getMaxDamageWithWeapon() {
	int max = 0;
	if (this->activeWeapon != NULL) {
		max = dynamic_cast<Weapon&>(*activeWeapon).getDamageMax();
	}

	//max += this->damageMax;

	return max;
}

int Entity::getMinDamageWithWeapon(){
	int min = 0;
	if (this->activeWeapon != NULL) {
		min = dynamic_cast<Weapon&>(*activeWeapon).getDamageMin();
	}

	//min += this->damageMin;

	return min;
}

int Entity::getMinDefenceWithArmour(){

    int mini = 0;
    if(this->activeArms != NULL){

        mini += dynamic_cast<Armour&>(*activeArms).getDefenceMin();
    }
    if(this->activeChest != NULL){

        mini += dynamic_cast<Armour&>(*activeChest).getDefenceMin();
    }
    if(this->activeHead != NULL){

        mini += dynamic_cast<Armour&>(*activeHead).getDefenceMin();
    }
    if(this->activeLegs != NULL){

        mini += dynamic_cast<Armour&>(*activeLegs).getDefenceMin();
    }

    return mini;
}

int Entity::getMaxDefenceWithArmour(){

    int mini = 0;
    if(this->activeArms != NULL){

        mini += dynamic_cast<Armour&>(*activeArms).getDefenceMax();
    }
    if(this->activeChest != NULL){

        mini += dynamic_cast<Armour&>(*activeChest).getDefenceMax();
    }
    if(this->activeHead != NULL){

        mini += dynamic_cast<Armour&>(*activeHead).getDefenceMax();
    }
    if(this->activeLegs != NULL){

        mini += dynamic_cast<Armour&>(*activeLegs).getDefenceMax();
    }

    return mini;
}

int Entity::getDefence(){

    int defence = 0;
    defence += attackComponent->getTotalDefence();

    if(activeHead != nullptr){

        attackComponent->calculateArmourModifier(dynamic_cast<Armour &>(*activeHead));

        defence += attackComponent->getTotalDefence();
    }
    if(activeChest != nullptr){

        attackComponent->calculateArmourModifier(dynamic_cast<Armour &>(*activeChest));
        defence += attackComponent->getTotalDefence();
    }
    if(activeArms != nullptr){

        attackComponent->calculateArmourModifier(dynamic_cast<Armour &>(*activeArms));
        defence += attackComponent->getTotalDefence();
    }
    if(activeLegs != nullptr){

        attackComponent->calculateArmourModifier(dynamic_cast<Armour &>(*activeLegs));
        defence += attackComponent->getTotalDefence();
    }

    return defence;
}

float Entity::getPositionXSave() {

	return float();
}

float Entity::getPositionYSave() {

	return float();
}


//Functions

float Entity::calculateDefence(){

	float total = 0.0f;

	total += this->getSkill(SKILLS::DEFENCE);

	return total;
}

std::shared_ptr<Item> Entity::getItem(int index){

	return inv->findItemSmart(index);
}

void Entity::removeItem(int index){

	this->inv->removeItemVectorSmart(this->inv->findItemSmart(index));
}

void Entity::addComponent(std::shared_ptr<Component> comp){

	int myOrder = comp->getUpdateOrder();

	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter) {

		if (myOrder < (*iter)->getUpdateOrder()) {

			break;
		}
	}

	mComponents.insert(iter, comp);
}

void Entity::removeComponent(std::shared_ptr<Component> comp){

	if (!mComponents.empty()) {

		auto iter = std::find(mComponents.begin(), mComponents.end(), comp);

		if (iter != mComponents.end()) {

			mComponents.erase(iter);
		}
	}
}

void Entity::updateComponents(){

	for (auto i : mComponents) {

		i->update();
	}
}

void Entity::update(){


}

bool Entity::getDialogueActive(){

    if(dialogueComponent != nullptr){

        return dialogueComponent->getTextBoxActive();
    }
    else{

        return false;
    }
}

void Entity::setDialogueActive(bool n){

    if(dialogueComponent){

        dialogueComponent->setTextBoxActive(n);
    }
}

void Entity::setDialogueText(std::string txt){

    dialogueComponent->setDialogueText(txt);
}

void Entity::setCharacterName(std::string name){

    m_name = name;

    if(dialogueComponent != nullptr){

        dialogueComponent->setHeader(m_name);
    }
}



void Entity::renderDialogue(){

    if(dialogueComponent->getTextBoxActive()){

        dialogueComponent->render();
    }
}


void Entity::render(){

	//if (this->hitboxComponent)
	//	this->hitboxComponent->Render(target);
	//
	//target.draw(this->sprite);
}

std::string Entity::displaySkills(){

    return skillComponent->displaySkills();
}
