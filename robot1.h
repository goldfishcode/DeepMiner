#ifndef ROBOT1_H
#define ROBOT1_H

#include "Player.h"
#include "World.h"

class Robot1 : public Player {
public:
    Robot1(int x, int y);

    int performAction(World& world, int dx, int dy);


};

#endif
