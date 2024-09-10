#include "stdafx.h"
#include "SkillComponent.h"
#include "AttributeComponent.h"

SkillComponent::SkillComponent(std::shared_ptr<Entity> owner) : Component(owner) {


	/*

	Split colours into two skills each, if the player joins the red team they will gain extra vit and melee, blue is extra ranged and defence,

	green/yellow is accuracy and endurance???


	Possibly reblance.






	*/
	mSkills.push_back(Skill(SKILLS::MELEE));			//UNARMED AND MELEE WEAPONS
	mSkills.push_back(Skill(SKILLS::CRIT));			//CRIT CHANCE
	mSkills.push_back(Skill(SKILLS::DEFENCE));			//BLOCK CHANCE
	mSkills.push_back(Skill(SKILLS::ACCURACY));		//HIT CHANCE
	mSkills.push_back(Skill(SKILLS::MAGIC));			//MAGIC CHANCE - MAYBE CHANGE TO ELEMENTAL????
	mSkills.push_back(Skill(SKILLS::STEALTH));			//CHANCE TO BE DETECTED AND CAHNCE CAUGHT STEALING
	mSkills.push_back(Skill(SKILLS::PICKPOCKET));		//rOB CHANCE
	mSkills.push_back(Skill(SKILLS::PERSUASION));		//DIALOGUE OPTIONS - CHANCE TO PERSUADE/INFLUENCE
	mSkills.push_back(Skill(SKILLS::PERCEPTION));		//CHANCE TO DETECT TRAPS AND SEE THROUGH LIARS??
	mSkills.push_back(Skill(SKILLS::DODGE));             //CHANCE TO AVOID ATTACK
	mSkills.push_back(Skill(SKILLS::BARTER));            //Buy/Sell price.
}

SkillComponent::~SkillComponent(){


}


///int SkillComponent::calculateSkillsNEW(std::string attribute_name, int currAttribute){
///
///    /// Assume each attribute has a weight that determines its impact on the skill
///
///    int base_skill_value = 50;
////
///    std::unordered_map<std::string, double> attribute_weight = {
///            {"Vitality", 10},
///            {"Strength", 20},
///            {"Dexterity", 20},
///            {"Agility", 20},
///            {"Intelligence", 20},
///            {"Charisma", 20},
///            {"Luck", 10}
///        };
///
///        /// Calculate the modified skill value based on the attribute's influence
///        double modified_skill_value = base_skill_value + (currAttribute * attribute_weight[attribute_name]);
///
///        /// Ensure the modified skill value stays within a reasonable range (e.g., 1 to 100)
///        modified_skill_value = std::max(1.0, std::min(100.0, modified_skill_value));
///
///
///        std::cout << attribute_name << " : " << std::to_string(modified_skill_value);
///
///        return static_cast<int>(modified_skill_value);
///}

int SkillComponent::getSkill(const unsigned int skill) {

	try {

		if (skill < 0 || skill >= mSkills.size()) {

			throw std::runtime_error("Error::SKILLCOMPONENT::GetSkill - skill not found: " + std::to_string(skill));
		}
		else {

			return mSkills[skill].getLevel();
		}
	}
	catch (std::exception &e) {

		std::ofstream outFile;

		outFile.open("errorLog.txt");

		if (outFile.is_open()) {

			outFile << e.what() << std::endl;

			outFile.close();
		}
	}

	return -1;
}

void SkillComponent::gainExp(const unsigned int skill, const int xp){

	try {


		if (skill < 0 || skill >= mSkills.size()) {

			throw std::runtime_error("Error::SKILLCOMPONENT::GainEXP - skill not found: " + std::to_string(skill));
		}
		else {


			mSkills[skill].gainExp(xp);
		}
	}
	catch (std::exception &e) {

		std::ofstream outFile;

		outFile.open("errorLog.txt");

		if (outFile.is_open()) {

			outFile << e.what() << std::endl;

			outFile.close();
		}
	}
}


void SkillComponent::increaseSkill(int skill){

	mSkills[skill].setLevel(mSkills[skill].getLevel() + 1);
	if (mSkills[skill].getLevel() >= 100) {

		mSkills[skill].setLevel(100);
	}

	std::cout << "New value: " + std::to_string(mSkills[skill].getLevel()) + "\n";
}

