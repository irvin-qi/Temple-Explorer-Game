#include "Monster.h"
#include <iostream>

Monster::Monster(int startX, int startY, int hp, int armor, int strength, int dex)
    : Actor(startX, startY, hp, armor, strength, dex) {}

bool Monster::isNextToPlayer(Actor* player) const {
    return (abs(player->x - x) + abs(player->y - y) == 1);
}
