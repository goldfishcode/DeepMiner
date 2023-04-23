#ifndef ROBOT3_H_INCLUDED
#define ROBOT3_H_INCLUDED


#include "Player.h"
#include "World.h"

class Robot3 : public Player {
public:
    Robot3(int x, int y);

    int performAction(World& world, int dx, int dy);

};



#endif // ROBOT3_H_INCLUDED
