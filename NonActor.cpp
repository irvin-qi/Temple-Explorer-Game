//
//  NonActor.cpp
//  CS32 Project 3
//
//  Created by Irvin Qi on 5/21/24.
//
#include "NonActor.h"

NonActor::NonActor(int startX, int startY) : x(startX), y(startY) {}

bool NonActor::canPlaceOn(int newX, int newY, const std::vector<std::vector<char>>& map, const std::vector<NonActor*>& nonActors) const {
    // Check if the new position is walkable
    if (map[newY][newX] != ' ') {
        return false;
    }
    // Check if the new position is occupied by another non-actor
    for (const NonActor* nonActor : nonActors) {
        if (nonActor->x == newX && nonActor->y == newY) {
            return false;
        }
    }
    return true;
}
