//
//  Dragon.h
//  CS32 Project 3
//
//  Created by Irvin Qi on 5/27/24.
//

#ifndef Dragon_h
#define Dragon_h

#include "Monster.h"
#include <string>

class Dragon : public Monster {
public:
    Dragon(int startX, int startY);
    virtual ~Dragon() {}

    void attack(Actor* opponent) override;
    void takeTurn(Actor* player, std::vector<std::vector<char>>& map, const std::vector<Actor*>& actors) override;
};


#endif /* Dragon_h */

