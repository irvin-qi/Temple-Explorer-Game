#ifndef GOBLIN_H
#define GOBLIN_H

#include "Monster.h"
#include "utilities.h"
#include <vector>
#include <string>

class Goblin : public Monster {
public:
    Goblin(int startX, int startY);

    void attack(Actor* opponent) override;
    void takeTurn(Actor* player, std::vector<std::vector<char>>& map, const std::vector<Actor*>& actors) override;

private:
    bool findPathToPlayer(int curX, int curY, int targetX, int targetY, const std::vector<std::vector<char>>& map, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& path);
    bool findPath(Actor* player, const std::vector<std::vector<char>>& map, std::vector<std::pair<int, int>>& path);
};

#endif // GOBLIN_H
