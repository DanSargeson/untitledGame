#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

enum weaponTypes {
	SWORD,
	AXE,
	DAGGER
};

class Weapon : public Item{

private:
    int damageMin;
    int damageMax;
	int type;
	//string strType;

public:
	Weapon();
    Weapon(int type, int damageMin, int damageMax, string name, int level, int buyValue, int sellValue, int rarity);
	Weapon(int level, int rarity);
	virtual ~Weapon();

    virtual Weapon* clone() const;

    string toString();
	string toStringSave();

	//ACCESSORS
	inline int getDamageMin() const { return this->damageMin; }
	inline int getDamageMax() const { return this->damageMax; }
	//inline string getTypeStr() const { return getTypeStr(); }
	inline string getWeaponName() { string n = this->getName(); n += " " + getTypeStr(); return n; }

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
