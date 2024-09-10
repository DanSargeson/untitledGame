#include "stdafx.h"
#include "AttackComponent.h"

AttackComponent::AttackComponent(std::shared_ptr<Entity> owner) : Component(owner){

	//this->skillComponent = skillComp;
	//this->attributeComponent = attriComp;

	this->baseDmg = 5; ///(this->skillComponent->getSkill(SKILLS::MELEE));

	this->magicTable["NORMAL"] = 5;
	this->magicTable["FIRE"] = 5;
	this->magicTable["ICE"] = 5;
	this->magicTable["GRASS"] = 5;
	this->magicTable["EARTH"] = 5;
	this->magicTable["WATER"] = 5;
	this->magicTable["AIR"] = 5;

	this->magicMod = 0;
	this->totalAttack = 0;
	this->weaponMod = 0;
	this->armourMod = 0;
	defMod = 0;
}

AttackComponent::~AttackComponent(){

}

int AttackComponent::getTotalAttack(){

	return this->totalAttack;
}

void AttackComponent::calculateElementBonus(int type) {

	switch (type) {

	case ELEMENT_TYPE::NORMAL:
		break;

	case ELEMENT_TYPE::FIRE:
		this->magicMod = magicTable["FIRE"];
		break;

	case ELEMENT_TYPE::ICE:
		this->magicMod = magicTable["ICE"];
		break;

	case ELEMENT_TYPE::GRASS:
		this->magicMod = magicTable["GRASS"];
		break;

	case ELEMENT_TYPE::WATER:
		this->magicMod = magicTable["WATER"];
		break;

	case ELEMENT_TYPE::EARTH:
		this->magicMod = magicTable["EARTH"];
		break;

	case ELEMENT_TYPE::AIR:
		this->magicMod = magicTable["AIR"];
		break;

	default:
		break;
	}
}

int AttackComponent::getMagicDamage(int type) {

	switch (type) {

	case ELEMENT_TYPE::AIR:
		return this->magicTable["AIR"];
		break;

	case ELEMENT_TYPE::EARTH:
		return this->magicTable["EARTH"];
		break;

	case ELEMENT_TYPE::FIRE:
		return this->magicTable["FIRE"];
		break;

	case ELEMENT_TYPE::GRASS:
		return this->magicTable["GRASS"];
		break;

	case ELEMENT_TYPE::ICE:
		return this->magicTable["ICE"];
		break;

	case ELEMENT_TYPE::NORMAL:
		return this->magicTable["NORMAL"];
		break;

	case ELEMENT_TYPE::WATER:
		return this->magicTable["WATER"];
		break;

	default:
		return this->magicTable["NORMAL"];
		break;
	}
}

void AttackComponent::calculateArmourModifier(Armour& armour) {

	//USED TO  DETERMINE WETHER THE WEAPON HITS WITH MIN - MAX DAMAGE..
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(static_cast<unsigned>(seed));


	int minWeapon = armour.getDefenceMin();
	int maxWeapon = armour.getDefenceMax();

	std::uniform_int_distribution<int> dmgDist(minWeapon, maxWeapon);
	this->armourMod = dmgDist(generator);
}

int AttackComponent::getMinDefence(){


    int minDefence = (mOwner->getSkill(SKILLS::DEFENCE));

	///minDamage += this->skillComponent->getSkill(SKILLS::MELEE);

	return minDefence;
}

int AttackComponent::getMaxDefence(){

    int maxDef = 0;

	maxDef += (mOwner->getSkill(SKILLS::DEFENCE) * 1.5);

	return maxDef;
}

void AttackComponent::calculateWeaponModifier(Weapon& weapon) {

	//USED TO  DETERMINE WETHER THE WEAPON HITS WITH MIN - MAX DAMAGE..
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(static_cast<unsigned>(seed));


	int minWeapon = weapon.getDamageMin();
	int maxWeapon = weapon.getDamageMax();

	std::uniform_int_distribution<int> dmgDist(minWeapon, maxWeapon);
	this->weaponMod = dmgDist(generator);
}

int AttackComponent::getBaseMinDamage(){


    int t1 = mOwner->getSkill(SKILLS::MELEE);
    int t2 = t1 * 0.10;
    int t3 = t1 * 0.5;

	int minDamage = (mOwner->getSkill(SKILLS::MELEE));

	///minDamage += this->skillComponent->getSkill(SKILLS::MELEE);

	return minDamage;
}

int AttackComponent::getBaseMaxDamage(){

	int maxDamage = 0;

	maxDamage += (mOwner->getSkill(SKILLS::MELEE) * 2);

	return maxDamage;
}

int AttackComponent::getTotalDamage() {

	 int mini = getBaseMinDamage();
    int maxi = getBaseMaxDamage();




            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(mini, maxi);
            totalAttack = dis(gen);

    totalAttack += weaponMod;
	return this->totalAttack;
}

int AttackComponent::getTotalDefence(){


    int mini = getMinDefence();
    int maxi = getMaxDefence();

	// Use std::random_device to obtain a seed for the random number generator
            std::random_device rd;

                // Use std::mt19937 as the random number generator
                std::mt19937 gen(rd());

                // Use std::uniform_int_distribution to generate random indices
                std::uniform_int_distribution<> dis(mini, maxi);

    int totalDefence = dis(gen);

    return totalDefence;
}
