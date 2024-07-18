#include "Snakewoman.h"
#include "Level.h"
#include <iostream>

Snakewoman::Snakewoman(int startX, int startY)
    : Monster(startX, startY, randInt(3, 6), 3, 2, 3) {
        type = "Snakewoman";
    }

void Snakewoman::attack(Actor* opponent) {
    int attackerPoints = dexterity;
    int defenderPoints = opponent->dexterity + opponent->armor;
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
        int damage = randInt(0, strength - 1);
        opponent->hitPoints -= damage;
        message = "The Snakewoman strikes magic fangs at Player and hits.\n";
        if (opponent->hitPoints <= 0) {
            message = "The Snakewoman strikes magic fangs at Player dealing a final blow.\n";
        }
    } 
    else {
        message = "The Snakewoman strikes magic fangs at Player and misses.\n";
    }
}

void Snakewoman::takeTurn(Actor* player, std::vector<std::vector<char>>& map, const std::vector<Actor*>& actors) {
    if (!isNextToPlayer(player)) {
        int distanceToPlayer = abs(player->x - x) + abs(player->y - y);
        if (distanceToPlayer <= 3) {
            int deltaX = player->x - x;
            int deltaY = player->y - y;
            if (abs(deltaX) > abs(deltaY)) {
                if (deltaX > 0 && canMoveTo(x + 1, y, map, actors)) {
                    ++x;
                } 
                else if (deltaX < 0 && canMoveTo(x - 1, y, map, actors)) {
                    --x;
                }
            } 
            else {
                if (deltaY > 0 && canMoveTo(x, y + 1, map, actors)) {
                    ++y;
                } 
                else if (deltaY < 0 && canMoveTo(x, y - 1, map, actors)) {
                    --y;
                }
            }
            map[y][x] = 'S';
        }
    }
}
