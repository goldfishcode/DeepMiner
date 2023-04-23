#include "robot1.h"
#include "world.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Player.h"
using namespace std;

Robot1::Robot1(int x, int y) : Player(x, y) {
}

int Robot1::performAction(World& world, int dx, int dy) {
    int newX = dx;
    int newY = dy;

    if (newX >= 0 && newX < 5 && newY >= 0 && newY < 5) {
        setPosition(newX, newY, getZ());

        for (int z = 0; z < 10; z++) {
            if (handleSpecialEffects(world, newX, newY, z)) {
                return 0; // If an effect is applied, stop execution and return 0
            }
        }

        vector<int> fieldValues(10);

        for (int z = 0; z < 10; z++) {
            fieldValues[z] = world.getFieldAt(newX, newY, z);
        }

        auto highestValueIt = max_element(fieldValues.begin(), fieldValues.end());
        int highestZ = distance(fieldValues.begin(), highestValueIt);
        int highestValue = world.getFieldAt(newX, newY, highestZ);

        world.setFieldAt(newX, newY, highestZ, -100);

        return highestValue == -100 ? 0 : highestValue;
    }

    return 0;
}