void SkillComponent::loadSkills(int skill, int value){

	switch (skill) {

	case SKILLS::ACCURACY:

		mSkills[SKILLS::ACCURACY].setLevel(value);
		break;

    case SKILLS::CRIT:
        mSkills[SKILLS::CRIT].setLevel(value);
        break;

	case SKILLS::DEFENCE:

		mSkills[SKILLS::DEFENCE].setLevel(value);
		break;

	case SKILLS::PICKPOCKET:

		mSkills[SKILLS::PICKPOCKET].setLevel(value);
		break;

    case SKILLS::DODGE:

        mSkills[SKILLS::DODGE].setLevel(value);

	case SKILLS::MAGIC:

		mSkills[SKILLS::MAGIC].setLevel(value);
		break;

	case SKILLS::MELEE:

		mSkills[SKILLS::MELEE].setLevel(value);
		break;

	case SKILLS::PERCEPTION:

		mSkills[SKILLS::PERCEPTION].setLevel(value);
		break;

	case SKILLS::PERSUASION:

		mSkills[SKILLS::PERSUASION].setLevel(value);
		break;

	case SKILLS::BARTER:

		mSkills[SKILLS::BARTER].setLevel(value);
		break;

	case SKILLS::STEALTH:

		mSkills[SKILLS::STEALTH].setLevel(value);
		break;
	}
}

std::string SkillComponent::getSkillName(int skill){

	int type = mSkills[skill].getType();

	std::string msg = "Increased ";

	switch (type) {

	case SKILLS::ACCURACY:
		msg += "Accuracy\n";
		break;

	case SKILLS::DEFENCE:
		msg += "Defence\n";
		break;

	case SKILLS::CRIT:
        msg += "Critical Hit Chance\n";
        break;

    case SKILLS::DODGE:
        msg += "Dodge Chance\n";
        break;

	case SKILLS::STEALTH:
		msg += "Stealth\n";
		break;

	case SKILLS::MELEE:
		msg += "Melee Damage\n";
		break;

	case SKILLS::BARTER:
        msg += "Buy/Sell Value\n";
		break;

	case SKILLS::MAGIC:
		msg += "Magic\n";
		break;

	case SKILLS::PICKPOCKET:
		msg += "Pickpocket\n";
		break;

	case SKILLS::PERCEPTION:
		msg += "Perception\n";
		break;

	case SKILLS::PERSUASION:
		msg += "Persuasion\n";
		break;

	default:
		msg = "Error retrieving skills";
		break;
	}

	//std::to_string(mSkills[skill].getLevel())
	return msg += std::to_string(mSkills[skill].getLevel());
}

void SkillComponent::assignRandomSkills(int level){


	/*

	lvl 1 = 5
	lvl 2 = 0
	lvl 3 = 10
	lvl 4 = 0
	lvl 5 = 15

	*/

	int skillPoint = level * 5;

	unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> skillDistribution(0, 10);

	for (int i = 0; i < skillPoint; i++) {

		int diceRoll = skillDistribution(generator);


		switch (diceRoll) {

		case SKILLS::ACCURACY:
			this->increaseSkill(SKILLS::ACCURACY);
			break;

		case SKILLS::DEFENCE:
			this->increaseSkill(SKILLS::DEFENCE);
			break;

		case SKILLS::PICKPOCKET:
			this->increaseSkill(SKILLS::PICKPOCKET);
			break;

	/*	case SKILLS::LUCK:
			this->increaseSkill(SKILLS::LUCK);
			break;*/

		case SKILLS::MAGIC:
			this->increaseSkill(SKILLS::MAGIC);
			break;

		case SKILLS::MELEE:
			this->increaseSkill(SKILLS::MELEE);
			break;

		case SKILLS::PERCEPTION:
			this->increaseSkill(SKILLS::PERCEPTION);
			break;

		case SKILLS::PERSUASION:
			this->increaseSkill(SKILLS::PERSUASION);
			break;

		case SKILLS::BARTER:
			this->increaseSkill(SKILLS::BARTER);
			break;

        case SKILLS::DODGE:
			this->increaseSkill(SKILLS::DODGE);
			break;

        case SKILLS::CRIT:
            this->increaseSkill(SKILLS::CRIT);
            break;

		case SKILLS::STEALTH:
			this->increaseSkill(SKILLS::STEALTH);
			break;

		default:
			break;
		}

	}
}

