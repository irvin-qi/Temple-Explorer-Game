#include "Weapon.h"

Weapon::Weapon(const std::string& name, const std::string& type, int dexterityBonus, int damageAmount, int armorIncrease, int strengthIncrease, int startX, int startY)
    : name(name), type(type), dexterityBonus(dexterityBonus), damageAmount(damageAmount), armorIncrease(armorIncrease), strengthIncrease(strengthIncrease), x(startX), y(startY) {}

Weapon::~Weapon() {}

std::string Weapon::getName() const {
    return name;
}

std::string Weapon::getType() const {
    return type;
}

int Weapon::getDexterityBonus() const {
    return dexterityBonus;
}

int Weapon::getDamageAmount() const {
    return damageAmount;
}

int Weapon::getX() const {
    return x;
}

int Weapon::getY() const {
    return y;
}

void Weapon::setCoordinates(int newX, int newY) {
    x = newX;
    y = newY;
}

Mace::Mace(int startX, int startY)
    : Weapon("mace", "weapon", 0, 2, 0, 0, startX, startY) {}

ShortSword::ShortSword(int startX, int startY)
    : Weapon("short sword", "weapon", 0, 2, 0, 0, startX, startY) {}

LongSword::LongSword(int startX, int startY)
    : Weapon("long sword", "weapon", 2, 4, 0, 0, startX, startY) {}

MagicAxe::MagicAxe(int startX, int startY)
    : Weapon("magic axe", "weapon", 5, 5, 0, 0, startX, startY) {}

MagicFangsOfSleep::MagicFangsOfSleep(int startX, int startY)
    : Weapon("magic fangs of sleep", "weapon", 3, 2, 0, 0, startX, startY) {}

bool MagicFangsOfSleep::putToSleep() const {
    return (randInt(1, 5) == 1);
}

int MagicFangsOfSleep::getSleepTime() const {
    return randInt(2, 6);
}

ScrollOfArmor::ScrollOfArmor(int startX, int startY) 
    : Weapon("scroll of improve armor", "scroll", 0, 0, randInt(1, 3), 0, startX, startY) {}

ScrollOfStrength::ScrollOfStrength(int startX, int startY)
    : Weapon("scroll of raised strength", "scroll", 0, 0, 0, randInt(1, 3), startX, startY) {}

ScrollOfDexterity::ScrollOfDexterity(int startX, int startY)
    : Weapon("scroll of enhance dexterity", "scroll", 1, 0, 0, 0, startX, startY) {}
