#include "robot3.h"
#include "world.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>
#include "Player.h"
using namespace std;

Robot3::Robot3(int x, int y) : Player(x, y) {
}

int Robot3::performAction(World& world, int dx, int dy) {
    int newX = dx;
    int newY = dy;

    if (newX >= 0 && newX < 5 && newY >= 0 && newY < 5) {
        setPosition(newX, newY, getZ());

        for (int z = 0; z < 10; z++) {
            if (handleSpecialEffects(world, newX, newY, z)) {
                return 0; // If an effect is applied, stop execution and return 0
            }
        }

        vector<int> availableLayers;
        for (int z = 0; z < 10; z++) {
            if (world.getFieldAt(newX, newY, z) != -100) {
                availableLayers.push_back(z);
            }
        }

        if (availableLayers.size() < 2) {
            return 0;
        }

        shuffle(availableLayers.begin(), availableLayers.end(), std::default_random_engine(std::random_device{}()));

        int z1 = availableLayers[0];
        int z2 = availableLayers[1];

        int fieldValue1 = world.getFieldAt(newX, newY, z1);
        int fieldValue2 = world.getFieldAt(newX, newY, z2);

        world.setFieldAt(newX, newY, z1, -100);
        world.setFieldAt(newX, newY, z2, -100);

        int score = (fieldValue1 < 0 ? 0 : fieldValue1) + (fieldValue2 < 0 ? 0 : fieldValue2);

        return score;
    }

    return 0;
}
