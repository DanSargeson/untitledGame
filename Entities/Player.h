#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
#include "Entity.h"
#include "GUI.h"

using namespace std;

class Player : public Entity{
private:

	Weapon weapon;
//	shared_ptr<Item> activeWeapon;
//	shared_ptr<Item> activeHead;
//	shared_ptr<Item> activeChest;
//	shared_ptr<Item> activeArms;
//	shared_ptr<Item> activeLegs;
	Armour armourHead;
	Armour armourChest;
	Armour armourArms;
	Armour armourLegs;
	int gold;
	int distanceTravelled;

    vector<shared_ptr<Entity>> followers;

    int dayChurhBsainEmptied;
    int churchBasinLevel;

	string name;
	int level;
	int corruption;

	int daysPassed;
	std::shared_ptr<WorldTimer> worldTimer;

public:
    Player();
    Player(string name, int dt);
    Player(string n, int dt, int g, int lvl, int exp, int vit, int str, int dex, int agi,
                     int intel, int charis, int luck, int hp,  int corr, int attriPoints = 0, bool reset = true);
    virtual ~Player();


    /* SAVE AREA SPECIFIC DATA, THIS SHOULD DEFINTELY BE SPLIT AT SOME POINT... */

    inline void setChurchBasinLevels(int level, int day) { churchBasinLevel = level; dayChurhBsainEmptied = day; }
    inline int getBasinLevel() { return churchBasinLevel; }
    inline int getDayBasinEmptied() { return dayChurhBsainEmptied; }

    //Functions
    void initialise(string name);
    std::string printPlayerDetails();
    string getStatsAsString() const;
    string getStatsAttributeScreen();
	string getInvAsString();
	void loadBonuses();
//	std::string getInvItemAsString(int choice);
//	std::string getArmAsString(int choice);
//	std::string getWepAsString(int choice);
//	SDL_Color getItemColour(int choice);
	string getInvAsStringSave();
	std::vector<std::string> getWepAsVec();
	std::vector<std::string> getArmAsVec();
    //void levelUp();
    //void updateStats(bool reset = true);
    int getAttributePoints();
	void addStat(int stat, int value);
	int takeDamage(int damage);
	void equipItem(int index);
	void equipWeapon(int index);
	void equipArmour(int index);
///	int getDefenceTotal();
//	int getDamage();
	//int getMinDamageWithWeapon();
	//int getMaxDamageWithWeapon();
	string getEquippedWeapon();
	string getEquippedArmour();
	inline int getInvSize() { return this->inv->smrtSize(); }
	//inline void setInv(Inventory inv) { this->inv = inv; }
	inline void setWeapon(shared_ptr<Weapon> w) { this->activeWeapon = w; }
	inline void setArmourHead(shared_ptr<Armour> a) { this->activeHead = a; }
	inline void setArmourChest(shared_ptr<Armour> a) { this->activeChest = a; }
	inline void setArmourArms(shared_ptr<Armour> a) { this->activeArms = a; }
	inline void setArmourLegs(shared_ptr<Armour> a) { this->activeLegs = a; }
	inline void increaseCorruption() { corruption++; }

	std::shared_ptr<Entity> getActiveFollower() { if (!followers.empty()) { return followers[0]; } else return nullptr; }

	//int getBonus(int type);

	inline void increaseDaysPassed() { daysPassed++; }
	inline std::shared_ptr<WorldTimer> getWorldTimer() { return worldTimer; }
	inline int getDaysPassed() { return daysPassed; }
    inline void createWorldTimer() { worldTimer = std::make_shared<WorldTimer>(); }
    inline void setDaysPassed(int i) { daysPassed = i; }

	std::string printFollowers();
	std::vector<std::shared_ptr<GUI::Text>> getFollowersAsStrVec();
	std::string getFollowersStrSave();

	std::vector<std::shared_ptr<Entity>> getFollowers() { return followers; }
	void addFollower(std::shared_ptr<Entity> npc){ followers.push_back(npc); loadBonuses(); }
    void removeBonuses(int type/*, int level*/);
	void removeFollower(std::shared_ptr<Entity> npc = nullptr){

		if(!followers.empty()) {

        std::cout << "SIZE1: " << std::to_string(followers.size()) << std::endl;
		if (npc == nullptr) {

			removeBonuses(followers[0]->getType());
			followers.erase(followers.begin());

			return;
		}
		else {

			removeBonuses(npc->getType()/*, npc->getLevel()*/);
			vector<shared_ptr<Entity>>::iterator smrtDEl = find(followers.begin(), followers.end(), npc);
		    followers.erase(smrtDEl);
	        std::cout << "SIZE2: " << std::to_string(followers.size()) << std::endl;
		}

		}
	}

	void swapActiveFollower(int choice){

          auto i = followers.begin();
          std::iter_swap(i, i + choice);
	}


	void setAttributePoints(int p);
	void increaseAttribute(int i);
	void decreaseAttribute(int i);

	void increaseSkill(int i);
	std::string saveAttributes();
	void setAttributes(int v, int s, int d, int a, int i, int c, int l);

//Accessors
    inline const string& getName() const { return this->name;}
//    const int& getLevel() const;
//    inline const int& getDistanceTravelled() const { return this->distanceTravelled;}
//    inline const int& getExp() const { return this->exp;}
//    inline const int& getExpNext() const { return this->expNext;}
//    inline const int& getHP() const { return this->hp;}
//    inline const int& getHpMax() const { return this->hpMax;}
//    inline const int& getStamina() const { return this->stamina;}
//	//inline const int& getDamage() const { return rand() % this->damageMax + this->damageMin; }
//	inline const int& getDamageMax() const { return this->damageMax;}
//    inline const int& getDamageMin() const { return this->damageMin;}
//    inline const int& getDefence() const { return this->defence;}
//    inline const int& getAccuracy() const { return this->accuracy;}
//	inline const int& getStatPoints() const { return this->statPoints; }
	inline const int& getGold() const { return this->gold; }
//	inline const bool isAlive() { return this->hp > 0;  }
	inline const int& getCorruption() { return corruption; }


    //modifiers
    inline void setDistanceTravelled(const int &distance) { this->distanceTravelled += distance; }
    inline void travel() { this->distanceTravelled++; }
//    inline void setExp(int exp) { this->exp += exp;}
	inline void setGold(int gold) { this->gold = gold; }
	inline void gainGold(int gold) { this->gold += gold; }
	void loadFactions(int black, int white, int red, int orange, int yellow, int green, int blue, int indigo, int violet);
//	inline void resetHP() { this->hp = this->hpMax; }


};

#endif // Player_H

