#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include "World.h"
#include "Player.h"
#include "robot1.h"
#include "robot2.h"
#include "robot3.h"

using namespace std;

int main() {
    srand(time(NULL)); // Seed the random number generator with the current time for more randomness

    // Variables to keep track of each player's score
    int player1Score = 0;
    int player2Score = 0;

    // Variables to store player choices and the game mode
    int player1Choice, player2Choice;
    int gameMode;
    cout << "Choose game mode (1 for player vs player, 2 for player vs computer): ";
    cin >> gameMode;

    // Get robot choices for both players or player and computer
    cout << "Choose player 1's robot (1, 2, or 3): ";
    cin >> player1Choice;
    if (gameMode == 1) {
        cout << "Choose player 2's robot (1, 2, or 3): ";
    } else {
        cout << "Choose computer's robot (1, 2, or 3): ";
    }
    cin >> player2Choice;

    // Create pointers to Player objects for both players (using nullptr to initialize)
    Player* player1Robot = nullptr;
    Player* player2Robot = nullptr;

    // Assign player1's robot based on their choice
    // We use static_cast to convert the Robot1/2/3 pointers to Player pointers
    // This is because Player is the base class for Robot1/2/3 classes
    if (player1Choice == 1) {
        player1Robot = static_cast<Player*>(new Robot1(0, 0));
    } else if (player1Choice == 2) {
        player1Robot = static_cast<Player*>(new Robot2(0, 0));
    } else {
        player1Robot = static_cast<Player*>(new Robot3(0, 0));
    }

    // Assign player2's or computer's robot based on their choice, using the same static_cast method
    if (player2Choice == 1) {
        player2Robot = static_cast<Player*>(new Robot1(4, 4));
    } else if (player2Choice == 2) {
        player2Robot = static_cast<Player*>(new Robot2(4, 4));
    } else {
        player2Robot = static_cast<Player*>(new Robot3(4, 4));
    }

    // Create a world object
    World world;

    // Main game loop
    while (true) {
        // Show the world with robots' positions
        world.PrintWorld(*player1Robot, *player2Robot);

        // Show scores
        cout << "Player 1 Score: " << player1Score << endl;
        cout << "Player 2/Computer Score: " << player2Score << endl;

        // Get player 1's move
        int dx, dy;
        cout << "Enter player 1 movement (dx dy): ";
        cin >> dx >> dy;

        // Perform player 1's action and update their score
    if (player1Choice == 1) {
        player1Score += static_cast<Robot1*>(player1Robot)->performAction(world, dx, dy);
    } else if (player1Choice == 2) {
        player1Score += static_cast<Robot2*>(player1Robot)->performAction(world, dx, dy);
    } else {
        player1Score += static_cast<Robot3*>(player1Robot)->performAction(world, dx, dy);
    }

    // If player vs player, get player 2 input, otherwise generate random dx and dy for computer
    if (gameMode == 1) {
        cout << "Enter player 2 movement (dx dy): ";
        cin >> dx >> dy;
    } else {
        dx = rand() % 6;
        dy = rand() % 6;
    }

    // Perform player 2's or computer's action and update their score
    // We use static_cast again to call the correct performAction() method for the specific Robot1/2/3 object
    if (player2Choice == 1) {
        player2Score += static_cast<Robot1*>(player2Robot)->performAction(world, dx, dy);
    } else if (player2Choice == 2) {
        player2Score += static_cast<Robot2*>(player2Robot)->performAction(world, dx, dy);
    } else {
        player2Score += static_cast<Robot3*>(player2Robot)->performAction(world, dx, dy);
    }
    // If a player's score is greater than 50, rearrange the world
   if ((player1Score % 50 == 0 && player1Score != 0) || (player2Score % 50 == 0 && player2Score != 0)) {
        int randomFunction = rand() % 3 + 1;  // Generate a random number between 1 and 3

        switch (randomFunction) {
            case 1:
                world.shuffleLayers();
                break;
            case 2:
                world.SortLayersDescending();
                break;
            case 3:
                world.sortLayersAscending();
                break;
            default:
                break;
        }
    }

}


delete player1Robot;
delete player2Robot;


return 0;
}
