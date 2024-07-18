#ifndef LEVEL_INCLUDED
#define LEVEL_INCLUDED

#include <vector>
#include "Room.h"
#include "Staircase.h"
#include "Icon.h"
#include "Bogeyman.h"
#include "Dragon.h"
#include "Goblin.h"
#include "Snakewoman.h"
#include "Weapon.h"
#include <string>

class Level {
public:
    std::vector<std::vector<char>> map;
    std::vector<Room> rooms;
    Staircase staircase;
    Icon icon;
    std::vector<Monster*> monsters;
    std::vector<Actor*> actors; // Add this to store all actors in the level
    std::vector<Weapon*> weapons;


    Level();
    ~Level();
    void createRooms(int numRooms);
    void createCorridors();
    void placeStaircase();
    void placeIcon();
    void placeMonsters(int levelNumber);
    void placeObjects();
    void removeObjects(int x, int y);
    bool overlap(const std::vector<Room>& rooms, const Room& room) const;
    void display() const;
private:
    void initializeMap();
};

#endif // LEVEL_INCLUDED
