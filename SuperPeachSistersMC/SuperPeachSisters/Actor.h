#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject {
public:
    Actor(int imageID, int startX, int startY, int dir = 0, int depth = 0, double size = 1.0);
    virtual void doSomething();
    virtual void bonk();
    bool isBlockingObjectAt(int x, int y);
    bool isAlive();
private:
    bool m_isAlive;
};

#endif // ACTOR_H_
