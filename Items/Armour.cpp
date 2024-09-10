#include "Armour.h"

std::vector<string> Armour::names;

void Armour::initNames() {

    ///TODO:
    /// FACTIONS ARE WHTA YOU COLECT, THEY AFFECT WHAT COLOURS YOU GET BASE IT ON RGB == 100 to start, they unlock secpmd off that
    ///Start on 40 depending on if you pikc RGB, corruption  == - 1of that


	Armour::names.push_back("Rusty");
	Armour::names.push_back("Iron");
	Armour::names.push_back("Steel");
	Armour::names.push_back("Titanium");
	Armour::names.push_back("Mythril");
	Armour::names.push_back("Diamond");
}

Armour::Armour() : Item() {
	this->defenceMax = 0;
	this->defenceMin = 0;

	initNames();
}

Armour::Armour(int type, int defenceMin, int defenceMax, string name, int level, int buyValue, int sellValue, int rarity)
              : Item(itemTypes::ARMOUR, name, level, buyValue, sellValue, rarity){
    
	
	initNames();
	this->type = type;
    this->defenceMin = defenceMin;
    this->defenceMax = defenceMax;

	switch (this->type) {
	case armourType::HEAD:
		this->strType = "Helm";
		break;

	case armourType::CHEST:
		this->strType = "Cuirass";
		break;

	case armourType::ARMS:
		this->strType = "Gauntlets";
		break;

	case armourType::LEGS:
		this->strType = "Greaves";
		break;

	default:
		this->strType = "ERROR INVALID TYPE";
	}
}

Armour::Armour(int level, int rarity): Item(level, rarity) {

	initNames();
	this->setItemType(itemTypes::ARMOUR);

	///this->setName(Armour::names[rand() % Armour::names.size()]);

	this->defenceMax = rand() % level * (this->getRarity()+1);
	this->defenceMax = level + (this->getRarity()+1);

	this->defenceMin = defenceMax / 2;

//	this->defence = rand() % (level * (this->getRarity()+1)) + (level);
//	this->defence += (this->getRarity()+1) * 2;
	this->type = rand() % 4;

	switch(rarity){

        case rarity::COMMON:
            itemColour = { 255, 0, 0};
            break;

        case rarity::UNCOMMON:
            itemColour = { 0, 255, 0};
            break;

        case rarity::RARE:
            itemColour = { 0, 0, 255};
            break;

        case rarity::MYTHIC:
            itemColour = {255, 0, 255};
            break;

        case rarity::LEGENDARY:
            itemColour = {255, 215, 0};
            break;

        default:
            itemColour = {0, 255, 0};
            break;
	}

	switch (this->type) {
	case armourType::HEAD:
		this->strType = "Helm";
		break;

	case armourType::CHEST:
		this->strType = "Cuirass";
		break;

	case armourType::ARMS:
		this->strType = "Gauntlets";
		break;

	case armourType::LEGS:
		this->strType = "Greaves";
		break;

	default:
		this->strType = "ERROR INVALID TYPE";
	}

	//this->setName(Armour::names[rand() % Armour::names.size()]);
	this->setName(Armour::names[this->getRarity()]);
//	if (rarity == 3) {
//		this->defence += level * 5;
//	}
//	else if (rarity == 4) {
//		this->defence += level * 10;
//	}
}


Armour::~Armour(){

}

Armour* Armour::clone()const{
    return new Armour(*this);
}


string Armour::toString(){

    std::string rarityStr;

    switch(this->getRarity()){

        case rarity::COMMON:
            rarityStr = "Common";
            break;

        case rarity::UNCOMMON:
            rarityStr = "Uncommon";
            break;

        case rarity::RARE:
            rarityStr = "Rare";
            break;

        case rarity::MYTHIC:
            rarityStr = "Mythic";
            break;

        case rarity::LEGENDARY:
            rarityStr = "Legendary";
            break;

        default:
            rarityStr = "ERROR FINDING ITEM RARITY";
            break;
    }

    string str = this->getName() + " " + this->strType
		+ "\n Level: " + to_string(this->getLevel()) + " "
		+ "\n Rarity: " + rarityStr + " "
		+ "\n Defence: " + to_string(this->defenceMin) + " - " + to_string(this->defenceMax) + " "
		+"\n Buy Value: " + to_string(this->getBuyValue()) + " "
		+ "\n Sell Value: " + to_string(this->getSellValue());

    return str;
}

string Armour::toStringSave() {
	string str =
		to_string(this->getItemType()) + " " +
		this->getName() + " " +
		to_string(this->getLevel()) + " " +
		to_string(this->getRarity()) + " " +
		to_string(this->defenceMin) + " " +
		to_string(this->defenceMax) + " " +
		to_string(this->type) + " ";

	return str;
}
