#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(std::shared_ptr<Entity> owner, unsigned level, bool reset, bool enemy) : Component(owner){

    baseEXP = 50.f;
	mLevel = level;
	mExp = 0;
	mExpNext = (baseEXP * mLevel) * 5;
	mAttributePoints = 0;
	mHasLevelled = false;

	for (int i = 0; i < TOTAL_ATTRIBUTES; i++) {

		mAttributes.push_back(1);
		bonusAttributes.push_back(0);
	}

	if (enemy) {

        baseEXP = 5.f;
        mExpNext = (baseEXP * mLevel) * 5;
		unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
		std::default_random_engine generator(seed);
		std::uniform_int_distribution<int> pointDistribution(0, 5);



		// Define the weights for each attribute
std::vector<int> attributeWeights = {4, 4, 3, 1, 3, 1}; // Weights for VITALITY, STRENGTH, DEXTERITY, INTELLIGENCE, LUCK, AGILITY

// Normalize weights to calculate probabilities
int totalWeight = std::accumulate(attributeWeights.begin(), attributeWeights.end(), 0);
std::vector<double> probabilities;
for (int weight : attributeWeights) {
    probabilities.push_back(static_cast<double>(weight) / totalWeight);
}

// Generate a random attribute based on weights
std::discrete_distribution<int> weightedDistribution(attributeWeights.begin(), attributeWeights.end());
int roll = weightedDistribution(generator);




        ///int point = 3;
        ///*EASY*/
		int point = 0;
		int counter = 0;
		if(mLevel > 5){ ///HARD is level > 1
            point += (mLevel - 3); /// += level
		}

		if(point < 0){

            point = 0;  /// == 3 if hard mode is true   ./.... If corruption > 10 make the white light come and remind thr player that they shouldn't be dying, do they want to play on easy?
		}

		for (int i = 0; i < point; i++) {

			int roll = weightedDistribution(generator);

			switch (roll) {

			case 0:
				mAttributes[ATTRIBUTE::VITALITY] += 1;      ///USED FOR DEFENCE
				break;

			case 1:
				mAttributes[ATTRIBUTE::STRENGTH] += 1;      ///USED FOR MELEE
				break;

			case 2:
				mAttributes[ATTRIBUTE::DEXTERITY] += 1;     ///USED FOR ACCURACY
				break;

			case 3:
				mAttributes[ATTRIBUTE::INTELLIGENCE] += 1;       ///WILL EVENTUALLY BE USED FOR MAGIC
				break;

			case 4:
				mAttributes[ATTRIBUTE::LUCK] += 1;          ///USED TO BOOST EVERYTHING SLIGHTLY
				break;

            case 5:
                mAttributes[ATTRIBUTE::AGILITY] +=1;

			default:
				break;
			}
		}

//		std::cout << "Enemy level: " << mLevel << "\n";
//		std::cout << "Enemy points: " << point << "\n";
//		std::cout << "Enemy vit: " << mAttributes[ATTRIBUTE::VITALITY] << "\n";
//		std::cout << "Enemy str: " << mAttributes[ATTRIBUTE::STRENGTH] << "\n";
//		std::cout << "Enemy dex: " << mAttributes[ATTRIBUTE::DEXTERITY] << "\n";
//		std::cout << "Enemy agi: " << mAttributes[ATTRIBUTE::AGILITY] << "\n";
//		std::cout << "Enemy cha: " << mAttributes[ATTRIBUTE::CHARISMA] << "\n";
//		std::cout << "Enemy int: " << mAttributes[ATTRIBUTE::INTELLIGENCE] << "\n";
//		std::cout << "Enemy luck: " << mAttributes[ATTRIBUTE::LUCK] << "\n";
//		std::cout << "EXP NEXT: " << std::to_string(mExpNext) << "\n\n";
	}

	//updateLevel();
	updateStats(reset);
}

AttributeComponent::~AttributeComponent(){

    mExp = 0;
}

