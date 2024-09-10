#ifndef QUESTCOMPONENT_H
#define QUESTCOMPONENT_H

#include <unordered_map>

#include "Component.h"
#include "FactionEncounter.h"

struct QuestState{

    bool accepted;
    bool active;
    bool completed;
    bool positivePath;
    int factionID;

    QuestState() : accepted(false), active(false), completed(false), positivePath(false), factionID(-1){}
};

class QuestComponent : public Component{

public:
    QuestComponent(std::shared_ptr<Entity> owner);

    void acceptQuest(int questID, int faction);
    bool isQuestActive(int questID);
    int questsCompleted();
    int questsCompletedByFaction(int faction);

private:

    int currentQuestID;
    std::unordered_map<int, QuestState> quests;
};

#endif // QUESTCOMPONENT_H