void SkillComponent::calculateSkills(std::shared_ptr<AttributeComponent> ac) {


     int base_skill_value = 1;
    std::unordered_map<std::string, double> attribute_weight = {
            {"Vitality", 2},
            {"Strength", 3},
            {"Dexterity", 3},
            {"Agility", 3},
            {"Intelligence", 3},
            {"Charisma", 3},
            {"Luck", 1}
        };



        /// Calculate the modified skill value based on the attribute's influence
///        double modified_skill_value = base_skill_value + (currAttribute * attribute_weight[attribute_name]);

        /// Ensure the modified skill value stays within a reasonable range (e.g., 1 to 100)
///        modified_skill_value = std::max(1.0, std::min(100.0, modified_skill_value));


   ///     std::cout << attribute_name << " : " << std::to_string(modified_skill_value);

//     unsigned seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
//
//     default_random_engine generator;
//
//     generator.seed(seed);
//
//     std::uniform_int_distribution<int> skillDist1(1, 5);
//     int skill1 = skillDist1(generator);
//
//     std::uniform_int_distribution<int> skillDist2(2, 4);
//     int skill2 = skillDist2(generator);

     int skillMod = 4;

     ///((mAttributes[VITALITY] * 4) + mLevel  * 10);

	/*
		LUCK HAS AN AFFECT ON ALL ABILITIES, SLIGHTLY
	*/

	int luckLevel = mOwner->getAttribute(LUCK) + mOwner->getBonus(LUCK);
	int level = mOwner->getLevel();

	/*
		AGILITY
	*/
	int agilityLevel = mOwner->getAttribute(AGILITY) + mOwner->getBonus(AGILITY);

	int dodgeLvl = base_skill_value + (agilityLevel * attribute_weight["Agility"]);
	mSkills[SKILLS::DODGE].setLevel(dodgeLvl + luckLevel);
	mSkills[SKILLS::STEALTH].setLevel(dodgeLvl + luckLevel);


    //DEX
    int dexLevel = mOwner->getAttribute(DEXTERITY) + mOwner->getBonus(DEXTERITY);
    int stealLvl = base_skill_value + (dexLevel * attribute_weight["Dexterity"]);
	mSkills[SKILLS::PICKPOCKET].setLevel(stealLvl + luckLevel);
	mSkills[SKILLS::ACCURACY].setLevel(stealLvl + luckLevel);


	/*
		CHARISMA
	*/

	int charismaLevel = mOwner->getAttribute(ATTRIBUTE::CHARISMA) + mOwner->getBonus(CHARISMA);
	int persuLvl = base_skill_value + (charismaLevel * attribute_weight["Charisma"]);
	mSkills[SKILLS::PERSUASION].setLevel(persuLvl + luckLevel);
	mSkills[SKILLS::BARTER].setLevel(persuLvl + luckLevel);


	/*
		VITALITY
	*/

	int vitLevel = mOwner->getAttribute(ATTRIBUTE::VITALITY) + mOwner->getBonus(VITALITY);
	int defenceLvl = base_skill_value + (vitLevel * attribute_weight["Vitality"]);
	mSkills[SKILLS::DEFENCE].setLevel(defenceLvl + luckLevel);


	/*
		INTELLIGENCE
	*/
	int intLevel = mOwner->getAttribute(ATTRIBUTE::INTELLIGENCE) + mOwner->getBonus(INTELLIGENCE);

	int magLvl = base_skill_value + (intLevel * attribute_weight["Intelligence"]);
	mSkills[SKILLS::MAGIC].setLevel(magLvl);
	mSkills[SKILLS::PERCEPTION].setLevel(magLvl + luckLevel);

	/*
		STRENGTH
	*/

	int strLevel = mOwner->getAttribute(ATTRIBUTE::STRENGTH) + mOwner->getBonus(STRENGTH);

	int meleeLvl = base_skill_value + (strLevel * attribute_weight["Strength"]);
	mSkills[SKILLS::MELEE].setLevel(meleeLvl + luckLevel);
	mSkills[SKILLS::CRIT].setLevel(meleeLvl + luckLevel);


	/*
			NEED TO IMPLEMENT A GOLD DISCOVERY NUMBER AND A CARRY WEIGHT
			WHICH WILL BE AFFECTED BY CHARISMA AND STRENGTH RESPECTIVELY

	*/

	//this->vitality = 0.01f;		//HEALTH + DEFENCE - DONE
	//this->strength = 0.01f;		//MELEE DMG + CARRY WEIGHT????
	//this->dexterity = 0.01f;		//STEALTH + LOCKPICKING		- DONE
	//this->agility = 0.01f;		//RANGED DMG + ACCURACY		- DONE
	//this->intelligence = 0.01f;	//MAGIC + PERCEPTION		- DONE
	//this->charisma = 0.10f;		//PERSUASION + MORE MONEY????
}


std::string SkillComponent::displaySkills(){

    std::string msg = "";
    for(unsigned i = 0; i < mSkills.size(); i++){

        msg += mSkills[i].getTypeAsString() + ": " + std::to_string(mSkills[i].getLevel()) + "\n";
    }

    return msg;
}
