//
//  Room.h
//  CS32 Project 3
//
//  Created by Irvin Qi on 5/20/24.
//

#ifndef Room_h
#define Room_h

#include <stdio.h>
#include <string>


class Room {
public:
    int x, y;
    int width, height;
    Room(int startX, int startY, int roomWidth, int roomHeight)
        : x(startX), y(startY), width(roomWidth), height(roomHeight) {}

    bool contains(int px, int py) const {
        return px >= x && px < x + width && py >= y && py < y + height;
    }
};

#endif /* Room_h */
