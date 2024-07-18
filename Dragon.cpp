//
//  Dragon.cpp
//  CS32 Project 3
//
//  Created by Irvin Qi on 5/27/24.
//

#include "Dragon.h"
#include "Level.h"
#include "utilities.h"
#include <iostream>

Dragon::Dragon(int startX, int startY)
    : Monster(startX, startY, randInt(20, 25), 4, 4, 4) {
    type = "Dragon";
}

void Dragon::attack(Actor* opponent) {
    int attackerPoints = dexterity + strength;
    int defenderPoints = opponent->dexterity + opponent->armor;
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
        int damage = randInt(0, strength - 1);
        opponent->hitPoints -= damage;
        message = "The Dragon swings long sword at Player and hits. \n";
        if (opponent->hitPoints <= 0) {
            message = "The Dragon kills the Player. \n";
        }
    } 
    else {
        message = "The Dragon swings long sword at Player and misses. \n";
    }
}

void Dragon::takeTurn(Actor* player, std::vector<std::vector<char>>& map, const std::vector<Actor*>& actors) {
    return;
}
