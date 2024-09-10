#ifndef NPC_H
#define NPC_H


/*

		Start Game, instant death, corruption starts to take over. Every death increases corruption

		Yellow appears and explains the mechanics of death.

		Choose path Red or Blue

		Red = fire magic
		Blue = Ice magic

		Green = Healing magic

		BLUE EXPLANATION:
		Balance needs to be maintained they are the control to reds wild nature... They are peaceful but strong. Rely on the old world
		and want to preserve the way things are hence ice.


		RED EXPLANATION:
		Blue have trapped red and won't allow them to uncover the true power of elements/colours. Red desires to rebuild a new world.
		Red needs to burn down this world to create a new world. Hence fire.


		At this point both red and blue will ask to swap sides, depending which way the player went.


		AT THIS POINT THE PLAYER CHOOSES THEIR PATH:

		RED PATH:
			destroy blue they discover water, GET GREEN create Earth.

		BLUE PATH:
			GET GREEN, create earth, contain red.



		AT THIS POINT THE STORY SPLITS INTO 3 - GREEN OFFER A THIRD SOLUTION:

		RED PATH: - BAD END
			DESTROY BLUE, RED + GREEN = YELLOW, SUN IS TOO BRIGHT AND SCORCHES THE EARTH

		BLUE PATH: - BAD END
			CONTAIN RED, BLUE +  GREEN = AQUA, PLANET DROWNS AND WILL EVENTUALLY BECOME PURE ICE


		GREEN PATH:
			BROKER A DEAL, RED + BLUE = PURPLE accesses AIR. GREEN+PURPLE = BLACK.



		BLACK WAS RIGHT ALL ALONG......



		DeATH:
		if fully corrupted white will visit and inform the player that they can remove the corruption for a price...

		WHITE = DEATH
		BLACK = REBIRTH
*/

#include "Entity.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Armour.h"
#include "Engine.h"

enum NPC_TYPE {

	ALCHEMIST,
	BLACKSMITH,
	COOK,
	SCOUT,
	LIBRARIAN,
	INNKEEPER,
	BARD,
	TOTAL_TYPES
};

class NPC : public Entity{

private:

	static int characterID;
	///int type;
	int faction;
	bool questGiver;
	bool companion;
	std::string dialogue;
	std::string name;
	int gold;

	//Inventory inv;

	unsigned seed;
	std::default_random_engine generator;

	std::string textFileName;

	void generateID();



	//std::unique_ptr<Texture> bg;

public:
	NPC(int level, int faction=-1);
	NPC(int type, int level, int faction);
	NPC(int faction, bool questGiver, std::string dialgoue);
	virtual ~NPC();

	std::vector<std::string> getDialogueOptions();

	void initBackground(SDL_Renderer* r);

	virtual std::string getFactionStr();


	//FUNCTIONS
	int getFaction();
	bool givesQuest();

	int getType();
	void setType(int t);
	std::string getName();
	void setName(std::string name);

	void setTextureRect(SDL_Rect r);

	int getInvCount();

	//std::string getItemString(int index);

	void setDialogue(int id);

	bool quitDialogue();

	void setCharm(bool x);

	bool charm();

	bool shop();

	void talk(int choice);

	std::string getDialogue();

	int getDialogueID();

	void createInventory();

	//virtual int getCurrentMapID();

	void setDialogueChoice(int choice);
	std::shared_ptr<Item> getItem(int index);

	void removeItem(int index);

	int getGold();
	std::string getInvAsString();

	virtual void update();
	virtual void render();
};

#endif
