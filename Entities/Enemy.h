#ifndef ENEMY_H
#define ENEMY_H

#include <stdlib.h>
#include <vector>
#include <string>

#include "Entity.h"



class Enemy : public Entity{

private:
	std::string name;
   // int hp;
    //int hpMax;
    //int level;
    int damageMin;
    int damageMax;
    float dropChance;
    int defence;
    int accuracy;

public:
    Enemy(int level, int faction);
    virtual ~Enemy();

//    inline bool isAlive() { return this->hp > 0;}
    std::string getAsString() const;
	int takeDamage(int damage);

	inline int getLevel() const { return this->m_level; }
  //  inline int getDamage() const { return this->damageMin + rand() % ((this->damageMax + 1) - this->damageMin); }
	inline int getDamageMin() const { return this->damageMin; }
	inline int getDamageMax() const { return this->damageMax; }
	int getExp() const;
	//inline int getHp() const { return this->hp; }
	//inline int getHpMax() const { return this->hpMax; }
	///inline int getDefence() const { return this->defence; }
	inline int getAccuracy() const { return this->accuracy; }
	inline std::string getName() { return this->name; }

	static vector<string> enemyNames;
	static void initNames();
};

#endif // ENEMY_H
