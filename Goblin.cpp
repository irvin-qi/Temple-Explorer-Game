#include "Goblin.h"
#include "Level.h"
#include <iostream>
#include <algorithm>

Goblin::Goblin(int startX, int startY)
    : Monster(startX, startY, randInt(15, 20), 3, 1, 1) {
    type = "Goblin";
}

void Goblin::attack(Actor* opponent) {
    int attackerPoints = dexterity;
    int defenderPoints = opponent->dexterity + opponent->armor;
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
        int damage = randInt(0, strength - 1);
        opponent->hitPoints -= damage;
        message = "The Goblin slashes short sword at Player and hits. \n";
        if (opponent->hitPoints <= 0) {
            message = "The Goblin slashes short sword at Player dealing a final blow. \n";
        }
    } else {
        message = "The Goblin slashes short sword at Player and misses. \n";
    }
}

bool Goblin::findPathToPlayer(int curX, int curY, int targetX, int targetY, const std::vector<std::vector<char>>& map, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& path) {
    if (curX == targetX && curY == targetY) {
        path.push_back(std::make_pair(curX, curY));
        return true;
    }
    visited[curY][curX] = true;
    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::vector<std::pair<int, int>> validMoves;
    for (size_t i = 0; i < directions.size(); ++i) {
        int newX = curX + directions[i].first;
        int newY = curY + directions[i].second;
        if (newX < 0 || newX >= map[0].size() || newY < 0 || newY >= map.size() || visited[newY][newX] || map[newY][newX] != ' ') {
            continue;
        }
        validMoves.push_back({newX, newY});
    }
    // Sort the valid moves based on their distance to the player
    std::sort(validMoves.begin(), validMoves.end(), [targetX, targetY](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        int distA = abs(a.first - targetX) + abs(a.second - targetY);
        int distB = abs(b.first - targetX) + abs(b.second - targetY);
        return distA < distB;
    });
    for (const auto& move : validMoves) {
        if (findPathToPlayer(move.first, move.second, targetX, targetY, map, visited, path)) {
            path.push_back(std::make_pair(curX, curY));
            return true;
        }
    }
    return false;
}

bool Goblin::findPath(Actor* player, const std::vector<std::vector<char>>& map, std::vector<std::pair<int, int>>& path) {
    int rows = 18;
    int cols = 70;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    if (findPathToPlayer(x, y, player->x, player->y, map, visited, path)) {
        std::reverse(path.begin(), path.end());
        return true;
    }
    return false;
}

void Goblin::takeTurn(Actor* player, std::vector<std::vector<char>>& map, const std::vector<Actor*>& actors) {
    if (!isNextToPlayer(player)) {
        std::vector<std::pair<int, int>> path;
        if (findPath(player, map, path) && path.size() > 1) {
            // Take one step towards the player
            std::pair<int, int> nextPosition = path[1];
            map[y][x] = ' ';
            x = nextPosition.first;
            y = nextPosition.second;
            map[y][x] = 'G';
        }
    }
}

