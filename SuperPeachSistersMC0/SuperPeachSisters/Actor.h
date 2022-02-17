#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor: public GraphObject {
public:
    Actor(StudentWorld* mg, int imageID, int startX, int startY, int dir = 0, int depth = 0, double size = 1.0);
    virtual void doSomething();
    bool isBlockingObjectAt(int x, int y);
    bool isAlive();
    StudentWorld* getWorld();
private:
    bool m_isAlive;
    StudentWorld* m_world;
};


//BLOCK
class Block: public Actor {
public:
    Block(StudentWorld* mg, int startX, int startY);
private:
};

//PEACH
class Peach: public Actor {
public:
    Peach(StudentWorld* mg, int startX, int startY);
    virtual void doSomething();
    
private:
    int m_health;
    bool starPower;
    bool shootPower;
    bool jumpPower;
};

//PIPE
class Pipe: public Actor {
public:
    Pipe(StudentWorld* mg, int startX, int startY);
};

//FLAG
class Flag: public Actor {
public:
    Flag(StudentWorld* mg, int startX, int startY);
    virtual void doSomething();
};

//ENEMY
class Enemy: public Actor {
public:
    Enemy(StudentWorld* mg, int imageID, int startX, int startY);
    virtual void doSomething();
private:
};

//GOOMBA
class Goomba: public Enemy {
public:
    Goomba(StudentWorld* mg, int startX, int startY);
private:
};

//KOOPA
class Koopa: public Enemy {
public:
    Koopa(StudentWorld* mg, int startX, int startY);
private:
};

#endif // ACTOR_H_
