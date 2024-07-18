#ifndef ACTOR_INCLUDED
#define ACTOR_INCLUDED

#include <vector>
#include "utilities.h"
#include <string>

class Actor {
public:
    int x, y;
    int hitPoints;
    int armor;
    int strength;
    int dexterity;
    char previousTile;
    std::string message;
    std::string type;

    Actor(int startX, int startY, int hp, int armor, int strength, int dex);
    virtual ~Actor() {}

    bool canMoveTo(int newX, int newY, const std::vector<std::vector<char>>& map, const std::vector<Actor*>& actors) const;
    void move(char direction);
    virtual void attack(Actor* opponent) = 0;
};

#endif // ACTOR_INCLUDED

