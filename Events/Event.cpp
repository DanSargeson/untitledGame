#include "Event.h"
#include "Game.h"
#include "Engine.h"

auto player = StateData::GetInstance()->getActiveCharacter();

Event::Event(){
    this->typeOfEvent = 2;
    eventMenu = std::make_shared<GUI::Menu>();

    //player->attributeComponent->getLevel();
}

Event::~Event(){
}

void Event::createEvent(){

    int i = rand() % this->typeOfEvent;

    switch(i){
    case 0:
        //enemy battle
        enemyEvent();
        break;

    case 1:
        //puzzle
        puzzleEvent();
        break;

    case 2:
        cout << "Nothing!" << "\n";
        break;
    default:
        break;
    }
}

void Event::enemyEvent(){
//	bool playerTurn = false;
//	int choice = 0;
//	int playerAccuracy = 0;
//	int playerDefence = 0;
//	int playerTotal = 0;
//	int enemyAccuracy = 0;
//	int enemyDefence = 0;
//	int enemyTotal = 0;
//	int combatTotal = 0;
//	int combatRoll = 0;
//	int combatRollPlayer = 0;
//	int combatRollEnemy = 0;
//	while(enemies.size() > 0) {
//		enemies.erase(enemies.begin());
//	}
//
//
//	//COIN TOSS DETERMINES TURN
//	int coinToss = rand() % 2 + 1;
//	if (coinToss == 2)
//		playerTurn = true;
//	else
//		playerTurn = false;
//
//	bool escape = false;
//	bool playerDefeated = false;
//	bool enemyDefeated = false;
//	int noOfEnemies = rand() % 3 + 1;
//
//	for (size_t i = 0; i < noOfEnemies; i++){
////		enemies.push_back(Enemy(StateData::GetInstance()->getActiveCharacter()->attributeComponent->getLevel() + rand()%3));
//	}
//
//	//BATTLE VARIABLES
//	int attackRoll = 0;
//	int defendRoll = 0;
//	int damage = 0;
//	int gainEXP = 0;
//	int gainGold = 0;
//
//	while (!escape && !playerDefeated && !enemyDefeated) {
//
//		if (playerTurn && !playerDefeated) {
//            //TODO:: HERE IS WHERE TO CHANGE THINGS FOR BATTLEMODE
//            std::vector<std::string> ops;
//            ops.push_back("Attack");
//            ops.push_back("Defend");
//            ops.push_back("Use Item");
//            eventMenu->setMenuOptions(ops, true);
//  //          std::string msg = "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHpMax());
//
//            getMainText()->setString("THIS SHOULD SHOW HP");
//            getEnemyText()->setString("Choose action: ");
////			system("clear");
////			cout << "= BATTLE MENU = \n\n";
////			cout << "HP: " << player.getHP() << "/" << player.getHpMax() << "\n\n";
////			cout << "0: Escape \n";
////			cout << "1: Attack \n";
////			cout << "2: Defend \n";
////			cout << "3: Use Item \n\n";
//
//			cout << "Choose action: \n";
//			cin >> choice;
//
//			while (cin.fail() || choice > 3 || choice < 0) {
//				system("clear");
//				cout << "Faulty input.\n\n";
//				cin.clear();
//				cin.ignore(100, '\n');
//
//				cout << "= BATTLE MENU = \n";
//				//cout << "HP: " << player.getHP() << "/" << player.getHpMax() << "\n\n";
//				cout << "0: Escape \n";
//				cout << "1: Attack \n";
//				cout << "2: Defend \n";
//				cout << "3: Use Item \n\n";
//				cout << "Choose action: " << "\n";
//				cin >> choice;
//			}
//
//			cin.ignore(100, '\n');
//			cout << "\n";
//
//			switch (choice){
//			case 0: //ESCAPE
//				escape = true;
//				cout << "ESCAPED!\n\n";
//				break;
//			case 1: //ATTACK
//				system("clear");
//				cout << "SELECT ENEMY: \n";
//				for (size_t i = 0; i < enemies.size(); i++) {
//					cout << i << ": " <<  enemies[i].getName() << " Level " << enemies[i].getLevel() << " - " << " HP "
//						<< enemies[i].getHp() << "/" << enemies[i].getHpMax() <<
//						" Defence: " << enemies[i].getDefence() <<
//						" Accuracy: " << enemies[i].getAccuracy() << " " <<
//						"Damage: " << enemies[i].getDamageMin() << " - " << enemies[i].getDamageMax() << "\n";
//				}
//				cout << "\n\n";
//				cin >> choice;
//
//				while (cin.fail() || choice >= enemies.size() || choice < 0) {
//					cout << "Faulty input.\n\n";
//					cin.clear();
//					cin.ignore(100, '\n');
//
//					cout << "SELECT ENEMY!";
//					cin >> choice;
//				}
//
//				cin.ignore(100, '\n');
//				cout << "\n";
//
//				//combatRoll = rand() % 100 + 1;
////				combatTotal = enemies[choice].getDefence() + StateData::GetInstance()->getActiveCharacter()->getAccuracy();
//				enemyTotal = enemies[choice].getDefence() / (double)combatTotal * 100;
//				playerTotal = StateData::GetInstance()->getActiveCharacter()->getAccuracy() / (double)combatTotal * 100;
//				combatRollPlayer = rand() % playerTotal + 1;
//				combatRollEnemy = rand() % enemyTotal + 1;
//
//				//cout << "Player roll: " << combatRollPlayer << "\n\n";
//				//cout << "Enemy roll: " << combatRollEnemy << "\n\n";
//				if (combatRollPlayer > combatRollEnemy) {
//					//HIT
//					damage = StateData::GetInstance()->getActiveCharacter()->getDamage();
//					int totalDmg = enemies[choice].takeDamage(damage);
//					cout << "HIT for " << totalDmg << " damage!\n\n" ;
//					if (!enemies[choice].isAlive()) {
//						cout << "YOU DEFEATED!\n\n";
//						gainGold = rand() & enemies[choice].getLevel() * 10 + 1;
//						StateData::GetInstance()->getActiveCharacter()->setGold(gainGold);
//						gainEXP = enemies[choice].getExp();
//						StateData::GetInstance()->getActiveCharacter()->setExp(gainEXP);
//						cout << "Gold Gained: " << gainGold << "\n";
//						cout << "EXP Gained: " << gainEXP << "\n\n";
//
//						//ITEM ROLL
//						int r = rand() % 100 + 1;
//						int rarity = -1;
//						if (r > 20) {
//							//GET ITEM
//							rarity = 0; //COMMON ITEM
//							int newRoll = rand() % 100 + 1;
//							if (newRoll > 60) {
//								rarity = 1; //UNCOMMON ITEM
//
//								newRoll = rand() % 100 + 1;
//								if (newRoll > 75 && StateData::GetInstance()->getActiveCharacter()->getLevel() > 20) {
//									rarity = 2; //RARE
//
//									int newRoll = rand() % 100 + 1;
//									if (newRoll > 90) {
//										rarity = 3; //LEGENDARY ITEM
//
//										int newRoll = rand() % 100 + 1;
//										if (newRoll > 95) {
//											rarity = 4; //MYTHIC ITEM
//										}
//									}
//								}
//							}
//
//							if (r >= 0) {
//								r = rand() % 100 + 1;
//								if (r > 50) {
//									int lvl = StateData::GetInstance()->getActiveCharacter()->getLevel();
//									Weapon tempW(lvl, rarity);
//									auto tempWe = make_shared<Weapon>(tempW);
//									StateData::GetInstance()->getActiveCharacter()->addItem(tempWe);
//									cout << "Weapon dropped!\n";
//									cout << tempWe->getName() << " " << tempWe->getTypeStr() << "\n\n";
//								}
//								else {
//									Armour tempA(StateData::GetInstance()->getActiveCharacter()->getLevel(), rarity);
//									auto tempAw = make_shared<Armour>(tempA);
//									StateData::GetInstance()->getActiveCharacter()->addItem(tempAw);
//									cout << "Armour dropped!\n";
//									cout << tempAw->getName() << " " << tempAw->getTypeStr() << "\n\n";
//								}
//							}
//						}
//						enemies.erase(enemies.begin() + choice);
//						cout << "Continue...\n";
//						cin.get();
//					}
//				}
//				else {
//					//MISS
//					cout << "MISSED ENEMY!\n\n";
//				}
//
//				break;
//			case 2: //DEFEND
//				break;
//			case 3: //USE ITEM
//				break;
//			default:
//				break;
//			}
//
//			//MOVE
//
//			//LEAVE TURN
//			playerTurn = false;
//		}
//		else if(!playerTurn && !escape && !enemyDefeated){
//			//ENEMY TURN
//			cout << "= ENEMY ATTACKS = \n\n";
//			for (size_t i = 0; i < enemies.size(); i++){
//				combatTotal = enemies[i].getAccuracy() + StateData::GetInstance()->getActiveCharacter()->getDefence();
//				enemyTotal = enemies[i].getAccuracy() / (double)combatTotal * 100;
//				playerTotal = StateData::GetInstance()->getActiveCharacter()->getDefence() / (double)combatTotal * 100;
//				combatRollPlayer = rand() % playerTotal + 1;
//				combatRollEnemy = rand() % enemyTotal + 1;
//				cout << enemies[i].getName() << " ";
//				//cout << "Player roll: " << combatRollPlayer << "\n\n";
//				//cout << "Enemy roll: " << combatRollEnemy << "\n\n";
//				if (combatRollPlayer < combatRollEnemy) {
//					//HIT
//					damage = enemies[i].getDamage();
//					int totalDmg = StateData::GetInstance()->getActiveCharacter()->takeDamage(damage);
//					cout << "HIT for " << totalDmg << " damage!\n\n";
//					cout << "HP: " << StateData::GetInstance()->getActiveCharacter()->getHP() << "/" << StateData::GetInstance()->getActiveCharacter()->getHpMax() << "\n\n";
//					if (!StateData::GetInstance()->getActiveCharacter()->isAlive()) {
//						cout << "YOU DIED!\n\n";
//						playerDefeated = true;
//						break;
//					}
//				}
//				else {
//					//MISS
//					cout << "ENEMY MISSED!\n\n";
//				}
//
//				cout << "Continue...\n";
//				cin.get();
//			}
//
//			//END TURN
//			playerTurn = true;
//		}
//
//		if (!StateData::GetInstance()->getActiveCharacter()->isAlive()) {
//			playerDefeated = true;
//		}
//		else if (enemies.size() <= 0) {
//			enemyDefeated = true;
//		}
//	}
//
//	cout << "All enemies defeated!\n\n";
}

