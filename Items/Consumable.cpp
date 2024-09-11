#include "Consumable.h"

//dArray<string> Consumable::names;
//
//void Consumable::initNames() {
//	Consumable::names.push("Rusty-Sword");
//	Consumable::names.push("Iron-Sword");
//	Consumable::names.push("Titanium-Sword");
//	Consumable::names.push("Rusty-Axe");
//	Consumable::names.push("Iron-Axe");
//	Consumable::names.push("Titanium-Axe");
//}

vector<string> Consumable::vecNames;


///Rock/Paper/Scissors. RED > GREEN > BLUE > RED
/// WHITE/BLACK are their own thing, they are each effective against the base colours but weak against gold.
/// GOLD beats white/black. Normal against red/green/blue

void Consumable::initVecNames() {
	Consumable::vecNames.push_back("Common");
	Consumable::vecNames.push_back("Uncommon");
	Consumable::vecNames.push_back("Rare");
	Consumable::vecNames.push_back("Mythic");
	Consumable::vecNames.push_back("Legendary");
}

Consumable::Consumable() : Item() {

	initVecNames();
}

Consumable::Consumable(int type, string name, int level, int buyValue, int sellValue, int rarity)
              : Item(itemTypes::KEY, name, level, buyValue, sellValue, rarity){
	this->type = type;


	switch (this->type) {
	case HEALTH_BOOST:
		this->strType = "Drink to get  some bonus health";
		break;
	case DAMAGE_HEALTH:
		this->strType = "Can be used to lower health";
		break;
	case MAGIC_BOOST:
		this->strType = "Drink to get  some bonus magicka";
		break;

    case DAMAGE_MAGIC:
        this->strType = "Lowers magicka";
        break;

    case SPEED_TIME:
        strType = "Adds a multiplies to the game time";
        break;

    case SLOW_TIME:
        strType = "Adds a negative multiplier to game time";
        break;

	default:
		this->strType = "Consumable Type Error";
		break;
	}

	initVecNames();
}

Consumable::Consumable(int level, int rarity): Item(level, rarity) {

	initVecNames();
    this->rarity = rarity;
	this->setItemType(KEY);

	switch(rarity){

        case rarity::COMMON:
            itemColour = { 255, 255, 255};
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

	this->type = rand() % 3;
	switch (this->type) {
	case HEALTH_BOOST:
		this->strType = "Drink to get  some bonus health";
		break;
	case DAMAGE_HEALTH:
		this->strType = "Can be used to lower health";
		break;
	case MAGIC_BOOST:
		this->strType = "Drink to get  some bonus magicka";
		break;

    case DAMAGE_MAGIC:
        this->strType = "Lowers magicka";
        break;

    case SPEED_TIME:
        strType = "Adds a multiplier to the game time";
        break;

    case SLOW_TIME:
        strType = "Adds a negative multiplier to game time";
        break;

	default:
		break;
	}
	this->setName(Consumable::vecNames[this->getRarity()]);
}


Consumable::~Consumable(){

}

string Consumable::toString(){

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


	string str = this->strType + " " + this->getName()
		+ "\nLevel: " + to_string(this->getLevel()) + " "
		+ "\nRarity: " + rarityStr + " "
		+ "\nBuy Value: " + to_string(this->getBuyValue()) + " "
		+ "\nSell Value: " + to_string(this->getSellValue());

		str += "\n\nConsumables can be used on treasure chests, find a chest on the world map to use your key.";

    return str;
}

string Consumable::toStringSave() {
	string str =
		to_string(this->getItemType()) + " " +
		this->getName() + " " +
		to_string(this->getLevel()) + " " +
		to_string(this->getRarity()) + " " +
//		to_string(this->damageMin) + " " +
//		to_string(this->damageMax) + " " +
		to_string(this->type) + " ";

	return str;
}

Consumable* Consumable::clone()const{

    return new Consumable(*this);
}
