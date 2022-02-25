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
    bool isAlive() const;
    void setDead();
    StudentWorld* getWorld() const;
    virtual bool isStatic();
    virtual bool isEnemy();
    virtual bool isPlayer();
    bool overlappingPeach() const;
    bool reachedFlagOrMario();
private:
    bool m_isAlive;
    StudentWorld* m_world;
};

class Obstacle: public Actor {
public:
    Obstacle(StudentWorld* mg, int imageID, int startX, int startY);
    virtual bool isStatic();
};


//BLOCK
class Block: public Obstacle {
public:
    Block(StudentWorld* mg, int startX, int startY);
    virtual void bonk();
    bool isHoldingGoodie() const;
    void setIsHoldingGoodie(bool b);
    bool powerUp();
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
};

//GOODIES
class Goodie: public Actor {
public:
    Goodie(StudentWorld *mg, int imageID, int startX, int startY);
    bool powerUpPeach(int score);
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
    bool isStarPower() const;
    bool isShootPower() const;
    bool isJumpPower() const;
    void setStarPower(bool b);
    void setShootPower(bool b);
    void setJumpPower(bool b);
    virtual bool isPlayer();
    virtual void bonk();
    void setHealth(int x);
    void setTempInvincibility(int x);
    void setStarInvincibility(int x);
private:
    int m_health;
    bool starPower;
    bool shootPower;
    bool jumpPower;
    bool tempInvincibility;
    int remaining_jump_distance;
    int time_to_recharge_before_next_fire;
    int temp_invincibility;
    int star_invincibility;
};

//PIPE
class Pipe: public Obstacle {
public:
    Pipe(StudentWorld* mg, int startX, int startY);
};

//FLAG

class levelEnder: public Actor {
public:
    levelEnder(StudentWorld* mg, int imageID, int startX, int startY);
    virtual void endLevel() = 0;
private:
    virtual void doSomething();

};

class Flag: public levelEnder {
public:
    Flag(StudentWorld* mg, int startX, int startY);
    virtual void endLevel();
};

class Mario: public levelEnder {
public:
    Mario(StudentWorld* mg, int startX, int startY);
    virtual void endLevel();
};

//ENEMY
class Enemy: public Actor {
public:
    Enemy(StudentWorld* mg, int imageID, int startX, int startY);
    Peach* getPlayer();
    virtual void doEnemy();
    virtual bool isEnemy();
    virtual void enemyBonk();
    void enemyOverlappingPeach();
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