void Event::puzzleEvent(){
//    bool completed = false;
//    int userAns = 0;
//    int chances = 3;
//    int expGain = (chances * player.getLevel() * (rand() % 10 + 1));
//	int puzzleNum = rand() % 2;
//	Puzzle p("puzzles/1.txt");
//	Puzzle p1("puzzles/2.txt");
//    while(!completed && chances > 0){
//            cout << "Chances: " + to_string(chances) << "\n";
//            if(puzzleNum == 0) cout << p.getAsString() << "\n";
//			else cout << p1.getAsString() << "\n";
//            cout << "\n" << "Your Answer: ";
//            cin >> userAns;
//
//			while (cin.fail()) {
//				cout << "Faulty input.\n";
//				cin.clear();
//				cin.ignore(100, '\n');
//				cout << "\n" << "Make your choice:" << "\n";
//				cin >> userAns;
//			}
//
//			cin.ignore(100, '\n');
//			cout << "\n";
//
//            if(puzzleNum == 0 && p.getCorrectAnswer() == userAns){
//                completed = true;
//                //GIVE EXP
//                player.setExp(expGain);
//                cout << "\n" << "You gained " << expGain << " experience." << "\n";
//            }
//			else if (puzzleNum == 1 && p1.getCorrectAnswer() == userAns) {
//				completed = true;
//				//GIVE EXP
//				player.setExp(expGain);
//				cout << "\n" << "You gained " << expGain << " experience." << "\n";
//			}
//
//            chances--;
//    }
//
//    if(completed){
//        cout << "WINNAR WINNAR" << "\n\n";
//    }
//    else{
//        cout << "YOU FAILED MATE" << "\n\n";
//    }

}

