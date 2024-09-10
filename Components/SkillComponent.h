#ifndef SKILLS_H
#define SKILLS_H

#include "Component.h"

enum SKILLS {

	MELEE = 0,
	CRIT,
	DEFENCE,
	ACCURACY,
	MAGIC,
	STEALTH,
	PICKPOCKET,
	PERSUASION,
	PERCEPTION,
	BARTER,
	DODGE
};

class SkillComponent : public Component{

public:

	SkillComponent(std::shared_ptr<Entity> owner);
	~SkillComponent();

	int getSkill(const unsigned int skill);
	void gainExp(const unsigned int skill, const int xp);

	void increaseSkill(int skill);
	void loadSkills(int skill, int value);

	std::string getSkillName(int skill);

	void assignRandomSkills(int level);
	void calculateSkills(std::shared_ptr<class AttributeComponent> ac);

	std::string displaySkills();

	///int calculateSkillsNEW(std::string attribute_name, int currAttribute);

private:

	class Skill {

	private:
		int skillType;
		int level;
		int levelCap;
		float exp;
		float expNext;

	public:
		Skill(int type) {

			skillType = type;
			level = 1;
			level = 100;
			exp = 0;
			expNext = 100;
		}

		~Skill() {}

		//Accessors
		const int& getType() { return skillType; }
		const int& getLevel() { return level; }
		const float& getExp() { return exp; }
		const float& getExpNext() { return expNext; }
		std::string getTypeAsString() {

            switch(this->skillType){

                case SKILLS::ACCURACY:
                    return "Accuracy";
                    break;

                case SKILLS::DEFENCE:
                    return "Defence";
                    break;

                case SKILLS::PICKPOCKET:
                    return "Pickpocket";
                    break;

                case SKILLS::MAGIC:
                    return "Magic";
                    break;

                case SKILLS::MELEE:
                    return "Melee";
                    break;

                case SKILLS::PERCEPTION:
                    return "Perception";
                    break;

                case SKILLS::PERSUASION:
                    return "Persuasion";
                    break;

                case SKILLS::BARTER:
                    return "Barter";
                    break;

                case SKILLS::STEALTH:
                    return "Stealth";
                    break;

                case SKILLS::DODGE:
                    return "Dodge";
                    break;

                case SKILLS::CRIT:
                    return "Crit Rate";
                    break;

                default:
                    return "Error: Could not get skill type as string";
                    break;

            }


		 }

		//Modifiers
		void setLevel(int lvl) { level = lvl; }
		void setLevelCap(int cap) { levelCap = cap; }

		void gainExp(const int xp) {

			exp += xp;
			updateLevel();
		}

		void loseExp(const int xp) {

			exp -= xp;

			if (exp < 0) {

				exp = 0;
			}
		}

		void updateLevel() {

			if (level < levelCap) {

				while (exp < expNext) {

					if (level < levelCap) {

						level++;
						exp = 0.f;
						expNext = static_cast<float>(std::pow(level, 2)) + static_cast<float>(level * 10) + static_cast<float>(level * 2);
					}
				}
			}
		}

		void update() {}
	};

	std::vector<Skill> mSkills;
};

#endif

