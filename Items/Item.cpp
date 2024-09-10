#include "Item.h"



//vector<string> Item::vectorNames;
//
//void Item::initVecNames() {
//	Item::vectorNames.push_back("Rusty Sword");
//	Item::vectorNames.push_back("Iron Sword");
//	Item::vectorNames.push_back("Titanium Sword");
//	Item::vectorNames.push_back("Rusty Axe");
//	Item::vectorNames.push_back("Iron Axe");
//	Item::vectorNames.push_back("Titanium Axe");
//}

Item::Item() {
	this->itemType = -1;
	this->name = "NONE";
	this->level = 0;
	this->rarity = 0;
	this->sellValue = 0;
	this->buyValue = 0;

	itemColour = {0, 0, 0, 255};
}

Item::Item(int level, int rarity) {
	this->name = "Scrap Metal";
	this->level = level;
	if (rarity < 0) {
		rarity = 0;
	}
	this->rarity = rarity;
	this->buyValue = level * (this->rarity+1)*10;
	this->sellValue = this->buyValue / 2;
}

SDL_Color Item::getItemColour(){

        switch(this->rarity){

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

        return itemColour;
}

Item::Item(int itemType, string name, int level, int buyValue, int sellValue, int rarity){
	this->itemType = itemType;
	this->name = name;
    this->level = level;
    this->buyValue = buyValue;
    this->sellValue = sellValue;
    this->rarity = rarity;

	this->buyValue = level * (this->rarity + 1) * 10;
	this->sellValue = this->buyValue / 2;
}

Item::Item(string name){
    this->name = name;
}

//void Item::initVecNames() {
//
//}
//
//void Item::initNames() {
//
//}

Item::~Item(){
}
