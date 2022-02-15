#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


Actor::Actor(int imageID, int startX, int startY, int dir, int depth, double size) : GraphObject(imageID, startX, startY, dir, depth, size) {
    m_isAlive = true;
}

void Actor::doSomething() {
    
}

void Actor::bonk() {
    
}

bool Actor::isBlockingObjectAt(int x, int y) {
    return x == getX() && y == getY();
}

bool Actor::isAlive() {
    return m_isAlive;
}
