#include "Key.h"

//dArray<string> Key::names;
//
//void Key::initNames() {
//	Key::names.push("Rusty-Sword");
//	Key::names.push("Iron-Sword");
//	Key::names.push("Titanium-Sword");
//	Key::names.push("Rusty-Axe");
//	Key::names.push("Iron-Axe");
//	Key::names.push("Titanium-Axe");
//}

vector<string> Key::vecNames;


///Rock/Paper/Scissors. RED > GREEN > BLUE > RED
/// WHITE/BLACK are their own thing, they are each effective against the base colours but weak against gold.
/// GOLD beats white/black. Normal against red/green/blue

void Key::initVecNames() {
	Key::vecNames.push_back("Common");
	Key::vecNames.push_back("Uncommon");
	Key::vecNames.push_back("Rare");
	Key::vecNames.push_back("Mythic");
	Key::vecNames.push_back("Legendary");
}

Key::Key() : Item() {

	initVecNames();
}

Key::Key(int type, string name, int level, int buyValue, int sellValue, int rarity)
              : Item(itemTypes::KEY, name, level, buyValue, sellValue, rarity){
	this->type = type;


	switch (this->type) {
	case RUSTY_KEY:
		this->strType = "Rusty Key";
		break;
	case IRON_KEY:
		this->strType = "Iron Key";
		break;
	case STEEL_KEY:
		this->strType = "Steel Key";
		break;

    case TITANIUM_KEY:
        this->strType = "Titanium Key";
        break;

    case MYTHRIL_KEY:
        strType = "Mythril Key";
        break;

    case DIAMOND_KEY:
        strType = "Diamond Key";
        break;

	default:
		this->strType = "Key Type Error";
		break;
	}

	initVecNames();
}

Key::Key(int level, int rarity): Item(level, rarity) {

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
	case RUSTY_KEY:
		this->strType = "Rusty Key";
		break;
	case IRON_KEY:
		this->strType = "Iron Key";
		break;
	case STEEL_KEY:
		this->strType = "Steel Key";
		break;

    case TITANIUM_KEY:
        this->strType = "Titanium Key";
        break;

    case MYTHRIL_KEY:
        strType = "Mythril Key";
        break;

    case DIAMOND_KEY:
        strType = "Diamond Key";
        break;

	default:
		break;
	}
	this->setName(Key::vecNames[this->getRarity()]);
}


Key::~Key(){

}

string Key::toString(){

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

		str += "\n\nKeys can be used on treasure chests, find a chest on the world map to use your key.";

    return str;
}

string Key::toStringSave() {
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

Key* Key::clone()const{

    return new Key(*this);
}
