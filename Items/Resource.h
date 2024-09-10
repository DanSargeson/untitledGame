#ifndef RESOURCE_H
#define RESOURCE_H

#include "Item.h"

enum resourceTypes {
	RUSTY_IRON,
	IRON,
	STEEL,
	TITANIUM,
	MYTHRIL,
	DIAMOND
};

class Resource : public Item{

private:
    int damageMin;
    int damageMax;
	int type;
	//string strType;

public:
	Resource();
    Resource(int type, int damageMin, int damageMax, string name, int level, int buyValue, int sellValue, int rarity);
	Resource(int level, int rarity);
	virtual ~Resource();

    virtual Resource* clone() const;

    string toString();
	string toStringSave();

	//ACCESSORS
	inline int getDamageMin() const { return this->damageMin; }
	inline int getDamageMax() const { return this->damageMax; }
	//inline string getTypeStr() const { return getTypeStr(); }
	inline string getResourceName() { string n = this->getName(); n += " " + getTypeStr(); return n; }

	//static
//	static dArray<string> names;
	static vector<string> vecNames;
	static void initVecNames();
	//static void initNames();


    std::string getInfo() override{

        std::string msg = Item::getInfo();
        msg += "\nDmg: " + std::to_string(damageMin) + " - " + std::to_string(damageMax);

        return msg;
	}
};

#endif // WEAPON_H
