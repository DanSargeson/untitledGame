#ifndef ATTACKCOMPONENT_H
#define ATTACKCOMPONENT_H

#include "SkillComponent.h"
#include "AttributeComponent.h"
#include "Weapon.h"
#include "Armour.h"


enum ELEMENT_TYPE {

	NORMAL = 0,
	ICE,
	FIRE,
	GRASS,
	EARTH,
	WATER,
	AIR
};


class AttackComponent : public Component{

private:

	//SkillComponent* skillComponent;
	//std::shared_ptr<class SkillComponent> skillComponent;
	//AttributeComponent* attributeComponent;
	//std::shared_ptr<AttributeComponent> attributeComponent;

	std::map<std::string, int> magicTable;

	int baseDmg;
	int magicMod;
	int weaponMod;
	int armourMod;
	int defMod;
	int totalAttack;


public:

	AttackComponent(std::shared_ptr<Entity> owner);
	virtual ~AttackComponent();

	int getTotalAttack();
	void calculateElementBonus(int type = 0);
	int getMagicDamage(int type);
	void calculateWeaponModifier(Weapon& weaponMod);
	void calculateArmourModifier(Armour& defMod);

	int getMinDefence();
	int getMaxDefence();
	int getBaseMinDamage();
	int getBaseMaxDamage();
	int getTotalDamage();
	int getTotalDefence();
};

#endif
