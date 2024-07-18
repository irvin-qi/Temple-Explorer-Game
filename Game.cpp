#include "Game.h"
#include "utilities.h"
#include <iostream>

Game::Game(int goblinSmellDistance) : goblinSmellDistance(goblinSmellDistance) {
    player = nullptr;
    currentLevelIndex = 0;
    for (int i = 0; i < 5; ++i) {
        createLevel(i);
    }
    if (!levels.empty() && !levels[0]->rooms.empty()) {
        Room& firstRoom = levels[0]->rooms[0];
        player = new Player(firstRoom.x + firstRoom.width / 2, firstRoom.y + firstRoom.height / 2);
    }
}

Game::~Game() {
    delete player;
    for (Level* level : levels) {
        delete level;
    }
    levels.clear();
}

void Game::createLevel(int levelNumber) {
    Level* newLevel = new Level();
    int numRooms = randInt(4, 8);
    newLevel->createRooms(numRooms);
    newLevel->createCorridors();
    if (levelNumber < 4) {
        newLevel->placeStaircase();
    } else {
        newLevel->placeIcon();
    }
    newLevel->placeMonsters(levelNumber);
    newLevel->placeObjects();
    newLevel->actors.push_back(player);
    for (Monster* monster : newLevel->monsters) {
        newLevel->actors.push_back(monster);
    }
    levels.push_back(newLevel);
}

void Game::placeActors() {
    levels[currentLevelIndex]->map[player->y][player->x] = '@';
    for (Monster* monster : levels[currentLevelIndex]->monsters) {
        if (monster->type == "Bogeyman") {
            levels[currentLevelIndex]->map[monster->y][monster->x] = 'B';
        }
        if (monster->type == "Dragon") {
            levels[currentLevelIndex]->map[monster->y][monster->x] = 'D';
        }
        if (monster->type == "Goblin") {
            levels[currentLevelIndex]->map[monster->y][monster->x] = 'G';
        }
        if (monster->type == "Snakewoman") {
            levels[currentLevelIndex]->map[monster->y][monster->x] = 'S';
        }
    }
}

void Game::handlePlayerMove(char direction) {
    int newX = player->x, newY = player->y;
    switch (direction) {
        case ARROW_LEFT:  --newX; break;
        case ARROW_RIGHT: ++newX; break;
        case ARROW_UP:    --newY; break;
        case ARROW_DOWN:  ++newY; break;
    }
    
    for (auto it = levels[currentLevelIndex]->monsters.begin(); it != levels[currentLevelIndex]->monsters.end(); ++it) {
        Monster* monster = *it;
        if (monster->x == newX && monster->y == newY) {
            player->attack(monster);
            monster->attack(player);
            if (monster->hitPoints <= 0) {
                int monsterX = monster->x;
                int monsterY = monster->y;
                it = levels[currentLevelIndex]->monsters.erase(it);
                delete monster;
                levels[currentLevelIndex]->map[monsterY][monsterX] = ' ';
            }
            return;
        }
    }
        if (player->canMoveTo(newX, newY, levels[currentLevelIndex]->map, { player })) {
            if ((player->previousTile == ')' || player->previousTile == '?') && pickedUp == true) {
                levels[currentLevelIndex]->map[player->y][player->x] = ' ';
                pickedUp = false;
        }
        else {
            levels[currentLevelIndex]->map[player->y][player->x] = player->previousTile;
        }
        player->previousTile = levels[currentLevelIndex]->map[newY][newX];
        player->move(direction);
        player->message.clear();
    }
}


void Game::handleMonsterTurns() {
    for (Monster* monster : levels[currentLevelIndex]->monsters) {
        if (monster->x != player->x || monster->y != player->y) {
            levels[currentLevelIndex]->map[monster->y][monster->x] = monster->previousTile;
            monster->takeTurn(player, levels[currentLevelIndex]->map, { player });
        }
    }
}

void Game::handleDescend() {
    if (player->x == levels[currentLevelIndex]->staircase.x && player->y == levels[currentLevelIndex]->staircase.y) {
        if (currentLevelIndex < 4) {
            currentLevelIndex++;
            Room& firstRoom = levels[currentLevelIndex]->rooms[0];
            player->x = firstRoom.x + firstRoom.width / 2;
            player->y = firstRoom.y + firstRoom.height / 2;
            player->previousTile = ' ';
        }
    }
}

void Game::handlePickup() {
    if (player->x == levels[currentLevelIndex]->icon.x && player->y == levels[currentLevelIndex]->icon.y) {
        std::cout << "You pick up the golden idol" << std::endl;
        std::cout << "Congratulations, you won!" << std::endl;
    }
}

void Game::pickUpWeapon() {
    for (auto it = levels[currentLevelIndex]->weapons.begin(); it != levels[currentLevelIndex]->weapons.end(); ++it) {
        Weapon* weapon = *it;
        if (weapon->getX() == player->x && weapon->getY() == player->y) {
            player->pickUpWeapon(weapon);
            pickedUp = true;
            levels[currentLevelIndex]->map[weapon->getY()][weapon->getX()] = ' ';
            levels[currentLevelIndex]->weapons.erase(it);
            break;
        }
    }
}

void Game::displayStatusBar() const {
    std::cout << "Level: " << currentLevelIndex
              << ", Hit points: " << player->hitPoints
              << ", Armor: " << player->armor
              << ", Strength: " << player->strength
              << ", Dexterity: " << player->dexterity
              << std::endl;
    std::cout << player->message;
    for (Monster* monster : levels[currentLevelIndex]->monsters) {
        std::cout << monster->message;
    }
}

void Game::play() {
    while (true) {
        clearScreen();
        placeActors();
        levels[currentLevelIndex]->display();
        displayStatusBar();
        char action = getCharacter();
        player->healTick();
        if (action == 'i') {
            player->displayInventory();
        }
        if (action == 'w') {
            player->selectWeapon();
        }
        if (action == 'c') {
            player->cheat();
        }
        if (action == 'q') break;
        if (action == '>') {
            handleDescend();
        }
        else if (action == 'g') {
            handlePickup();
            pickUpWeapon();
        }
        else {
            handlePlayerMove(action);
        }
        handleMonsterTurns();
    }
}
