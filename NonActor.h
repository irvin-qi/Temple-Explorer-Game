//
//  NonActor.h
//  CS32 Project 3
//
//  Created by Irvin Qi on 5/21/24.
//

#ifndef NonActor_h
#define NonActor_h

#include <stdio.h>
#include <vector>

class NonActor {
public:
    int x, y; // NonActor's position

    NonActor(int startX, int startY);
    virtual ~NonActor() {}
    bool canPlaceOn(int newX, int newY, const std::vector<std::vector<char>>& map, const std::vector<NonActor*>& nonActors) const;
};

#endif /* NonActor_h */
