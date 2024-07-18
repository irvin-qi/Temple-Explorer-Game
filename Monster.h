#ifndef MONSTER_INCLUDED
#define MONSTER_INCLUDED

#include "Actor.h"
#include <string>

class Monster : public Actor {
public:    
    Monster(int startX, int startY, int hp, int armor, int strength, int dex);
    virtual ~Monster() {}

    virtual void takeTurn(Actor* player, std::vector<std::vector<char>>& map, const std::vector<Actor*>& actors) = 0; 
    bool isNextToPlayer(Actor* player) const;
};

#endif // MONSTER_INCLUDED
