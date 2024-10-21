//#include "stdafx.h"
#include "NPC.h"
#include "FactionComponent.h"
#include "DialogueComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"
#include "State.h"

int NPC::characterID = 0;

void NPC::generateID(){

	this->characterID++;
}

std::string NPC::getFactionStr(){

    std::string fact = factionComponent->getFactionName(faction);

    return fact;
}

NPC::NPC(int level, int faction){        ///TODO FACTION IS SETTING RANDOMLY HERE<<<<

	///this->createFactionComponent();
	m_type = NPC_TYPE::ALCHEMIST;


	if(faction == -1){

	int low = 2; ///TODO: BLACJ AND WHITE ARE 0 AND 1
	int high = FACTIONS::TOTAL_FACTIONS - 1;
	int randomIndex = 0;
	   // Use std::random_device to obtain a seed for the random number generator
                std::random_device rd;

                // Use std::mt19937 as the random number generator
                std::mt19937 gen(rd());

                // Use std::uniform_int_distribution to generate random indices
                std::uniform_int_distribution<> dis(low, high);

                // Generate a random index
                randomIndex = dis(gen);

                // Access the corresponding element in the set
//                int randomValue = numbers[randomIndex];
	Entity::faction = randomIndex;
	NPC::faction = randomIndex;
	}
	else{

        Entity::faction = faction;
        NPC::faction = faction;
	}
	this->questGiver = false;
	this->companion = false;
	this->dialogue = " ";
	this->seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	this->generator.seed(seed);

	//TODO add a Colour counter and make this dirtribute pixels.
	std::uniform_int_distribution<int> goldDistribution(1, 500);
	int randomGold = goldDistribution(generator);

	this->gold = randomGold;

	//createFactionComponent();
	Entity::setLevel(level);
	//createAttributeComponent(level, true, true);
   // attributeComponent->assignRandomAttributes(level, true);
	//createSkillComponent();
	//calculateSkills();
	//createAttackComponent();
	//this->createDialogueComponent();


    std::array<int, 4> seeds;
    std::random_device rd;
    std::generate(seeds.begin(), seeds.end(), std::ref(rd));
    std::seed_seq seed_seq(seeds.begin(), seeds.end());
    std::mt19937 gen(seed_seq);
    std::uniform_int_distribution<> dis(0, TOTAL_TYPES-1);
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dis(0, TOTAL_TYPES-1);
    int job = dis(gen);
	name += Entity::entityNames[job];
	setType(job);
	Entity::m_name = name;


	std::uniform_int_distribution<int> textDistribution(1, 5);
	int randomText = textDistribution(generator);
	std::string v = "99" + std::to_string(randomText);
//	int total = std::stoi(v);
//	dialogueComponent->setDialogueOptions("Resources/Text/randomNews.txt", total);

	textFileName = "Resources/Text/randomNews.txt";

	this->createInventory();

	this->generateID();

//	initBackground(Engine::GetInstance()->GetRenderer());
}

NPC::NPC(int type, int level, int faction) {

    Entity::faction = faction;
    NPC::faction = faction;

    m_type = type;
    setName(entityNames[m_type]);
	this->questGiver = false;
	this->companion = false;
	this->dialogue = " ";
	this->seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	this->generator.seed(seed);

	//TODO add a Colour counter and make this dirtribute pixels.
	std::uniform_int_distribution<int> goldDistribution(1, 500);
	int randomGold = goldDistribution(generator);

	this->gold = randomGold;

	//createFactionComponent();
	Entity::setLevel(level);
	m_level = level;
	//createAttributeComponent(level, true, true);
    //attributeComponent->assignRandomAttributes(level, true);
	//createSkillComponent();
	//calculateSkills();
	//createAttackComponent();
	//this->createDialogueComponent();


	std::uniform_int_distribution<int> textDistribution(1, 5);
	int randomText = textDistribution(generator);
	std::string v = "99" + std::to_string(randomText);
//	int total = std::stoi(v);
//	dialogueComponent->setDialogueOptions("Resources/Text/randomNews.txt", total);

	textFileName = "Resources/Text/randomNews.txt";

	///this->createInventory();

	this->generateID();
}

NPC::NPC(int faction, bool questGiver, std::string fileName){

	//this->factionComponent->changeRep()
	m_type = NPC_TYPE::LIBRARIAN;
	this->faction = faction;
	this->questGiver = questGiver;
	this->dialogue = dialogue;
	this->createFactionComponent();
//	this->createDialogueComponent();

	textFileName = fileName;
	this->factionComponent->calculateReputation(this->faction);

	std::uniform_int_distribution<int> goldDistribution(1, 500);

	int randomGold = goldDistribution(generator);

	this->gold = randomGold;

	this->createInventory();

//	initBackground(rend);
}

NPC::~NPC(){


}

//std::vector<std::string> NPC::getDialogueOptions() {
//
//	if (type == INNKEEPER) {
//
//		return dialogueComponent->getDialogueOptions(true);
//	}
//	else {
//
//		return Entity::getDialogueOptions();
//	}
//}

