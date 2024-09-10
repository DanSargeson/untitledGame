#include "Enemy.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"
#include <random>

vector<string> Enemy::enemyNames;

void Enemy::initNames() {
	Enemy::enemyNames.push_back("Goblin");
	Enemy::enemyNames.push_back("Warlock");
	Enemy::enemyNames.push_back("Wolf");
	Enemy::enemyNames.push_back("Ghost");
	Enemy::enemyNames.push_back("Skeleton");
	Enemy::enemyNames.push_back("Rat");
	Enemy::enemyNames.push_back("Harpy");
	Enemy::enemyNames.push_back("Gremlin");
	Enemy::enemyNames.push_back("Berserker");
}


Enemy::Enemy(int lvl, int faction) : Entity(){
    initNames();
    //this->level = rand() % (level - 2);
    m_level = lvl;

//    createFactionComponent();

    unsigned seed;
    std::default_random_engine generator;
    seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
     generator.seed(seed);
//    std::uniform_int_distribution<int> numEnemiesDistribution(lvl-2, lvl);
//     this->level = numEnemiesDistribution(generator);
     if(m_level <= 0){

        m_level = 1;
     }

  //  this->createAttributeComponent(this->level, true, true);
    //attributeComponent->updateLevel();
   // createSkillComponent();
    //updateStats(true);
  //  createAttackComponent();

        this->faction = faction;
        this->name += Enemy::enemyNames[rand() % Enemy::enemyNames.size()];

    int player_lvl = StateData::GetInstance()->getActiveCharacter()->getLevel();

    if(player_lvl > 1){

        for(int i = 0; i < player_lvl; i++){

            spawnGear();
        }
    }
}

Enemy::~Enemy(){

 //   attributeComponent.re
 //removeComponent(attributeComponent);
 //removeComponent(skillComponent);
}

int Enemy::getExp() const{

    return attributeComponent->getEXPNext();
}

string Enemy::getAsString() const{
    return name + " Level: " + to_string(this->m_level) + "\n" +
           "HP: " + to_string(this->attributeComponent->getHP()) + "/" + to_string(this->attributeComponent->getHPMax()) + "\n" +
           "Damage: " + to_string(this->damageMin) + " - " + to_string(this->damageMax) + "\n" +
           "Defence: " + to_string(this->defence) + "\n" +
           "Accuracy: " + to_string(this->accuracy) + "\n" +
           "Drop Chance: " + to_string(this->dropChance) + "\n" +
           "EXP Next: " + std::to_string(attributeComponent->getEXPNext()) + "\n";
}

int Enemy::takeDamage(int damage) {
	damage -= this->defence;

	if(damage <= 0){
        damage = 1;
	}
    int hp = attributeComponent->getHP();
	hp -= damage;
	if (hp <= 0) {
		hp = 0;
	}

	return damage;
}
