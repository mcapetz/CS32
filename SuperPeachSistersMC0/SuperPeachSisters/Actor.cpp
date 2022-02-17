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
Block::Block(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_BLOCK, startX, startY, 0, 2, 1) {}

//PIPE
Pipe::Pipe(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_PIPE, startX, startY, 0, 2, 1) {
}

//FLAG
Flag::Flag(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_FLAG, startX, startY, 0, 1, 1) {}

void Flag::doSomething() {
    if(!isAlive()) return;
    
    //check if overlaps with peach
        //if so, increase score by 1000
        //set state to not alive
        //inform student world that level is complete
    
    //do not block other players from moving on it
}

//ENEMY
Enemy::Enemy(StudentWorld* mg, int imageID, int startX, int startY) : Actor(mg, imageID, startX, startY, 0, 1, 1) {};

void Enemy::doSomething() {
    if(!isAlive()) return;
    
    //check if overlapping with peach
    //if so bonk peach and return
    
    //check if falling off edge
    
    int x = getX();
    int y = getY();
    
    if(getDirection() == left) {
        if(getWorld()->isBlockingObjectAt(this, x-1, y)) {
            setDirection(right);
            if(getWorld()->isBlockingObjectAt(this, x+1, y)) {
                return;
            }
            else {
                moveTo(x+1, y);
                return;
            }
        }
        else {
            moveTo(x-1,y);
            return;
        }
    }
    else if(getDirection() == right) {
        if(getWorld()->isBlockingObjectAt(this, x+1, y)) {
            setDirection(left);
            if(getWorld()->isBlockingObjectAt(this, x-1, y)) {
                return;
            }
            else {
                moveTo(x-1,y);
                return;
            }
        }
        else {
            moveTo(x+1,y);
            return;
        }
    }
}

//GOOMBA
Goomba::Goomba(StudentWorld* mg, int startX, int startY) : Enemy(mg, IID_GOOMBA, startX, startY){};


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
                if(getWorld()->isBlockingObjectAt(this, targetX, targetY)) {
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
                if(getWorld()->isBlockingObjectAt(this, targetX, targetY)) {
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
