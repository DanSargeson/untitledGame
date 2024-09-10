#ifndef KEY_H
#define KEY_H

#include "Item.h"

enum keyTypes {

	RUSTY_KEY,
    IRON_KEY,
    STEEL_KEY,
    TITANIUM_KEY,
    MYTHRIL_KEY,
    DIAMOND_KEY

};

class Key : public Item{

private:
	int type;
	//string strType;

public:
	Key();
    Key(int type, string name, int level, int buyValue, int sellValue, int rarity);
	Key(int level, int rarity);
	virtual ~Key();

    virtual Key* clone() const;

    string toString();
	string toStringSave();

	inline string getKeyName() { string n = this->getName(); n += " " + getTypeStr(); return n; }

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
