#ifndef BOGEYMAN_INCLUDED
#define BOGEYMAN_INCLUDED

#include "Monster.h"
#include <string>

class Bogeyman : public Monster {
public:
    Bogeyman(int startX, int startY);
    virtual ~Bogeyman() {}

    void attack(Actor* opponent) override;
    void takeTurn(Actor* player, std::vector<std::vector<char>>& map, const std::vector<Actor*>& actors) override;
};

#endif // BOGEYMAN_INCLUDED
