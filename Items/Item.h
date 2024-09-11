#ifndef ITEM_H
#define ITEM_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif // WIN32

#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
//#include "dArray.h"

using namespace std;

enum rarity {
	COMMON = 0,
	UNCOMMON,
	RARE,
	MYTHIC,
	LEGENDARY
};

enum itemTypes {
	WEAPON,
	ARMOUR,
	RESOURCE,
	POTION,
	KEY,
	CONSUMABLE
};

class Item{

public:
	Item();
    Item(int itemType, string name, int level, int buyValue, int sellValue, int rarity);
    Item(string name);
	Item(int level, int rarity);
    virtual ~Item();

    inline string debugPrint() const { return this->name;}
    virtual Item* clone() const = 0;
	virtual string toString() = 0;
	virtual string toStringSave() = 0;

    //Accessors
    inline const string& getName() const { return this->name; }
    inline const int& getLevel() const { return this->level; }
    inline const int& getBuyValue() const { return this->buyValue; }
    inline const int& getSellValue() const { return this->sellValue; }
    inline const int& getRarity() const { return this->rarity; }
	inline const int& getItemType() { return this->itemType; }
	inline std::string getTypeStr() { return this->strType; }

	virtual std::string getInfo(){

        std::string msg = "";
        msg += name + " " + strType;

        return msg;
	}

	SDL_Colour getItemColour();

    //Modifiers
	inline void setName(string name) { this->name = name; }
	inline void setItemType(int type) { this->itemType = type; }

	//static
	//static vector<string> vectorNames;
	//static void initVecNames();

private:
    string name;
    int buyValue;
    int sellValue;
    int level;
	int itemType;

protected:
    int rarity;
	std::string strType;
	SDL_Color itemColour;
};
#endif // ITEM_H