void AttributeComponent::increaseAttribute(int attr){

	switch (attr) {

	case ATTRIBUTE::AGILITY:
		mAttributes[AGILITY] += 1;
		break;

	case ATTRIBUTE::CHARISMA:
		mAttributes[CHARISMA] += 1;
		break;

	case ATTRIBUTE::DEXTERITY:
		mAttributes[DEXTERITY] += 1;
		break;

	case ATTRIBUTE::INTELLIGENCE:
		mAttributes[INTELLIGENCE] += 1;
		break;

	case ATTRIBUTE::LUCK:
		mAttributes[LUCK] += 1;
		break;

	case ATTRIBUTE::STRENGTH:
		mAttributes[STRENGTH] += 1;
		break;

	case ATTRIBUTE::VITALITY:
		mAttributes[VITALITY] += 1;
		break;

	default:
		break;
	}
}

void AttributeComponent::decreaseAttribute(int attr){

    ///Never used, but could be
	switch (attr) {

	case ATTRIBUTE::AGILITY:
		mAttributes[AGILITY] -= 1;
		break;

	case ATTRIBUTE::CHARISMA:
		mAttributes[CHARISMA] -= 1;
		break;

	case ATTRIBUTE::DEXTERITY:
		mAttributes[DEXTERITY] -= 1;
		break;

	case ATTRIBUTE::INTELLIGENCE:
		mAttributes[INTELLIGENCE] -= 1;
		break;

	case ATTRIBUTE::LUCK:
		mAttributes[LUCK] -= 1;
		break;

	case ATTRIBUTE::STRENGTH:
		mAttributes[STRENGTH] -= 1;
		break;

	case ATTRIBUTE::VITALITY:
		mAttributes[VITALITY] -= 1;
		break;

	default:
		break;
	}

	for (int i = 0; i < TOTAL_ATTRIBUTES; i++) {

		if (mAttributes[i] <= 0) {

			mAttributes[i] = 0;
		}
	}
}

void AttributeComponent::loadAttribute(int level, float xp, int hp, int vit, int str, int dex, int agi, int intel, int charis, int luck){

	mLevel = level;
	mExp = xp;
	mAttributes[ATTRIBUTE::VITALITY] = vit;
	mAttributes[STRENGTH] = str;
	mAttributes[DEXTERITY] = dex;
	mAttributes[AGILITY] = agi;
	mAttributes[INTELLIGENCE] = intel;
	mAttributes[CHARISMA] = charis;
	mAttributes[LUCK] = luck;

	updateLevel();
	updateStats(true);
}

void AttributeComponent::removeBonuses(int type/*, int level*/){

    switch(type){

            case ATTRIBUTE::AGILITY:
                bonusAttributes[AGILITY]-- /*-= level*/;
                break;

            case ATTRIBUTE::CHARISMA:
                bonusAttributes[CHARISMA]--; //-= level;
                break;

            case ATTRIBUTE::DEXTERITY:
                bonusAttributes[DEXTERITY]--; //-= level;
                break;

            case ATTRIBUTE::INTELLIGENCE:
                bonusAttributes[INTELLIGENCE]--;// -= level;
                break;

            case ATTRIBUTE::LUCK:
                bonusAttributes[LUCK]--;// -= level;
                break;

            case ATTRIBUTE::STRENGTH:
                bonusAttributes[STRENGTH]--;// -= level;
                break;

            case ATTRIBUTE::VITALITY:
                bonusAttributes[VITALITY]--;//-= level;
                break;

            default:
                break;
    }
}

