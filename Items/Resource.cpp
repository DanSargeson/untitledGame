#include "Resource.h"

//dArray<string> Resource::names;
//
//void Resource::initNames() {
//	Resource::names.push("Rusty-Sword");
//	Resource::names.push("Iron-Sword");
//	Resource::names.push("Titanium-Sword");
//	Resource::names.push("Rusty-Axe");
//	Resource::names.push("Iron-Axe");
//	Resource::names.push("Titanium-Axe");
//}

vector<string> Resource::vecNames;


///Rock/Paper/Scissors. RED > GREEN > BLUE > RED
/// WHITE/BLACK are their own thing, they are each effective against the base colours but weak against gold.
/// GOLD beats white/black. Normal against red/green/blue

void Resource::initVecNames() {
	Resource::vecNames.push_back("Ore");
	Resource::vecNames.push_back("Fragment");
	Resource::vecNames.push_back("Ingot");
	Resource::vecNames.push_back("Plate");  ///For each of the materials, X amount of ores == fragment and so on until Plate which is the final and can be used to upgrade/craft new
}

Resource::Resource() : Item() {
	this->damageMax = 0;
	this->damageMin = 0;

	initVecNames();
}

Resource::Resource(int type, int damageMin, int damageMax, string name, int level, int buyValue, int sellValue, int rarity)
              : Item(itemTypes::RESOURCE, name, level, buyValue, sellValue, rarity){
	this->type = type;
	this->damageMin = damageMin;
    this->damageMax = damageMax;

	switch (this->type) {
	case RUSTY_IRON:
		this->strType = "Rusty";
		break;
	case IRON:
		this->strType = "Ion";
		break;
	case STEEL:
		this->strType = "Steel";
		break;

    case TITANIUM:
        this->strType = "Titanium";
        break;

    case MYTHRIL:
        strType = "Mythril";
        break;

    case DIAMOND:
        strType = "Diamond";
        break;

	default:
		this->strType = "Resource Type Error";
		break;
	}

	initVecNames();
}

Resource::Resource(int level, int rarity): Item(level, rarity) {

	initVecNames();
    this->rarity = rarity;
	this->setItemType(RESOURCE);
	///this->damageMax = rand() % level * (this->getRarity()+1);
	this->damageMax = level + ((this->getRarity()+1) * 2);

	if (this->getRarity() == 3) {
		this->damageMax += level * 5;
	}
	else if (this->getRarity() == 4) {
		this->damageMax += level * 10;
	}

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

	this->damageMin = damageMax / 2;
	this->type = rand() % 3;
	switch (this->type) {
	case RUSTY_IRON:
		this->strType = "Rusty";
		break;
	case IRON:
		this->strType = "Iron";
		break;
	case STEEL:
		this->strType = "Steel";
		break;

    case TITANIUM:
        this->strType = "Titanium";
        break;

    case MYTHRIL:
        strType = "Mythril";
        break;

    case DIAMOND:
        strType = "Diamond";
        break;

	default:
		break;
	}
	this->setName(Resource::vecNames[this->getRarity()]);
}


Resource::~Resource(){

}

string Resource::toString(){

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
		+ "\nDamage: " + to_string(this->damageMin) + " - "
		+ to_string(this->damageMax) + " " +
		+ "\nBuy Value: " + to_string(this->getBuyValue()) + " "
		+ "\nSell Value: " + to_string(this->getSellValue());

    return str;
}

string Resource::toStringSave() {
	string str =
		to_string(this->getItemType()) + " " +
		this->getName() + " " +
		to_string(this->getLevel()) + " " +
		to_string(this->getRarity()) + " " +
		to_string(this->damageMin) + " " +
		to_string(this->damageMax) + " " +
		to_string(this->type) + " ";

	return str;
}

Resource* Resource::clone()const{

    return new Resource(*this);
}