void NPC::initBackground(SDL_Renderer* rend) {

//	bg = std::make_unique<Texture>();
	std::string fileName = "Resources/Images/temp/";
	switch (faction) {

	case FACTIONS::BLACK:
		fileName = " ";
		break;

	case FACTIONS::RED:
		fileName += "Red.png";
		break;

	case FACTIONS::YELLOW:
		fileName += "Green.png";
		break;

	case FACTIONS::BLUE:
		fileName += "Blue.png";
		break;

	case FACTIONS::GREEN:
		fileName += "Aqua.png";
		break;

	case FACTIONS::INDIGO:
		fileName += "Yellow.png";
		break;

	case FACTIONS::ORANGE:
		fileName += "MAgenta.png";
		break;

	case FACTIONS::WHITE:
		fileName += "White.png";
		break;

	default:
		fileName = " ";
		break;
	}

//	if (faction != FACTIONS::BLACK) {
//
//		bg->loadFromFile(fileName, rend);
//	}
}

int NPC::getFaction(){

	return this->faction;
}

bool NPC::givesQuest(){


	return this->questGiver;
}

void NPC::setType(int t){

	m_type = t;
}

std::string NPC::getName(){


	return this->name;
}

void NPC::setName(std::string name){

    Entity::m_name = name;
	this->name = name;
}

void NPC::setTextureRect(SDL_Rect r){

//	bg->setTextureRect(r.x, r.y, r.w, r.h);
}

int NPC::getInvCount(){


	return this->inv->smrtSize();
}

//std::string NPC::getItemString(int index){
//
//
//	std::shared_ptr<Item> item = this->inv->findItemSmart(index);
//
//	return item->getTypeStr();
//}

void NPC::setDialogue(int id) {

//	if (m_type == INNKEEPER) {
//
//		textFileName = "Resources/Text/innkeeper.txt";
//	}

//	dialogueComponent->NEWDIAG(textFileName, id);

	//std::uniform_int_distribution<int> textDistribution(1, 5);
	//int randomText = textDistribution(generator);

	//if (type == NPC_TYPE::PEASANT) {

	//	std::string v = "99" + std::to_string(randomText);
	//	int total = std::stoi(v);
	//	dialogueComponent->setDialogueOptions("Resources/Text/randomNews.txt", id);
	//}

	//if (type == NPC_TYPE::INNKEEPER) {

	//	int total = 666;
	//	dialogueComponent->NEWDIAG("Resources/Text/innkeeper.txt", id);
	//	//dialogueComponent->setDialogueOptions("Resources/Text/innkeeper.txt", id);
	//}
}

bool NPC::quitDialogue() {

//	return dialogueComponent->quitDialogue();
	return  false;
}

void NPC::setCharm(bool x) {

//	dialogueComponent->setCharm(x);
}

bool NPC::charm() {

//	return dialogueComponent->charm();
	return false;
}

bool NPC::shop() {

//	return dialogueComponent->shop();
	return false;
}

void NPC::talk(int choice) {

//	if (type == INNKEEPER) {
//
////		dialogueComponent->talk(choice, true);
//	}
//	else {
//
////		dialogueComponent->talk(choice);
//	}

}

//std::string NPC::getDialogue(){
//
//	if (this->dialogueComponent) {
//
//
//	//	return dialogueComponent->getDialogue();
//		//return this->dialogueComponent->getDialogue();
//	}
//
//	return "";
//}

int NPC::getDialogueID(){

//	int id = dialogueComponent->getID();
	return 0;
}

void NPC::createInventory(){

	this->seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	this->generator.seed(seed);

	std::uniform_int_distribution<int> invDistribution(1, 100);
	std::uniform_int_distribution<int> itemDistribution(1, 10);
	std::uniform_int_distribution<int> rarityDistribution(0, 4);

	int items = itemDistribution(generator);

	//std::vector<std::shared_ptr<Item&>> itemVec;
	for (int i = 0; i < items; i++) {

        int rarity = rarityDistribution(generator);
		int random = invDistribution(generator);

		int lvl = StateData::GetInstance()->getActiveCharacter()->getLevel();			//MAGIC NUMBER
		if (random > 50) {

			Weapon tempW(lvl, rarity);

			auto tempWe = make_shared<Weapon>(lvl, rarity);
			this->inv->addItemVectorSmart(tempWe);
			//itemVec.push_back(tempW);
		}
		else {

			Armour tempA(lvl, rarity);

			auto tempAe = make_shared<Armour>(lvl, rarity);
			this->inv->addItemVectorSmart(tempAe);
		}
	}
}

//int NPC::getCurrentMapID(){
//
//	return this->mapID;
//}

void NPC::setDialogueChoice(int choice){

//	this->dialogueComponent->playerChoice(choice);
}

std::shared_ptr<Item> NPC::getItem(int index){

	return inv->findItemSmart(index);
}

void NPC::removeItem(int index){


	this->inv->removeItemVectorSmart(this->inv->findItemSmart(index));
}

int NPC::getGold(){

	return this->gold;
}

std::string NPC::getInvAsString(){

	return inv->getInvAsString();
}

void NPC::update(){


}

void NPC::render(){

//	bg->render(rend, bg->getTextureRect().x, bg->getTextureRect().y);
}