void AttributeComponent::loadBonuses(int type/*, int level*/){


            switch(type){

            case ATTRIBUTE::AGILITY:
                bonusAttributes[AGILITY]++; //+= level;
                break;

            case ATTRIBUTE::CHARISMA:
                bonusAttributes[CHARISMA]++;// += level;
                break;

            case ATTRIBUTE::DEXTERITY:
                bonusAttributes[DEXTERITY]++;// += level;
                break;

            case ATTRIBUTE::INTELLIGENCE:
                bonusAttributes[INTELLIGENCE]++;// += level;
                break;

            case ATTRIBUTE::LUCK:
                bonusAttributes[LUCK]++;// += level;
                break;

            case ATTRIBUTE::STRENGTH:
                bonusAttributes[STRENGTH]++;// += level;
                break;

            case ATTRIBUTE::VITALITY:
                bonusAttributes[VITALITY]++;// += level;
                break;

            default:
                break;
            }
}


void AttributeComponent::setAttributes(int vit, int str, int dex, int agi, int intel, int charis, int luck){

mAttributes[ATTRIBUTE::VITALITY] = vit;
	mAttributes[STRENGTH] = str;
	mAttributes[DEXTERITY] = dex;
	mAttributes[AGILITY] = agi;
	mAttributes[INTELLIGENCE] = intel;
	mAttributes[CHARISMA] = charis;
	mAttributes[LUCK] = luck;


    mHpMax = ((mAttributes[VITALITY] * 4) + mLevel  * 20);
}

int AttributeComponent::getHP(){

	return mHp;
}

int AttributeComponent::getHPMax(){

	return mHpMax;
}

float AttributeComponent::getEXP(){

	return mExp;
}

float AttributeComponent::getEXPNext(){

	return mExpNext;
}

unsigned AttributeComponent::getLevel(){

	return mLevel;
}

void AttributeComponent::gainEXP(const float exp){

	mExp += exp;
}

void AttributeComponent::loseEXP(const float exp){

	mExp -= exp;
	if (mExp < 0) {

		mExp = 0;
	}
}


void AttributeComponent::gainHP(const int hp){

	mHp += hp;

	if (mHp > mHpMax) {

		mHp = mHpMax;
	}
}

void AttributeComponent::loseHP(const int hp){

	mHp -= hp;

	if (mHp < 0) {

		mHp = 0;
	}
}

void AttributeComponent::calculateNextEXP()
{
    ///DOES NOTHING?? TODO
}

void AttributeComponent::updateStats(const bool reset){

	mHpMax = ((mAttributes[VITALITY] * 4) + mLevel  * 20);

	if (reset) {

		mHp = mHpMax;
	}
}

void AttributeComponent::updateLevel(){

	if (mLevel == 0) {

		mLevel = 1;
	}

	mExpNext = (baseEXP * mLevel) * 5;

	while (mExp >= mExpNext && mExpNext != 0) {

		++mLevel;
		mExp -= mExpNext;

		//mExpNext = static_cast<float>((50 / 3) * (pow(mLevel + 1, 3) - 6 * pow(mLevel + 1, 2) + ((mLevel + 1) * 17) - 12));
		mExpNext = (baseEXP * mLevel) * 5;
		updateStats(true);

		mHasLevelled = true;
	}

	///if (mLevel % 5 == 0) { //TODO - Every 10 levels player gains an attribute point. Might change this.

		mAttributePoints++;
	///}

//	for(int i = 0; i < ATTRIBUTE::TOTAL_ATTRIBUTES; i++){
//
//        mAttributes[i]++;
//	}
}

void AttributeComponent::setAttributePoints(int p){

    mAttributePoints = p;
}

void AttributeComponent::update(){

	updateLevel();
}

