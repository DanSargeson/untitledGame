#ifndef EVENT_H
#define EVENT_H

#include <stdlib.h>
#include <iostream>
//#include "puzzle.h"
#include "Enemy.h"
//#include "dArray.h"
#include "GUI.h"

class Event{
private:
    int typeOfEvent;
    std::shared_ptr<GUI::Menu> eventMenu;
    std::vector<Enemy> enemies;

public:
    Event();
    virtual ~Event();
    void createEvent();
    void enemyEvent();
    void puzzleEvent();
};

#endif // EVENT_H

