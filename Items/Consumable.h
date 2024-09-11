#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Item.h"

enum consumableTypes {

	HEALTH_BOOST,
    DAMAGE_HEALTH,
    MAGIC_BOOST,
    DAMAGE_MAGIC,
    SPEED_TIME,
    SLOW_TIME
};

class Consumable : public Item{

private:
	int type;
	//string strType;

public:
	Consumable();
    Consumable(int type, string name, int level, int buyValue, int sellValue, int rarity);
	Consumable(int level, int rarity);
	virtual ~Consumable();

    virtual Consumable* clone() const;

    string toString();
	string toStringSave();

	inline string getConsumableName() { string n = this->getName(); n += " " + getTypeStr(); return n; }

	//static
//	static dArray<string> names;
	static vector<string> vecNames;
	static void initVecNames();
	//static void initNames();


    std::string getInfo() override{

        std::string msg = Item::getInfo();
//        msg += "\nDmg: " + std::to_string(damageMin) + " - " + std::to_string(damageMax);

        return msg;
	}
};

#endif // WEAPON_H
