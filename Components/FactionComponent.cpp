#include "stdafx.h"
#include "FactionComponent.h"

FactionComponent::FactionComponent(std::shared_ptr<Entity> owner) : Component(owner){

	mFactions.push_back(Faction(FACTIONS::BLACK));
	mFactions.push_back(Faction(FACTIONS::WHITE));
	mFactions.push_back(Faction(FACTIONS::RED));
	mFactions.push_back(Faction(FACTIONS::ORANGE));
	mFactions.push_back(Faction(FACTIONS::YELLOW));
	mFactions.push_back(Faction(FACTIONS::GREEN));
	mFactions.push_back(Faction(FACTIONS::BLUE));
	mFactions.push_back(Faction(FACTIONS::INDIGO));
	mFactions.push_back(Faction(FACTIONS::VIOLET));
}

FactionComponent::~FactionComponent(){

}

int FactionComponent::getReputation(unsigned int faction){

	try {


		if (faction < 0 || faction >= mFactions.size()) {

			throw std::runtime_error("Error::FACTIONCOMPONENT::GetReputation - faction not found: " + std::to_string(faction));
		}
		else {

			return mFactions[faction].getRepLevel();
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

	return 0;
}


void FactionComponent::calculateReputation(int faction) {


	unsigned seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::uniform_int_distribution<int> repDist(REPUTATION::SUSPICIOUS_LOW, REPUTATION::SUSPICIOUS_HIGH);

	int rep = repDist(generator);

	try {


		switch (faction) {

		case FACTIONS::BLUE:
			//this->
			mFactions[FACTIONS::BLUE].setLevel(REPUTATION::REVERED);
			break;

		case FACTIONS::BLACK:

			break;

		case FACTIONS::ORANGE:

			break;

		case FACTIONS::GREEN:

			break;

		case FACTIONS::YELLOW:

			//GREEN ARE SUSPICIOUS AGAINST BLUE AND slightly against RED UNTIL THE PLAYER INTERVENES

			mFactions[FACTIONS::GREEN].setLevel(REPUTATION::REVERED);
			mFactions[FACTIONS::BLUE].setLevel(rep);
			mFactions[FACTIONS::RED].setLevel(rep);

			break;

		case FACTIONS::INDIGO:

			break;

		case FACTIONS::RED:

			break;

		case FACTIONS::WHITE:

			mFactions[FACTIONS::WHITE].setLevel(REPUTATION::REVERED);
			mFactions[FACTIONS::BLACK].setLevel(REPUTATION::HATED_LOW);
			break;

		default:

			throw std::runtime_error("ERROR: FACTION COMPONENT - LINE 82");
			break;
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

void FactionComponent::changeRep(int faction, int value){

	mFactions[faction].setLevel(value);
}

void FactionComponent::loseRep(int faction, int rep){

	mFactions[faction].loseRep(rep);
}

void FactionComponent::gainRep(int faction, int rep) {

	mFactions[faction].gainRep(rep);

        ///RED HATE BLUE HATE GREEN HATE RED
        ///if red > 255
        /// GREEN will be lowered
        /// /RED + GREEN == YELLOW (peacemakers)

        ///if BLUE > 255
        /// red will be lowered
        /// / red + blue == BLUE (peacemakers)

        ///If GREEN >  255
        /// blue will be lowered
        /// / green + blue == AQUA (peacemakers)

//        float lose = static_cast<float>(rep) / 4;
//
//        lose = std::round(lose);
//
//        if(lose <= 0){
//
//            lose = 1;
//        }
//
//
//	switch(faction){
//
//    case FACTIONS::RED:     ///RED FACTION HATE BLUE AND ARE SUSPICIOUS OF GREEN
//        mFactions[FACTIONS::GREEN].loseRep(lose);
//        break;
//
//    case FACTIONS::BLUE:
//        mFactions[FACTIONS::RED].loseRep(lose);
//        break;
//
//    case FACTIONS::GREEN:
//        mFactions[FACTIONS::BLUE].loseRep(lose);
//        break;
//	}
}

std::string FactionComponent::getFactionName(int faction) {

	return mFactions[faction].getName();
}

std::string FactionComponent::getFactionsStr() {

	std::string msg;



	for (int i = 0; i < TOTAL_FACTIONS; i++) {

		msg += mFactions[i].getName() + ":   ";

		if (mFactions[i].getRepLevel() <= REPUTATION::HATED_HIGH) {

			msg += "HATED";
		}
		else if (mFactions[i].getRepLevel() <= REPUTATION::DISLIKED_HIGH) {

			msg += "DISLIKED";
		}
		else if (mFactions[i].getRepLevel() <= REPUTATION::SUSPICIOUS_HIGH) {

			msg += "SUSPICIOUS";
		}
		else if (mFactions[i].getRepLevel() <= REPUTATION::NEUTRAL_HIGH) {

			msg += "NEUTRAL";
		}
		else if (mFactions[i].getRepLevel() <= REPUTATION::AMIABLE_HIGH) {

			msg += "AMIABLE";
		}
		else if (mFactions[i].getRepLevel() <= REPUTATION::LIKED_HIGH) {

			msg += "LIKED";
		}
		else if (mFactions[i].getRepLevel() >= REPUTATION::REVERED) {

			msg += "REVERED";
		}

		int rep = mFactions[i].getRepLevel() - 100;
//		if(rep < -255){
//
//            rep = -255;
//		}
//		if(rep > 255){
//
//            rep = 255;
//		}

		msg += "  (" + std::to_string(rep) + ")\n";
	}

	return msg;
}

std::string FactionComponent::getFactionsStrSave() {

	std::string deets = "";

	for (int i = 0; i < FACTIONS::TOTAL_FACTIONS; i++) {

		deets += std::to_string(mFactions[i].getRepLevel()) + " ";
	}

	return deets;
}

void FactionComponent::loadFactions(int black, int white, int red, int orange, int yellow, int green, int blue, int indigo, int violet){

	mFactions[FACTIONS::BLACK].setLevel(black);
	mFactions[FACTIONS::WHITE].setLevel(white);
	mFactions[FACTIONS::RED].setLevel(red);
	mFactions[FACTIONS::ORANGE].setLevel(orange);
	mFactions[FACTIONS::YELLOW].setLevel(yellow);
	mFactions[FACTIONS::GREEN].setLevel(green);
	mFactions[FACTIONS::BLUE].setLevel(blue);
	mFactions[FACTIONS::INDIGO].setLevel(indigo);
	mFactions[FACTIONS::VIOLET].setLevel(violet);
}
