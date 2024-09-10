#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

class AttributeComponent;
class SkillComponent;
class FactionComponent;
class DialogueComponent;
class AttackComponent;
class QuestComponent;
//DEFENCE COMPONENT HERE
class Item;
#include "Inventory.h"

class Entity : public enable_shared_from_this<Entity>{

private:

	void InitVariables();

protected:


	//EQUIPPED ITEMS
	std::shared_ptr<class Weapon> activeWeapon;
	std::shared_ptr<class Armour> activeHead;
	std::shared_ptr<class Armour> activeChest;
	std::shared_ptr<Armour> activeArms;
	std::shared_ptr<Armour> activeLegs;
	std::shared_ptr<Armour> activeTool;

	std::shared_ptr<AttributeComponent> attributeComponent;
	std::shared_ptr<SkillComponent> skillComponent;
	std::shared_ptr<FactionComponent> factionComponent;
	std::shared_ptr<DialogueComponent> dialogueComponent;
	std::shared_ptr<AttackComponent> attackComponent;
	std::shared_ptr<QuestComponent> questComponent;

	int faction;

	std::vector<std::shared_ptr<class Component>> mComponents;
	std::shared_ptr<class Inventory> inv;

	std::string m_name;
    int m_type;
	int m_level;

	static std::vector<std::string> entityNames;

public:

	Entity();
	virtual ~Entity();

	//Component Functions

	//Attribute functions

	void initNames();

	void loseHP(int hp);
	void gainHP(int hp);
	void loseXP(float xp);
	void gainXP(float xp = -1);

	void loseRep(int faction, int rep);
	void gainRep(int faction, int rep);

	int getSkill(int skill);
	int getFaction(int faction);
	int getAttribute(int attribute);
	int checkDurability();
	float getAttributeFloat(int attribute);

	int getExp();
	int getExpNext();

	int getType(){ return m_type; }

	std::shared_ptr<Entity> getPtr() {

		return shared_from_this();
	}

	void setExp(int exp);

	void levelUp();
	void updateStats(bool reset = true);

	std::string getStatsAttributeScreen();

	SDL_Color getItemColour(int item);
	SDL_Color getWepItemColour(int item);
	SDL_Color getArmItemColour(int item);

	void createComponents();

	void assignRandomAttributes(int level, bool npc = false);

	int getBonus(int type);

	int getLevel();
	void setLevel(int level){ m_level = level; }

	int getHP();
	int getHPMax();

	void loseDurability();

	bool fullHealth();


	//bool checkEntityCollision(Entity* entity);

	std::vector<std::string> sortWepByStr() { return inv->sortWepByStr(); }

	std::string getFactionStr();
	std::string getFactionStrSave();
	std::string getFactionName(int faction);
	int getSavedFaction() { return this->faction; }

	std::string getInvItemAsString(int i);
	std::string getArmAsString(int choice);
	std::string getWepAsString(int choice);
	std::vector<std::string> getInvAsVec();
	std::shared_ptr<Inventory> getInv();

	inline void sortItems() { inv->sortWepByStr(); }

	std::string getSavedFactionName();

	void calculateSkills();


	bool skillCheck(std::shared_ptr<Entity> checkAgainst, int skill1, int skill2);

///	void updateStats(bool s);

	inline shared_ptr<Item> findItem(int index) { return this->inv->findItemSmart(index); }
	inline void removeItem(shared_ptr<Item> w) { this->inv->removeItemVectorSmart(w); }
	inline void addItem(shared_ptr<Item>item) { this->inv->addItemVectorSmart(item); }
	inline shared_ptr<Item> findWeapon(int index){ return inv->findWeaponSmart(index); }
	inline shared_ptr<Item> findArmour(int index){ return inv->findArmourSmart(index); }
//	inline void getInv() { this->inv.debugVector(); }

	//std::vector<std::string> getDialogueOptions();

	void setCharacterName(std::string name);

	std::string getItemString(int index);

	int getRep(int faction);

	bool isAlive();

	void setHP(int l);

//	virtual int getCurrentMapID() = 0;
//	virtual void setMapID(int id);

	void createAttributeComponent(const unsigned level, const bool reset, bool enemy = false);
	void createSkillComponent();
	void createFactionComponent();
	void createDialogueComponent();
	void createAttackComponent();
	void createQuestComponent();

    std::shared_ptr<AttributeComponent> getAttributeComponent() { return this->attributeComponent; }
	std::shared_ptr<SkillComponent> getSkillComponent() { return skillComponent; };
	std::shared_ptr<FactionComponent> getFactionComponent() { return factionComponent; }
	std::shared_ptr<DialogueComponent> getDialogueComponent() { return dialogueComponent; };
	std::shared_ptr<AttackComponent> getAttackComponent() { return attackComponent; }


	std::string displaySkills();

	void resetHP();

	void equipWeapon(int index);
	void equipArmour(int index);
	void spawnGear();

    std::string getName() { return m_name; }

	int getDamage();
	int getDefence();

	int getMaxDefenceWithArmour();
	int getMinDefenceWithArmour();
	int getMaxDamageWithWeapon();
	int getMinDamageWithWeapon();

	//const virtual sf::Vector2f& getPosition() const;
	float getPositionXSave();
	float getPositionYSave();
	//const virtual sf::Vector2f getCentre() const;
	//const virtual sf::Vector2i getGridPosition(const int gridSizeI) const;
	//const virtual sf::FloatRect getGlobalBounds() const;
	//const virtual sf::FloatRect getNextPositionBounds(const float& dt) const;

	/*TODO - Refactor at some point*/
	//void createSpriteFromSheet(sf::Texture* texture, float startX, float startY, float width, float height);


	//functions

	//virtual void setPosition(const float x, const float y);
	//virtual void move(const float x, const float y, const float& dt);
	//sf::Vector2f getVelocity();
	//sf::Vector2f getPreviousVelocity();
	//virtual void stopVelocity();
	//virtual void stopVelocityY();
	//virtual void stopVelocityX();



	float calculateDefence();

	/*
		INVETORY FUNCTIONS
	*/

	std::shared_ptr<Item> getItem(int index);
	void removeItem(int index);

	///inline void addItem(shared_ptr<Item>item) { this->inv.addItemVectorSmart(item); }

	void addComponent(std::shared_ptr<class Component> comp);
	void removeComponent(std::shared_ptr<class Component> comp);
	void updateComponents();

	bool getDialogueActive();
	void setDialogueActive(bool n);
	void setDialogueText(std::string);
	void renderDialogue();

	//virtual int getDirection() = 0;

	std::shared_ptr<Weapon> getActiveWeapon();

	std::shared_ptr<Armour> getActiveHead();
	std::shared_ptr<Armour> getActiveChest();
	std::shared_ptr<Armour> getActiveArms();
	std::shared_ptr<Armour> getActiveLegs();

	virtual void update();
	virtual void render();
};

#endif

