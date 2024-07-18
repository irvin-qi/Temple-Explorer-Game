#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <vector>
#include "Level.h"
#include "Player.h"
#include "Monster.h"
#include "Bogeyman.h"
#include <string>

class Game {
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
private:
    Player* player;
    std::vector<Level*> levels;
    int currentLevelIndex;
    int goblinSmellDistance;
    bool pickedUp;

    void createLevel(int levelNumber);
    void placeActors();
    void handlePlayerMove(char direction);
    void handleDescend();
    void handlePickup(); 
    void pickUpWeapon();
    void handleMonsterTurns();
    void displayStatusBar() const;
};

#endif // GAME_INCLUDED
