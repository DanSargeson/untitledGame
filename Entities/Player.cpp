#include "Player.h"
#include "State.h"
#include "FactionComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"
#include "AttackComponent.h"
#include "Entity.h"

std::string Player::saveAttributes(){

    std::string msg = "";

    msg += std::to_string(getAttribute(ATTRIBUTE::VITALITY)) + " ";
    msg += std::to_string(getAttribute(ATTRIBUTE::STRENGTH)) + " ";
    msg += std::to_string(getAttribute(ATTRIBUTE::DEXTERITY)) + " ";
    msg += std::to_string(getAttribute(ATTRIBUTE::AGILITY)) + " ";
    msg += std::to_string(getAttribute(ATTRIBUTE::INTELLIGENCE)) + " ";
    msg += std::to_string(getAttribute(ATTRIBUTE::CHARISMA)) + " ";
    msg += std::to_string(getAttribute(ATTRIBUTE::LUCK)) + " ";
    msg += std::to_string(attributeComponent->getAttributePoints()) + " ";

    return msg;
}

void Player::setAttributes(int v, int s, int d, int a, int i, int c, int l){

    attributeComponent->setAttribute(ATTRIBUTE::VITALITY, v);
    attributeComponent->setAttribute(ATTRIBUTE::STRENGTH, s);
    attributeComponent->setAttribute(ATTRIBUTE::DEXTERITY, d);
    attributeComponent->setAttribute(ATTRIBUTE::AGILITY, a);
    attributeComponent->setAttribute(ATTRIBUTE::INTELLIGENCE, i);
    attributeComponent->setAttribute(ATTRIBUTE::CHARISMA, c);
    attributeComponent->setAttribute(ATTRIBUTE::LUCK, l);
}

void Player::increaseAttribute(int i ){

    attributeComponent->increaseAttribute(i);
}

void Player::decreaseAttribute(int i ){

    attributeComponent->decreaseAttribute(i);
}

void Player::increaseSkill(int i){

    skillComponent->increaseSkill(i);
}

Player::Player() : Entity(){
    distanceTravelled = 0;

    gold = 0;
    name = "";
//    level = 0;
//    exp = 0;
//    expNext = 0;
//
//    strength = 0;
//    vitality = 0;
//    dexterity = 0;
//    intelligence = 0;
//
//    hp = 0;
//    hpMax = 0;
//    stamina = 0;
//    staminaMax = 0;
//    damageMin = 0;
//    damageMax = 0;
//    defence = 0;
//    accuracy = 0;
//    luck = 0;


    //this->createAttributeComponent(1, true);
	//this->createSkillComponent();
	//this->createFactionComponent();

	//this->skillComponent->calculateSkills(attributeComponent);
	//this->createAttackComponent(skillComponent, attributeComponent);
	//createAttackComponent();


    //statPoints = 0;
    //skillPoints = 0;

    //attributeComponent->updateStats(true);
    corruption = 0;
}

Player::Player(string n, int dt, int g, int lvl, int exp, int vit, int str, int dex, int agi,
                     int intel, int charis, int luck, int hp, int corr, int attriPoint, bool reset) : Entity(){
    this->name = n;
    this->m_level = lvl;
    this->gold = g;
    corruption = corr;

   //this->createAttributeComponent(level, true, false);
   //attributeComponent->setAttributes(vit, str, dex, agi, intel, charis, luck);
   //attributeComponent->setAttributePoints(attriPoint);


	//this->createSkillComponent();
	//this->createFactionComponent();
   //attributeComponent->loadAttribute(lvl, exp, hp, vit, str, dex, agi, intel, charis, luck);

	//attributeComponent->updateLevel();
	//attributeComponent->updateStats(true);
	//skillComponent->calculateSkills(attributeComponent);
	//updateStats(false);
	//createAttackComponent();
	//attributeComponent->setHP(hp);
	//attributeComponent->setXP(exp);
}

