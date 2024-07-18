#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "Actor.h"
#include "Weapon.h"
#include "utilities.h"
#include <string>


class Player : public Actor {
public:
    Player(int startX, int startY);
    void attack(Actor* opponent) override;
    void pickUpWeapon(Weapon* weapon);
    Weapon* getCurrentWeapon() const;
    void displayInventory();
    void selectWeapon();
    void useScroll();
    void cheat();  
    void healTick();

private:
    std::vector<Weapon*> inventory;
    Weapon* currentWeapon = nullptr;
};

#endif // PLAYER_INCLUDED
