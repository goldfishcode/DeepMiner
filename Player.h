#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "World.h"

class World;
class Player {
public:
    Player(int x, int y);
     virtual ~Player() = default;

    int getX() const;
    int getY() const;
    int getZ() const;

    void setPosition(int x, int y, int z);
    virtual bool handleSpecialEffects(World& world, int newX, int newY, int z);

private:
    struct Position {
        int x;
        int y;
        int z;
    };

    int score;
    Position pos;
};

#endif // PLAYER_HPP
