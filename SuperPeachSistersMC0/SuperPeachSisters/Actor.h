#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor: public GraphObject {
public:
    Actor(StudentWorld* mg, int imageID, int startX, int startY, int dir = 0, int depth = 0, double size = 1.0);
    virtual void doSomething();
    virtual void bonk();
    bool isAlive();
    void setDead();
    StudentWorld* getWorld();
    virtual bool isStatic();
    virtual bool isEnemy();
    virtual bool isPlayer();
    virtual bool isGoodie() {return false;}
private:
    bool m_isAlive;
    StudentWorld* m_world;
};


//BLOCK
class Block: public Actor {
public:
    Block(StudentWorld* mg, int startX, int startY);
    virtual bool isStatic();
    virtual void bonk();
    bool isHoldingGoodie();
    void setIsHoldingGoodie(bool b);
private:
    bool holdsGoodie;
};

class starBlock: public Block {
public:
    starBlock(StudentWorld* mg, int startX, int startY);
    virtual void bonk();
};

class mushroomBlock: public Block {
public:
    mushroomBlock(StudentWorld* mg, int startX, int startY);
    virtual void bonk();
};

class flowerBlock: public Block {
public:
    flowerBlock(StudentWorld* mg, int startX, int startY);
    virtual void bonk();
    virtual bool isGoodie() {return true;}
};

//GOODIES
class Goodie: public Actor {
public:
    Goodie(StudentWorld *mg, int imageID, int startX, int startY);
    void doGoodie();
};

class Star: public Goodie {
public:
    Star(StudentWorld *mg, int startX, int startY);
    virtual void doSomething();
};

class Mushroom: public Goodie {
public:
    Mushroom(StudentWorld *mg, int startX, int startY);
    virtual void doSomething();
};

class Flower: public Goodie {
public:
    Flower(StudentWorld *mg, int startX, int startY);
    virtual void doSomething();
};

//PEACH
class Peach: public Actor {
public:
    Peach(StudentWorld* mg, int startX, int startY);
    virtual void doSomething();
    bool isStarPower();
    bool isShootPower();
    bool isJumpPower();
    void setStarPower(bool b);
    void setShootPower(bool b);
    void setJumpPower(bool b);
    virtual bool isPlayer();
    virtual void bonk();
    void setHealth(int x);
private:
    int m_health;
    bool starPower;
    bool shootPower;
    bool jumpPower;
    int remaining_jump_distance;
    int time_to_recharge_before_next_fire;
    int temp_invincibility;
};

//PIPE
class Pipe: public Actor {
public:
    Pipe(StudentWorld* mg, int startX, int startY);
    virtual bool isStatic();
};

//FLAG
class Flag: public Actor {
public:
    Flag(StudentWorld* mg, int startX, int startY);
    virtual void doSomething();
};

class Mario: public Actor {
public:
    Mario(StudentWorld* mg, int startX, int startY);
    virtual void doSomething();
};

//ENEMY
class Enemy: public Actor {
public:
    Enemy(StudentWorld* mg, int imageID, int startX, int startY);
    Peach* getPlayer();
    virtual void doEnemy();
    virtual bool isEnemy();
    virtual void enemyBonk();
private:
    Peach* m_player;
};

//GOOMBA
class Goomba: public Enemy {
public:
    Goomba(StudentWorld* mg, int startX, int startY);
    virtual void doSomething();
    virtual void bonk();
private:
};

//KOOPA
class Koopa: public Enemy {
public:
    Koopa(StudentWorld* mg, int startX, int startY);
    virtual void doSomething();
    virtual void bonk();
private:
};

//PIRANHA
class Piranha: public Enemy {
public:
    Piranha(StudentWorld* mg, int startX, int startY);
    virtual void doSomething();
    virtual void bonk();
private:
    int m_firingDelay;
};

//PROJECTILE
class Projectile: public Actor {
public:
    Projectile(StudentWorld* mg, int imageID, int startX, int startY, int dir);
    void moveWithFalling();
};

class Shell: public Projectile {
public:
    Shell(StudentWorld* mg, int startX, int startY, int dir);
    virtual void doSomething();
};

class PeachFireball: public Projectile {
public:
    PeachFireball(StudentWorld* mg, int startX, int startY, int dir);
    virtual void doSomething();
};

class PiranhaFireball: public Projectile {
public:
    PiranhaFireball(StudentWorld* mg, int startX, int startY, int dir);
    virtual void doSomething();
};

#endif // ACTOR_H_
