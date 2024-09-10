#include "QuestComponent.h"

QuestComponent::QuestComponent(std::shared_ptr<Entity> owner) : Component(owner){


}

void QuestComponent::acceptQuest(int questID, int faction){

    quests[questID].accepted = true;
    quests[questID].active = true;
    quests[questID].factionID = faction;
}

bool QuestComponent::isQuestActive(int questID){

    return quests.find(questID) != quests.end() && quests[questID].active;
}

int QuestComponent::questsCompleted(){

    int counter = 0;
    for(auto q : quests){

        if(q.second.completed){

            counter++;
        }
    }

    return counter;
}

int QuestComponent::questsCompletedByFaction(int faction){

    int counter = 0;
    for(auto q : quests){

        if(q.second.factionID == faction && q.second.completed){

            counter++;
        }
    }

    return counter;
}