void Player::loadBonuses(){

    if(attributeComponent && !followers.empty()){

        attributeComponent->loadBonuses(followers.back()->getType()/*, followers.back()->getLevel()*/);
        calculateSkills();
    }
}

Player::Player(string name, int dt) : Entity(){
//    this->name = name;
    this->distanceTravelled = dt;

    this->createAttributeComponent(0, true);
	this->createSkillComponent();
	this->createFactionComponent();
	createAttackComponent();
}

Player::~Player(){
}

void Player::initialise(string name){
    this->name = name;
//    this->gold = 0;
//    this->distanceTravelled = 0;
//    this->level = 1;
//    this->exp = 0;
//    this->expNext = static_cast<int>((50/3)*((pow(level,3) - 6*pow(level,2)) + 17*level - 12)) + 100;
//
//    this->strength = 5;
//    this->vitality = 5;
//    this->dexterity = 5;
//    this->intelligence = 5;
//
//    //this->hpMax = (this->vitality * 2) + (this->strength / 2);
//    this->hpMax = (this->vitality * 2) + (this->strength / 2) + level;
//    this->hp = hpMax;
//    this->staminaMax = this->vitality + (this->strength / 2) + (this->dexterity / 3);
//    this->stamina = this->staminaMax;
//    this->damageMin = this->strength;
//    this->damageMax = this->strength + 2;
//    this->defence = this->dexterity + (this->intelligence / 2);
//    this->accuracy = (this->dexterity / 2) + intelligence;
//    this->luck = this->intelligence;


    corruption = 0;
    //this->statPoints = 0;
    //this->skillPoints = 0;
}

std::string Player::printPlayerDetails(){

    std::string msg = "";
//    msg += " = Player SHEET = \n\n";
//    msg += "Name: " + this->name + " ";
//    msg += "| Level: " + std::to_string(this->level) + " ";
//    msg += "| EXP: " + std::to_string(this->exp) + " ";
//    msg += "| Exp to next level: " + std::to_string(expNext) + " ";
//    msg += "| HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax) + "\n";
//    //cout + std::setw(10) + std::setfill("=") + endl;
//    msg += "Strength: " + std::to_string(strength) + " ";
//    msg += "| Vitality: " + std::to_string(this->vitality) + " ";
//    msg += "| Dexterity: " + std::to_string(this->dexterity) + " ";
//    msg += "| Intelligence: " + std::to_string(this->intelligence) + " ";
//    //cout + std::setw(10) + std::setfill("=") + endl;
//    msg += "| Accuracy: " + std::to_string(this->accuracy) + " ";
//    msg += "| Luck: " + std::to_string(this->luck) + "\n";
//    msg += "| Stamina: " + std::to_string(this->stamina) + "/" + std::to_string(this->staminaMax) + "\n";
//    msg += "Damage: " + std::to_string(this->damageMin) + " (" +
//        std::to_string(getMinDamageWithWeapon()) + ")" + " - " + std::to_string(this->damageMax) + " (" + std::to_string(getMaxDamageWithWeapon()) + ") ";
//    msg += "| Defence: " + std::to_string(this->defence) + " (" + std::to_string(getDefenceTotal()) + ")" + " ";
//    msg += "\n";
//	msg += "Distance Travelled: " + std::to_string(this->distanceTravelled) + " ";
//	msg += "| Gold: " + std::to_string(this->gold) + "\n\n";
//	msg += "Equipped Weapon: ";
//	if (this->activeWeapon != NULL) {
//
//        auto wv = std::dynamic_pointer_cast<Weapon>(activeWeapon);
//		msg += wv->getWeaponName() + "\n";
//	}
//	else {
//		msg += " Empty\n";
//	}
//	msg += "Equipped Armour Head: ";
//	if (this->activeHead != NULL) {
//
//        auto wv = std::dynamic_pointer_cast<Armour>(activeHead);
//        msg += wv->getArmourName() + "\n";
////		 msg += this->activeHead->getArmourName() + "\n";
//	}
//	else {
//		msg += " Empty\n";
//	}
//	msg += "Equipped Armour Chest: ";
//	if (this->activeChest != NULL) {
//        auto wv = std::dynamic_pointer_cast<Armour>(activeChest);
//        msg += wv->getArmourName() + "\n";
//	}
//	else {
//		msg += " Empty\n";
//	}
//	msg += "Equipped Armour Arms: ";
//	if (this->activeArms != NULL) {
//		auto wv = std::dynamic_pointer_cast<Armour>(activeArms);
//        msg += wv->getArmourName() + "\n";
//	}
//	else {
//		msg += " Empty\n";
//	}
//	msg += "Equipped Armour Legs: ";
//	if (this->activeLegs != NULL) {
//		auto wv = std::dynamic_pointer_cast<Armour>(activeLegs);
//        msg += wv->getArmourName() + "\n";
//	}
//	else {
//		msg += " Empty\n";
//	}

	//cout << "\n";


	msg += factionComponent->getFactionsStrSave();

	return msg;
}

