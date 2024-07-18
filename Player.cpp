#include "Player.h"
#include <iostream>

Player::Player(int startX, int startY)
    : Actor(startX, startY, 20, 2, 2, 2) {
    Weapon* shortSword = new Weapon("short sword", "weapon", 0, 2, 0, 0, startX, startY);
    inventory.push_back(shortSword);
    currentWeapon = shortSword;
}

void Player::attack(Actor* opponent) {
    if (currentWeapon) {
        int attackerPoints = dexterity + currentWeapon->getDexterityBonus();
        int defenderPoints = opponent->dexterity + opponent->armor;
        if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
            int damage = randInt(0, strength + currentWeapon->getDamageAmount() - 1);
            opponent->hitPoints -= damage;
            if (opponent->hitPoints <= 0) {
                message += "\nPlayer swings " + currentWeapon->getName() + " at " + opponent->type + " dealing a final blow.\n";
            }
            else {
                message = "\nPlayer swings " + currentWeapon->getName() + " at " + opponent->type + " and hits.\n";
            }
        }
        else {
            message = "\nPlayer swings " + currentWeapon->getName() + " at " + opponent->type + " and misses.\n";
        }
    } 
    else {
        return;
    }
}

void Player::pickUpWeapon(Weapon* weapon) {
    inventory.push_back(weapon);
    message = "\nYou pick up a " + weapon->getName() + "\n";
}

Weapon* Player::getCurrentWeapon() const {
    return currentWeapon;
}

void Player::displayInventory(){
    clearScreen();
    std::cout << "Inventory:" << std::endl;
    char label = 'a';
    for (const Weapon* weapon : inventory) {
        std::cout << label << ". " << weapon->getName() << std::endl;
        label++;
    }
    getCharacter();
}

void Player::selectWeapon(){
    clearScreen();
    std::cout << "Inventory:" << std::endl;
    char label = 'a';
    for (const Weapon* weapon : inventory) {
        std::cout << label << ". " << weapon->getName() << std::endl;
        label++;
    }
    char choice = getCharacter();
    int index = choice - 'a';
    if (index >= 0 && index < 26) {
        if (inventory[index]->getType() == "weapon") {
            currentWeapon = inventory[index];
            std::cout << "\nYou are wielding the " << currentWeapon->getName() << std::endl;
        }
        if (inventory[index]->getType() == "scroll") {
            if (inventory[index]->getName() == "scroll of improve armor") {
                armor += inventory[index]->armorIncrease;
            }
            if (inventory[index]->getName() == "scroll of raised strength") {
                strength += inventory[index]->strengthIncrease;
            }
            if (inventory[index]->getName() == "scroll of enhance dexterity") {
                dexterity += inventory[index]->getDexterityBonus();
            }
            std::cout << "\nYou used " << inventory[index]->getName() << std::endl;
            inventory.erase(inventory.begin() + index);
        }
    } else {
        return;
    }
}

void Player::cheat() {
    strength = 9;
    hitPoints = 50;
}

void Player::healTick() {
    if (randInt(1, 10) == 5 && hitPoints < 20) {
        hitPoints++;
    }
}
