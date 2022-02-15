#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, int dir, int depth, double size) : GraphObject(imageID, startX, startY, dir, depth, size) {
    m_isAlive = true;
}

void Actor::doSomething() {
    
}

bool Actor::isAlive() {
    return m_isAlive;
}


//BLOCK
Block::Block(int startX, int startY) : Actor(IID_BLOCK, startX, startY, 0, 2, 1) {
    
}

//PEACH
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
    int key;
    m_world->getKey(key);
    if(key == KEY_PRESS_LEFT) {
        setDirection(left);
        int targetX = getX() - 4;
        int targetY = getY();
        if(m_world->isBlockingObjectAt(targetX, targetY)) {
            //bonk
            //cause a bonk() method in the target object to be called
        }
        else {
            moveTo(targetX, targetY);
        }
    }
    if(key == KEY_PRESS_RIGHT) {
        setDirection(right);
        int targetX = getX() + 4;
        int targetY = getY();
        if(m_world->isBlockingObjectAt(targetX, targetY)) {
            //bonk
        }
        else {
            moveTo(targetX, targetY);
        }
    }
}