string Player::getStatsAsString() const{

    std::string deets;

    int hp, hpMax;

	hp = static_cast<int>(this->attributeComponent->getHP());
	hpMax = static_cast<int>(this->attributeComponent->getHPMax());

	int xp = static_cast<int>(this->attributeComponent->getEXP());
	int xpNext = static_cast<int>(this->attributeComponent->getEXPNext());

	int level = attributeComponent->getLevel();

	deets += name + " " +
		to_string(/*distanceTravelled*/92809) + " " +
		to_string(level) + " " +
		to_string(hp) + " " +
		to_string(xp) + " " +
		to_string(gold) + " " +
		to_string(corruption);

    return deets;
}

std::string Player::getStatsAttributeScreen(){

	std::string deets;

	int hp, hpMax;

	//gold = 0;
	hp = static_cast<int>(this->attributeComponent->getHP());
	hpMax = static_cast<int>(this->attributeComponent->getHPMax());

	int xp = static_cast<int>(this->attributeComponent->getEXP());
	int xpNext = static_cast<int>(this->attributeComponent->getEXPNext());

	if(gold < 0){

        gold = 0;
	}

	deets += "Name: " + this->name + "\n";
	deets += "Level: " + std::to_string(this->attributeComponent->getLevel()) + "\n";
	deets += "HP: " + std::to_string(hp) + " / " + std::to_string(hpMax) + "\n";
	deets += "Exp: " + std::to_string(xp) + " / " + std::to_string(xpNext) + "\n";
	deets += "Gold: " + std::to_string(gold) + "\n";

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

//std::string Player::getInvItemAsString(int choice){
//
//    return this->inv->getInvItemAsString(choice);
//}
//
//std::string Player::getArmAsString(int choice){
//
//    return this->inv->getArmAsString(choice);
//}
//
//
//std::string Player::getWepAsString(int choice){
//
//    return this->inv->getWepAsString(choice);
//}


//SDL_Color Player::getItemColour(int choice){
//
//    return this->inv->getInvItemColour(choice);
//}


std::vector<std::shared_ptr<GUI::Text>> Player::getFollowersAsStrVec(){

    std::vector<std::shared_ptr<GUI::Text>> vec;
    for(unsigned i = 0; i < followers.size(); i++){
            vec.push_back(std::make_shared<GUI::Text>());
            std::string msg = followers[i]->getName() + " LVL: " + std::to_string(followers[i]->getLevel()) + " HP: " + std::to_string(followers[i]->getHP()) + "/" + std::to_string(followers[i]->getHPMax()) + " EXP: " + std::to_string(followers[i]->getExp()) + "/" + std::to_string(followers[i]->getExpNext()) + "\n";
            vec[i]->setString(msg, true);
        }

    return vec;
}

std::string Player::printFollowers(){

    std::string msg = "";

    if(followers.empty()){

        msg = "No followers";
    }
    else{

        for(unsigned i = 0; i < followers.size(); i++){

            msg += followers[i]->getName() + " LVL: " + std::to_string(followers[i]->getLevel()) + " HP: " + std::to_string(followers[i]->getHP()) + "/" + std::to_string(followers[i]->getHPMax()) + " EXP: " + std::to_string(followers[i]->getExp()) + "/" + std::to_string(followers[i]->getExpNext()) + "\n";
        }
    }

    return msg;
}

std::string Player::getFollowersStrSave(){

    std::string msg = "";
    if(!followers.empty()){

        for(unsigned i = 0; i < followers.size(); i++){

            msg += std::to_string(followers[i]->getType()) + " "
            + std::to_string(followers[i]->getLevel()) + " "
            + std::to_string(followers[i]->getSavedFaction()) + " "
            + std::to_string(followers[i]->getHP()) + " "
            + std::to_string(followers[i]->getExp()) + " ";
        }
    }

    return msg;
}

void Player::loadFactions(int black, int white, int red, int orange, int yellow, int green, int blue, int indigo, int violet)
{
    if(factionComponent != nullptr){

        factionComponent->loadFactions(black, white, red, orange, yellow, green, blue, indigo, violet);
    }
}


string Player::getInvAsString() {

	return this->inv->getInvAsString();
}

std::vector<std::string> Player::getWepAsVec(){

    return inv->getWepAsVecOps();
}

std::vector<std::string> Player::getArmAsVec(){

    return inv->getArmAsVecOps();
}


string Player::getInvAsStringSave() {

	return this->inv->getInvAsStringSave();

}

void Player::setAttributePoints(int p){

    attributeComponent->setAttributePoints(p);
}

int Player::getAttributePoints(){

    return attributeComponent->getAttributePoints();
}

//void Player::levelUp(){
//
//    bool levelled;
//
//    attributeComponent->updateLevel();
//
////    if(this->exp >= this->expNext){
////        this->exp -= this->expNext;
////        this->level++;
////        this->expNext = static_cast<int>((50/3)*((pow(level,3) - 6*pow(level,2)) + 17*level - 12)) + 100;
////
////        this->statPoints++;
////        this->skillPoints++;
////
////        //return true;
////
////        std::string msg =  "You are now level " + std::to_string(this->level) + "!";
////        getMainText()->setString(msg);
////
////        updateStats();
////        this->hp = this->hpMax;
////    }
////    else{
////        getMainText()->setString("You do not have enough experience.");
////        //return false;
////    }
//}

//void Player::updateStats(bool reset){
//
//    attributeComponent->updateStats(reset);
//}

void Player::removeBonuses(int type){

    attributeComponent->removeBonuses(type);
    calculateSkills();
}

void Player::addStat(int stat, int value) {



//	if (this->statPoints < value) {
//		//cout << "Error not enough stat points!" << "\n";
//	}
//	else {
//
//		switch (stat) {
//		case 0:
//			this->strength += value;
//			break;
//		case 1:
//			this->vitality += value;
//			break;
//		case 2:
//			this->dexterity += value;
//			break;
//		case 3:
//			this->intelligence += value;
//			break;
//		default:
//			cout << "Add Stat function failed." << "\n";
//			break;
//		}
//
//		this->statPoints -= value;
//		updateStats();
//	}
}

int Player::takeDamage(int damage) {
//	damage -= this->defence;
//	if (this->activeHead != NULL) {
//		//ADD HELM DEFENCE
//		int def = dynamic_cast<Armour&>(*activeHead).getDefence();
//		damage -= def;
//
//	}
//	else if (this->activeChest != NULL) {
//		//ADD CHEST DEFENCE
//		int def = dynamic_cast<Armour&>(*activeChest).getDefence();
//		damage -= def;
//	}
//	else if (this->activeArms != NULL) {
//		//ADD ARM DEFENCE
//		int def = dynamic_cast<Armour&>(*activeArms).getDefence();
//		damage -= def;
//	}
//	else if (this->activeLegs != NULL) {
//		//ADD LEG DEFENCE
//		int def = dynamic_cast<Armour&>(*activeLegs).getDefence();
//		damage -= def;
//	}
//	if (damage <= 0) {
//		damage = 1;
//	}
//	this->hp -= damage;
//
//	if (this->hp <= 0) {
//		this->hp = 0;
//	}
//
//
//	return damage;

	return 0;
}

void Player::equipWeapon(int index){

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

void Player::equipArmour(int index){

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

void Player::equipItem(int index){
	if (index < 0 || index >= this->inv->smrtSize()) {
		cout << "Equip item out of bounds error!\n\n";
	}
	else {

		shared_ptr<Item> item = this->inv->findItemSmart(index);
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
		else if(item->getItemType() == ARMOUR) {

			//a = dynamic_cast<Armour*>(&this->inventory[index]);
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
			else {
				cout << "Error Trying to equip Item!\n\n";
			}
		}
	}
}

//int Player::getDamage() {
//
//
////    attackComponent->getDamage();
//	int minDmg = 0;
//	int maxDmg = 0;
//
//	if (this->activeWeapon != NULL) {
//		//minDmg = dynamic_cast<Weapon&>(*activeWeapon).getDamageMin();
//		//maxDmg = dynamic_cast<Weapon&>(*activeWeapon).getDamageMax();
//	///	attackComponent->calculateWeaponModifier(<Item>activeWeapon);
//	}
//
//	int minTotal = attackComponent->getBaseMinDamage() + minDmg;
//	int maxTotal = attackComponent->getBaseMaxDamage() + maxDmg;
//
//	int calculatedDamage = minTotal + rand() % ((maxTotal + 1) - minTotal);
//
//	return calculatedDamage;
//}

//int Player::getMinDamageWithWeapon(){
//	int min = 0;
//	if (this->activeWeapon != NULL) {
//		min = dynamic_cast<Weapon&>(*activeWeapon).getDamageMin();
//	}
//
//	//min += this->damageMin;
//
//	return min;
//}

//int Player::getMaxDamageWithWeapon() {
//	int max = 0;
//	if (this->activeWeapon != NULL) {
//		max = dynamic_cast<Weapon&>(*activeWeapon).getDamageMax();
//	}
//
//	//max += this->damageMax;
//
//	return max;
//}

//int Player::getDefenceTotal(){
//	int total = 0;
//	int def = 0;
//	if (this->activeHead != NULL) {
//		def += dynamic_cast<Armour&>(*activeHead).getDefence();
//	}
//	if (this->activeChest != NULL) {
//		def += dynamic_cast<Armour&>(*activeChest).getDefence();
//	}
//	if (this->activeArms != NULL) {
//		def += dynamic_cast<Armour&>(*activeArms).getDefence();
//	}
//	if (this->activeLegs != NULL) {
//		def += dynamic_cast<Armour&>(*activeLegs).getDefence();
//	}
//
////	total = def + this->defence;
//
//	return total;
//}

string Player::getEquippedWeapon() {
	string equipped = "";

	if (this->activeWeapon != NULL) {
		equipped += this->activeWeapon->toStringSave();
	}

	return equipped;
}
//
//const int& Player::getLevel() const{
//
//    return attributeComponent->getLevel();
//}

string Player::getEquippedArmour() {

	string equipped = "";

	if (this->activeHead != NULL) {
		equipped += this->activeHead->toStringSave();
	}
	if (this->activeChest != NULL) {
		equipped += this->activeChest->toStringSave();
	}
	if (this->activeArms != NULL) {

		equipped += this->activeArms->toStringSave();
	}
	if (this->activeLegs != NULL) {
		equipped += this->activeLegs->toStringSave();
	}

	return equipped;
}
