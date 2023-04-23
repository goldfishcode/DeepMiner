#include "World.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <windows.h>
#include <iomanip> // Added this header to include setw()

using namespace std;

// Constructor that initializes the world's field (grid)
World::World() {
    field = grid();
    // alias for a three-dimensional vector of integers, grid data structure is used to store the field member variable of the World class.
    // Seed a random number generator using the current time
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    // using <chrono> library to obtain the current time from a high-resolution clock
    std::mt19937 generator(seed);
    // Create distributions for random values within specific ranges using a random number generator
    std::uniform_int_distribution<int> distribution(1, 9);
    std::uniform_int_distribution<int> effectDistribution(-3, -1);
    std::uniform_int_distribution<int> positionDistribution(0, 4);

    // Initialize the 3D grid (field) with random values
    for (int x = 0; x < 5; x++) {
        field.push_back(std::vector<std::vector<int>>());
        for (int y = 0; y < 5; y++) {
            field.at(x).push_back(std::vector<int>(10));
            for (int z = 0; z < 10; z++) {
                field.at(x).at(y).at(z) = distribution(generator);
            }
        }
    }

    // Add special effect tiles to the grid randomly
    for (int z = 0; z < 10; z++) {
        for (int i = 0; i < 1; i++) {
            int x = positionDistribution(generator);
            int y = positionDistribution(generator);
            field.at(x).at(y).at(z) = effectDistribution(generator);
        }
    }
}

// Function to set text and background colors in the console
void SetColor(int textcolor, int bgcolor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textcolor | bgcolor << 4);
}

// Function to print the current state of the world
void World::PrintWorld(const Player& player, const Player& computer) {
    SetColor(11, 0); // Change console text and background colors

    // Loop through the world's layers
    for (int row = 0; row < 2; row++) {
        // Print layer labels
        for (int z = 0; z < 5; z++) {
            int currentLayer = z + row * 5;
            SetColor(15, 0);
            std::cout << "Layer " << currentLayer << ":           ";
        }
        std::cout << std::endl;

        // Print layer contents
        for (int x = 0; x < 5; x++) {
            for (int z = 0; z < 5; z++) {
                int currentLayer = z + row * 5;
                for (int y = 0; y < 5; y++) {
                    // Print player and computer positions with different colors
                    if (x == player.getX() && y == player.getY() && currentLayer == player.getZ()) {
                        SetColor(13, 0);
                        std::cout << setw(2) << " P ";
                    } else if (x == computer.getX() && y == computer.getY() && currentLayer == computer.getZ()) {
                        SetColor(13, 0);
                        std::cout << setw(2) << " C ";
                    } else {
                        // Print other field values with appropriate colors
                        int fieldValue = field.at(x).at(y).at(currentLayer);
                        if (fieldValue == -100) {
                                SetColor(10, 0);
                            std::cout << setw(2) << " X ";
                        } else {
                            SetColor(11, 0);
                            std::cout << setw(2) << fieldValue << " ";
                        }
                    }
                }
                std::cout << "   ";
                SetColor(15, 0);
            }
            std::cout << std::endl;
        }
    }
}

std::vector<int> World::getFieldValuesAt(int x, int y) {
    return field.at(x).at(y);
}

void World::setFieldAt(int x, int y, int z, int value) {
    field.at(x).at(y).at(z) = value;
}

int World::getFieldAt(int x, int y, int z) {
    return field.at(x).at(y).at(z);
}

// Function to rearrange (sort) the layers of the field based on their sums in descending order
void World::SortLayersDescending() {
    std::cout << "Sorting Layers Descending" << endl;

    // Create a vector to store the sums of each layer
    std::vector<int> layerSums(10, 0);

    // Calculate the sums of each layer
    for (int z = 0; z < 10; z++) {
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                int fieldValue = field.at(x).at(y).at(z);
                if (fieldValue != -100) {
                    layerSums[z] += fieldValue;
                }
            }
        }
    }

    // Create a vector to store layer indices based on their sums
    std::vector<int> layerIndices(10);

    // Fill layerIndices with increasing integer values from 0 to 9 using std::iota
    std::iota(layerIndices.begin(), layerIndices.end(), 0);

    // Sort the layerIndices in ascending order of their sums using std::sort and a custom comparison function
    std::sort(layerIndices.begin(), layerIndices.end(), [&layerSums](int a, int b) {
        return layerSums[a] < layerSums[b];
    });

    // The rearrangeLayers() function takes the sorted layerIndices vector as an input and rearranges the layers in the field accordingly.
    rearrangeLayers(layerIndices);
}

// Function to sort the layers in ascending order of their sums
void World::sortLayersAscending() {
    std::cout << "Sorting Layers ascending" << endl;

    // Create a vector to store the sums of each layer
    std::vector<int> layerSums(10, 0);

    // Calculate the sums of each layer
    for (int z = 0; z < 10; z++) {
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                int fieldValue = field.at(x).at(y).at(z);
                if (fieldValue != -100) {
                    layerSums[z] += fieldValue;
                }
            }
        }
    }

    // Create a vector to store layer indices
    std::vector<int> layerIndices(10);

    // Fill layerIndices with increasing integer values from 0 to 9 using std::iota
    std::iota(layerIndices.begin(), layerIndices.end(), 0);

    // sorts the elements in layerindices vector and captures the layerSums vector by reference and takes two integer arguments a and b.
    // The lambda function returns true if the value of layerSums[a] is greater than the value of layerSums[b],
    //and false otherwise. This custom comparison function tells std::sort how to compare the elements in the layerIndices vector when sorting.
    std::sort(layerIndices.begin(), layerIndices.end(), [&layerSums](int a, int b) {
        return layerSums[a] > layerSums[b];
    });

    // Rearrange the layers according to the sorted layerIndices
    rearrangeLayers(layerIndices);
}

void World::shuffleLayers() {
    std::cout << "Shuffe Layers" << endl;
    // Create a vector to store layer indices
    std::vector<int> layerIndices(10);

    // Fill layerIndices with increasing integer values from 0 to 9 using std::iota
    std::iota(layerIndices.begin(), layerIndices.end(), 0);

    // Seed a random number generator using the current time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);

    // Shuffle the layerIndices randomly using std::shuffle
    std::shuffle(layerIndices.begin(), layerIndices.end(), rng);


    // Rearrange the layers according to the shuffled layerIndices
    rearrangeLayers(layerIndices);
}

// Function to rearrange the layers of the field based on the given layer indices
void World::rearrangeLayers(const std::vector<int>& layerIndices) {
    // Create a temporary field to store the rearranged layers
    grid tempField = field;

    // Rearrange the layers in tempField according to the given layerIndices
    for (int z = 0; z < 10; z++) {
        int sourceZ = layerIndices[z];
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                tempField.at(x).at(y).at(z) = field.at(x).at(y).at(sourceZ);
            }
        }
    }

    // Update the field with the rearranged layers from tempField
    field = tempField;
}