void AttributeComponent::assignRandomAttributes(int level, bool npc){

    ///Used for enemies and NPCS (In theory)
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator(seed);
        int point = 3;
		///int counter = 0;
		if(level > 1){
            point += level;
		}

		if(!npc){
            std::uniform_int_distribution<int> pointDistribution(0, TOTAL_ATTRIBUTES-1);


            for (int i = 0; i < point; i++) {

                int roll = pointDistribution(generator);
                int currAttri = 0;

                switch (roll) {

                case ATTRIBUTE::AGILITY:
                    currAttri = getAttribute(ATTRIBUTE::AGILITY);
                    currAttri++;
                    setAttribute(ATTRIBUTE::AGILITY, currAttri);
                    break;

                case ATTRIBUTE::CHARISMA:
                    currAttri = getAttribute(ATTRIBUTE::CHARISMA);
                    currAttri++;
                    setAttribute(ATTRIBUTE::CHARISMA, currAttri);
                    break;

                case ATTRIBUTE::DEXTERITY:
                    currAttri = getAttribute(ATTRIBUTE::DEXTERITY);
                    currAttri++;
                    setAttribute(ATTRIBUTE::DEXTERITY, currAttri);
                    break;

                case ATTRIBUTE::INTELLIGENCE:
                    currAttri = getAttribute(ATTRIBUTE::INTELLIGENCE);
                    currAttri++;
                    setAttribute(ATTRIBUTE::INTELLIGENCE, currAttri);
                    break;


                case ATTRIBUTE::LUCK:
                    currAttri = getAttribute(ATTRIBUTE::LUCK);
                    currAttri++;
                    setAttribute(ATTRIBUTE::LUCK, currAttri);
                    break;

                case ATTRIBUTE::STRENGTH:
                    currAttri = getAttribute(ATTRIBUTE::STRENGTH);
                    currAttri++;
                    setAttribute(ATTRIBUTE::STRENGTH, currAttri);
                    break;

                case ATTRIBUTE::VITALITY:
                    currAttri = getAttribute(ATTRIBUTE::VITALITY);
                    currAttri++;
                    setAttribute(ATTRIBUTE::VITALITY, currAttri);
                    break;

                default:
                    break;
                }
            }
		}
		else{

            std::uniform_int_distribution<int> pointDistribution(0, 2);

            ///NPC HERE.. TODO Check this

            for (int i = 0; i < point; i++) {

                int roll = pointDistribution(generator);
                int currAttri = 0;

                switch (roll){

                 case 0:
                    currAttri = getAttribute(ATTRIBUTE::CHARISMA);
                    currAttri++;
                    setAttribute(ATTRIBUTE::CHARISMA, currAttri);
                    break;

                 case 1:
                    currAttri = getAttribute(ATTRIBUTE::INTELLIGENCE);
                        currAttri++;
                        setAttribute(ATTRIBUTE::INTELLIGENCE, currAttri);
                        break;

                 case 2:
                    currAttri = getAttribute(ATTRIBUTE::LUCK);
                        currAttri++;
                        setAttribute(ATTRIBUTE::LUCK, currAttri);
                        break;

                 default:
                    break;
                }
            }
		}
}

int AttributeComponent::getAttribute(const int attr){

	try {

		if (attr < 0 || attr >= ATTRIBUTE::TOTAL_ATTRIBUTES) {

			throw(std::runtime_error("Error: AttributeComponent::getAttribute() - Attribute not found: " + std::to_string(attr)));
		}
		else {

			return static_cast<int>(mAttributes[attr]);
		}
	}
	catch (std::exception &e) {

		std::ofstream outFile;

		outFile.open("ErrorLog.txt");

		if (outFile.is_open()) {

			outFile << e.what() << std::endl;

			outFile.close();
		}
	}

	return -1;
}

int AttributeComponent::getBonus(int type){

    try {

		if (type < 0 || type >= ATTRIBUTE::TOTAL_ATTRIBUTES) {

			throw(std::runtime_error("Error: AttributeComponent::getAttribute() - Attribute not found: " + std::to_string(type)));
		}
		else {

			return static_cast<int>(bonusAttributes[type]);
		}
	}
	catch (std::exception &e) {

		std::ofstream outFile;

		outFile.open("ErrorLog.txt");

		if (outFile.is_open()) {

			outFile << e.what() << std::endl;

			outFile.close();
		}
	}

	return -1;
}
