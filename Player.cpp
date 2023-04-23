#include "Player.h"
using namespace std;

Player::Player(int x, int y) {
    score = 0;
    pos.x = x;
    pos.y = y;
    pos.z = 9;
}

int Player::getX() const {
    return pos.x;
}

int Player::getY() const {
    return pos.y;
}

int Player::getZ() const {
    return pos.z;
}

void Player::setPosition(int x, int y, int z) {
    pos.x = x;
    pos.y = y;
    pos.z = z;
}



bool Player::handleSpecialEffects(World& world, int newX, int newY, int z) {
    int fieldValue = world.getFieldAt(newX, newY, z);

    if (fieldValue == -1 || fieldValue == -2 || fieldValue == -3) {
               if (fieldValue == -1) {

                 cout << "Effect Value -1, player is locked this round" << endl;
            }
        if (fieldValue == -2) {
            int min_x = 0;
            int min_y = 0;
            int min_value = 10;

            for (int x = 0; x < 5; x++) {
                for (int y = 0; y < 5; y++) {
                    int current_value = world.getFieldAt(x, y, 9);
                    if (current_value >= 1 && current_value <= 9 && current_value < min_value) {
                        min_x = x;
                        min_y = y;
                        min_value = current_value;
                    }
                }
            }

            setPosition(min_x, min_y, 9);
            cout << "Effect Value -2, player moved to position (" << min_x << ", " << min_y << ", 9)" << endl;
        }

        if (fieldValue == -3) {
            int rand_x, rand_y;
            do {
                rand_x = rand() % 5;
                rand_y = rand() % 5;
            } while (world.getFieldAt(rand_x, rand_y, 9) < 1 || world.getFieldAt(rand_x, rand_y, 9) > 9);

            setPosition(rand_x, rand_y, 9);
            cout << "Effect Value -3, player teleported to position (" << rand_x << ", " << rand_y << ", 9)" << endl;
        }

        world.setFieldAt(newX, newY, z, 0); // Set the field value to 0
        return true;
    }

    return false;
}
