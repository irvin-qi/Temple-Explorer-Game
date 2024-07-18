#include "Level.h"
#include "utilities.h"
#include <iostream>

Level::Level() {
    initializeMap();
}

Level::~Level() {
    for (Monster* monster : monsters) {
        delete monster;
    }
    monsters.clear();
    for (Weapon* weapon : weapons) {
        delete weapon;
    }
    weapons.clear();
}

void Level::initializeMap() {
    map = std::vector<std::vector<char>>(18, std::vector<char>(70, '#'));
}

bool Level::overlap(const std::vector<Room>& rooms, const Room& room) const {
    for (const Room& existing : rooms) {
        if (room.x < existing.x + existing.width + 1 &&
            room.x + room.width + 1 > existing.x &&
            room.y < existing.y + existing.height + 1 &&
            room.y + room.height + 1 > existing.y)
            return true;
    }
    return false;
}

void Level::createRooms(int numRooms) {
    while (rooms.size() < numRooms) {
        int width = randInt(4, 10);
        int height = randInt(4, 6);
        int x = randInt(1, 70 - width - 1);
        int y = randInt(1, 18 - height - 1);
        Room newRoom(x, y, width, height);
        if (!overlap(rooms, newRoom)) {
            rooms.push_back(newRoom);
            for (int i = newRoom.y; i < newRoom.y + newRoom.height; ++i) {
                for (int j = newRoom.x; j < newRoom.x + newRoom.width; ++j) {
                    map[i][j] = ' ';
                }
            }
        }
    }
}

void Level::placeStaircase() {
    if (!rooms.empty()) {
        Room& lastRoom = rooms.back();
        int stairX, stairY;
        do {
            stairX = lastRoom.x + randInt(0, lastRoom.width - 1);
            stairY = lastRoom.y + randInt(0, lastRoom.height - 1);
        } while (map[stairY][stairX] != ' ');
        staircase = Staircase(stairX, stairY);
        map[stairY][stairX] = '>';
    }
}

void Level::placeIcon() {
    if (!rooms.empty()) {
        Room& lastRoom = rooms.back();
        int iconX, iconY;
        do {
            iconX = lastRoom.x + randInt(0, lastRoom.width - 1);
            iconY = lastRoom.y + randInt(0, lastRoom.height - 1);
        } while (map[iconY][iconX] != ' ');
        icon = Icon(iconX, iconY);
        map[iconY][iconX] = '&';
    }
}

void Level::placeMonsters(int levelNumber) {
    int numMonsters = randInt(2, 5 * (levelNumber + 1) + 1);
    for (int i = 0; i < numMonsters; ++i) {
        int monsterX, monsterY;
        do {
            monsterX = randInt(1, 68);
            monsterY = randInt(1, 16);
        } while (map[monsterY][monsterX] != ' ');
        if (levelNumber >= 3) {
            int monsterSpawned = randInt(1, 4);
            switch (monsterSpawned) {
                case 1: {
                    Monster* bogeyman = new Bogeyman(monsterX, monsterY);
                    monsters.push_back(bogeyman);
                    actors.push_back(bogeyman);
                    break;
                }
                case 2: {
                    Monster* dragon = new Dragon(monsterX, monsterY);
                    monsters.push_back(dragon);
                    actors.push_back(dragon);
                    break;
                }
                case 3: {
                    Monster* goblin = new Goblin(monsterX, monsterY);
                    monsters.push_back(goblin);
                    actors.push_back(goblin);
                    break;
                }
                case 4: {
                    Monster* snakewoman = new Snakewoman(monsterX, monsterY);
                    monsters.push_back(snakewoman);
                    actors.push_back(snakewoman);
                    break;
                }
                default:
                    break;
            }
        } 
        else if (levelNumber >= 2) {
            int monsterSpawned = randInt(1, 3);
            switch (monsterSpawned) {
                case 1: {
                    Monster* bogeyman = new Bogeyman(monsterX, monsterY);
                    monsters.push_back(bogeyman);
                    actors.push_back(bogeyman);
                    break;
                }
                case 2: {
                    Monster* goblin = new Goblin(monsterX, monsterY);
                    monsters.push_back(goblin);
                    actors.push_back(goblin);
                    break;
                }
                case 3: {
                    Monster* snakewoman = new Snakewoman(monsterX, monsterY);
                    monsters.push_back(snakewoman);
                    actors.push_back(snakewoman);
                    break;
                }
                default:
                    break;
            }
        }
        else if (levelNumber >= 0) {
            int monsterSpawned = randInt(1, 2);
            switch (monsterSpawned) {
                case 1: {
                    Monster* snakewoman = new Snakewoman(monsterX, monsterY);
                    monsters.push_back(snakewoman);
                    actors.push_back(snakewoman);
                    break;
                }
                case 2: {
                    Monster* goblin = new Goblin(monsterX, monsterY);
                    monsters.push_back(goblin);
                    actors.push_back(goblin);
                    break;
                }
                default:
                    break;
            }
        }
    }
}

void Level::placeObjects() {
    int numObjects = randInt(2, 3);
    for (int i = 0; i < numObjects; i++) {
        int objectX, objectY;
        do {
            objectX = randInt(1, 68);
            objectY = randInt(1, 16);
        } while (map[objectY][objectX] != ' ');
        int objectSpawned = randInt(1, 6);
        switch (objectSpawned) {
            case 1: {
                Weapon* mace = new Mace(objectX, objectY);
                weapons.push_back(mace);
                map[objectY][objectX] = ')';
                break;
            }
            case 2: {
                Weapon* shortSword = new ShortSword(objectX, objectY);
                weapons.push_back(shortSword);
                map[objectY][objectX] = ')';
                break;
            }
            case 3: {
                Weapon* longSword = new LongSword(objectX, objectY);
                weapons.push_back(longSword);
                map[objectY][objectX] = ')';
                break;
            }
            case 4: {
                Weapon* scrollOfArmor = new ScrollOfArmor(objectX, objectY);
                weapons.push_back(scrollOfArmor);
                map[objectY][objectX] = '?';
                break;
            }
            case 5: {
                Weapon* scrollofStrength = new ScrollOfStrength(objectX, objectY);
                weapons.push_back(scrollofStrength);
                map[objectY][objectX] = '?';
                break;
            }
            case 6: {
                Weapon* scrollofDexterity = new ScrollOfDexterity(objectX, objectY);
                weapons.push_back(scrollofDexterity);
                map[objectY][objectX] = '?';
                break;
            }
        }
    }
}

void Level::removeObjects(int x, int y) {
    map[y][x] = ' ';
}

void Level::createCorridors() {
    for (size_t i = 1; i < rooms.size(); ++i) {
        int x1 = rooms[i].x + rooms[i].width / 2;
        int y1 = rooms[i].y + rooms[i].height / 2;
        int x2 = rooms[i - 1].x + rooms[i - 1].width / 2;
        int y2 = rooms[i - 1].y + rooms[i - 1].height / 2;

        while (x1 != x2 || y1 != y2) {
            if (x1 != x2) {
                if (x1 < x2) ++x1;
                else --x1;
            } else if (y1 != y2) {
                if (y1 < y2) ++y1;
                else --y1;
            }
            if (x1 >= 0 && x1 < 70 && y1 >= 0 && y1 < 18) {
                map[y1][x1] = ' ';
            }
        }
    }
}

void Level::display() const {
    for (const auto& row : map) {
        for (char tile : row) {
            std::cout << tile;
        }
        std::cout << std::endl;
    }
}

