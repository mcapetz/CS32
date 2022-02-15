//
//  Peach.cpp
//  SuperPeachSisters
//
//  Created by Margaret Capetz on 2/14/22.
//  Copyright © 2022 UCLA Computer Science Department. All rights reserved.
//

#include "Peach.h"


Peach::Peach(int startX, int startY) : Actor(IID_PEACH, startX, startY, 0, 0, 1) {
    m_health = 1;
    starPower = false;
    shootPower = false;
    jumpPower = false;
}

void Peach::doSomething() {
    if(!isAlive()) return;
    //check temp invincibility
    //check recharge
    //check overlap
    //check jump
    //check falling
    int key = 0;
    //getKey(key); <-- how to access??
    if(key == KEY_PRESS_LEFT) {
        setDirection(left);
        int targetX = getX() - 4;
        int targetY = getY();
        //check if there is an object
        //if so, bonk
        moveTo(targetX, targetY);
    }
    if(key == KEY_PRESS_RIGHT) {
        setDirection(right);
        int targetX = getX() + 4;
        int targetY = getY();
        //check if there is an object
        //if so, bonk
        moveTo(targetX, targetY);
    }
}
