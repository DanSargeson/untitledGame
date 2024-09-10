#ifndef FACTIONS_H
#define FACTIONS_H

#include "Component.h"


///RED
///BLUE
///GREEN

///SECONDARY == CYAN, MAGENTA, YELLOW

enum FACTIONS {

	BLACK = 0,
	WHITE,
	RED,    ///RED STILL RED
	ORANGE,   ///BLUE NOW ORANGE
	YELLOW,  ///GREEN NOW YELLOW
	GREEN,   ///AQUA NOW GREEN
	BLUE,    ///MAGENTA NOW BLUE
	INDIGO, ///YELLOW NOW INDIGO
	VIOLET, ///VIOLET NEW
	TOTAL_FACTIONS
};


//HATED = Attack on sight
//DISLIKED = People are dicks to you, Merchants won't sell to you
//SUSPICIOUS = Mostly same as neutral, some will be dicks, merchanst still sell but increase their price/High alert for theft
//NEUTRAL - People will be civil but not too friendly, Merchants are on normal alert and will sell for slightly increased prices
//AMIABLE - Most are friendly, Merchants sell for normal prices and normal alert levels, some people open up
//LIKED - ALL are friendly, merchants may give a slight discount, relaxed alert levels, can access better dialogue
//REVERED - Merchants will give some free items + big discount, low alert levels, everyone is friendly, can access full town dialogues
enum REPUTATION {

	HATED_LOW = 0,
	HATED_HIGH = 19,
	DISLIKED_LOW = 20,
	DISLIKED_HIGH = 39,
	SUSPICIOUS_LOW = 40,
	SUSPICIOUS_HIGH = 79,
	NEUTRAL_LOW = 80,
	NEUTRAL = 100,
	NEUTRAL_HIGH = 119,
	AMIABLE_LOW = 120,
	AMIABLE_HIGH = 159,
	LIKED_LOW = 160,
	LIKED_HIGH = 179,
	REVERED = 180
};

class FactionComponent : public Component{

public:

	FactionComponent(std::shared_ptr<Entity> owner);
	virtual ~FactionComponent();


	int getReputation(unsigned int faction);
	void calculateReputation(int faction);

	void changeRep(int faction, int value);
	void loseRep(int faction, int value);
	void gainRep(int faction, int value);

	std::string getFactionName(int faction);
	std::string getFactionsStr();
	std::string getFactionsStrSave();

	void loadFactions(int black, int white, int red, int orange, int yellow, int green, int blue, int inidigo, int violet);

private:

	class Faction {

	private:
		std::string name;
		int faction;
		int repLevel;
		int levelCap;
		int repChange;

	public:

		Faction(int type) {

			faction = type;
			repLevel = 100;
			levelCap = 355;
			repChange = 0;

			setName(faction);
		}

		~Faction() { }

		//Getters
		int getRepLevel() { return repLevel; }
		std::string getName() { return name; }


		//setters
		void gainRep(int rep) { if(rep < 355){repLevel += rep;} }
		void loseRep(int rep) { if(rep > -355){repLevel -= rep;} }

		void setLevel(int level) { repLevel = level; }
		void setName(int faction) {

			switch (faction) {

			case FACTIONS::INDIGO:
				this->name = "Indigo";
				break;

			case FACTIONS::BLACK:
				this->name = "Black";
				break;

			case FACTIONS::BLUE:
				this->name = "Blue";
				break;

			case FACTIONS::ORANGE:
				this->name = "Orange";
				break;

			case FACTIONS::YELLOW:
				this->name = "Yellow";
				break;

			case FACTIONS::GREEN:
				this->name = "Green";
				break;

			case FACTIONS::RED:
				this->name = "Red";
				break;

			case FACTIONS::WHITE:
				this->name = "White";
				break;

            case FACTIONS::VIOLET:
                name = "Violet";
                break;

			default:
			    name = "Error in faction names";
				break;
			}
		}
	};
	//END CLASS

	std::vector<Faction> mFactions;
};

#endif

