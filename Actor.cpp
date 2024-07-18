#include "Actor.h"

Actor::Actor(int startX, int startY, int hp, int armor, int strength, int dex)
    : x(startX), y(startY), hitPoints(hp), armor(armor), strength(strength), dexterity(dex), previousTile(' ') {}

bool Actor::canMoveTo(int newX, int newY, const std::vector<std::vector<char>>& map, const std::vector<Actor*>& actors) const {
    if (newY < 0 || newY >= map.size() || newX < 0 || newX >= map[0].size()) {
        return false;
    }
    if (map[newY][newX] == '@' || map[newY][newX] == '#' || map[newY][newX] == 'D' || map[newY][newX] == 'B' || map[newY][newX] == 'G' || map[newY][newX] == 'S') {
        return false;
    }
    return true;
}

void Actor::move(char direction) {
    switch (direction) {
        case ARROW_LEFT:  --x; break;
        case ARROW_RIGHT: ++x; break;
        case ARROW_UP:    --y; break;
        case ARROW_DOWN:  ++y; break;
    }
}
