#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "utilities.h"
#include <string>

class Weapon {
public:
    Weapon(const std::string& name, const std::string& type, int dexterityBonus, int damageAmount, int armorIncrease, int strengthIncrease, int startX, int startY);
    virtual ~Weapon();

    std::string getName() const;
    std::string getType() const;
    int getDexterityBonus() const;
    int getDamageAmount() const;
    int getX() const;
    int getY() const;
    int armorIncrease;
    int strengthIncrease;
    void setCoordinates(int newX, int newY);

protected:
    std::string name;
    std::string type;
    int dexterityBonus;
    int damageAmount;
    int x, y; // Starting coordinates
};

class Mace : public Weapon {
public:
    Mace(int startX, int startY);
};

class ShortSword : public Weapon {
public:
    ShortSword(int startX, int startY);
};

class LongSword : public Weapon {
public:
    LongSword(int startX, int startY);
};

class MagicAxe : public Weapon {
public:
    MagicAxe(int startX, int startY);
};

class MagicFangsOfSleep : public Weapon {
public:
    MagicFangsOfSleep(int startX, int startY);

    bool putToSleep() const;
    int getSleepTime() const;
};

class ScrollOfArmor : public Weapon {
public:
    ScrollOfArmor(int startX, int startY);
};

class ScrollOfStrength : public Weapon {
public:
    ScrollOfStrength(int startX, int startY);
};

class ScrollOfDexterity : public Weapon {
public:
    ScrollOfDexterity(int startX, int startY);
};

#endif // WEAPON_H
