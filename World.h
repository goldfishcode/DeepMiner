#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <iostream>
#include "Player.h"
#include <functional>



// World.h
// World.h

class Player;
class World {
public:
    World();
   void PrintWorld(const Player& player, const Player& computer);
    std::vector<int> getFieldValuesAt(int x, int y);
    void setFieldAt(int x, int y, int z, int value); // Add setFieldAt function
     int getFieldAt(int x, int y, int z);
     void rearrangeLayers(const std::vector<int>& layerIndices);
     void SortLayersDescending();
     void shuffleLayers();
     void sortLayersAscending();


private:
    using grid = std::vector<std::vector<std::vector<int>>>;
    grid field;
};

#endif // WORLD_HPP
