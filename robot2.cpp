#include "robot2.h"
#include "world.h"
#include "Player.h"
#include <cstdlib>
#include <vector>
#include <numeric>
using namespace std;

Robot2::Robot2(int x, int y) : Player(x, y) {
}

int Robot2::performAction(World& world, int dx, int dy) {
    // If no movement arguments are provided, generate random movement
    int newX = dx;
    int newY = dy;

    if (newX >= 0 && newX < 5 && newY >= 0 && newY < 5) {
        setPosition(newX, newY, getZ());

        // Create a vector to store field values for z=9, z=8, and z=7
        vector<int> fieldValues(3);
        bool lockedThisRound = false;

        // Fill the vector with field values at the given x and y coordinates
        for (int z = 9, i = 0; z >= 7; z--, i++) {
        int fieldValue = world.getFieldAt(newX, newY, z);
            if (fieldValue == -2) {
                int min_x = 0;
                int min_y = 0;
                int min_value = 10; // Set initial minimum value to 10, since we only consider values between 1 and 9

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
                 world.setFieldAt(newX, newY, z, 0);
                 lockedThisRound = true;
                break;
            }

            if (fieldValue == -1) {
                lockedThisRound = true;
                world.setFieldAt(newX, newY, z, 0); // Set the field value to 0 when -1 value field is encountered
                break;
            }
               if (fieldValue == -3) {
                int rand_x, rand_y;
                do {
                    rand_x = rand() % 5;
                    rand_y = rand() % 5;
                } while (world.getFieldAt(rand_x, rand_y, 9) < 1 || world.getFieldAt(rand_x, rand_y, 9) > 9);

                setPosition(rand_x, rand_y, 9);
                cout << "Effect Value -3, player teleported to position (" << rand_x << ", " << rand_y << ", 9)" << endl;
                lockedThisRound = true;
                break;
            }
            fieldValues[i] = fieldValue == -100 ? 0 : fieldValue; // Set the value to 0 if the field is empty
            world.setFieldAt(newX, newY, z, -100); // Clear the field at the current x, y, and z coordinates
        }

        if (!lockedThisRound) {
            // Calculate the total score to be added using std::accumulate
            int scoreToAdd = accumulate(fieldValues.begin(), fieldValues.end(), 0);

            // Return the total score to be added
            return scoreToAdd;
        } else {
            return 0;
        }
    }

    // Return 0 if the player doesn't move
    return 0;
}
