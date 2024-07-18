#ifndef SNAKEWOMAN_H
#define SNAKEWOMAN_H

#include "Monster.h"
#include "utilities.h"
#include <string>

class Snakewoman : public Monster {
public:
    Snakewoman(int startX, int startY);

    void attack(Actor* opponent) override;
    void takeTurn(Actor* player, std::vector<std::vector<char>>& map, const std::vector<Actor*>& actors) override;
};

#endif // SNAKEWOMAN_H
