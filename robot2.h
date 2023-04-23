#ifndef ROBOT2_H
#define ROBOT2_H

#include "player.h"
#include "world.h"

class Robot2 : public Player {
public:
    Robot2(int x, int y);

    int performAction(World& world, int dx, int dy);
};

#endif // ROBOT2_H
