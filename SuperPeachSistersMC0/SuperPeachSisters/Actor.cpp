#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(StudentWorld* mg, int imageID, int startX, int startY, int dir, int depth, double size) : GraphObject(imageID, startX, startY, dir, depth, size) {
    m_isAlive = true;
    m_world = mg;
}

void Actor::doSomething() {
    
}

bool Actor::isAlive() {
    return m_isAlive;
}

StudentWorld* Actor::getWorld() {
    return m_world;
}


//BLOCK
Block::Block(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_BLOCK, startX, startY, 0, 2, 1) {
    
}

//PEACH
Peach::Peach(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_PEACH, startX, startY, 0, 0, 1) {
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
    int targetX = getX();
    int targetY = getY();
    if(getWorld()->getKey(key)) {
        switch(key) {
            case KEY_PRESS_LEFT:
                setDirection(left);
                targetX -= 4;
                if(getWorld()->isBlockingObjectAt(targetX, targetY)) {
                    //bonk
                    //cause a bonk() method in the target object to be called
                }
                else {
                    moveTo(targetX, targetY);
                }
                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                targetX += 4;
                if(getWorld()->isBlockingObjectAt(targetX, targetY)) {
                    //bonk
                }
                else {
                    moveTo(targetX, targetY);
                }
                break;
//            case KEY_PRESS_UP:
//                setDirection(right);
//                targetY += 4;
//                if(getWorld()->isBlockingObjectAt(targetX, targetY)) {
//                    //bonk
//                }
//                else {
//                    moveTo(targetX, targetY);
//                }
//                break;
//            case KEY_PRESS_DOWN:
//                setDirection(right);
//                targetY -= 4;
//                if(getWorld()->isBlockingObjectAt(targetX, targetY)) {
//                    //bonk
//                }
//                else {
//                    moveTo(targetX, targetY);
//                }
//                break;
        }
    }
}
