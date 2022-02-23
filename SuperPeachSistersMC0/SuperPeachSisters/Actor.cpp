#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(StudentWorld* mg, int imageID, int startX, int startY, int dir, int depth, double size) : GraphObject(imageID, startX, startY, dir, depth, size) {
    m_isAlive = true;
    m_world = mg;
}

void Actor::bonk() {
    std::cout << "bonk did nothing" << std::endl;
}

void Actor::doSomething() {
    if(!isAlive()) return;
}

bool Actor::isAlive() {
    return m_isAlive;
}

StudentWorld* Actor::getWorld() {
    return m_world;
}

bool Actor::isStatic() {return false;}

//BLOCK
Block::Block(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_BLOCK, startX, startY, 0, 2, 1) {}
bool Block::isStatic() {return true;}

//PIPE
Pipe::Pipe(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_PIPE, startX, startY, 0, 2, 1) {
}
bool Pipe::isStatic() {return true;}

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
Enemy::Enemy(StudentWorld* mg, int imageID, int startX, int startY) : Actor(mg, imageID, startX, startY, randInt(0, 1)*180, 1, 1) {};

Peach* Enemy::getPlayer() { return getWorld()->getPlayer(); }

void Enemy::doEnemy() {
    if(!isAlive()) return;
    
    int x = getX();
    int y = getY();
    
    //check if overlapping with peach
    if(x + SPRITE_WIDTH - 1 >= getWorld()->getPlayer()->getX() && x - SPRITE_WIDTH + 1 <= getWorld()->getPlayer()->getX() && y + SPRITE_WIDTH - 1 >= getWorld()->getPlayer()->getY() && y - SPRITE_WIDTH + 1 <= getWorld()->getPlayer()->getY()) {
        //if so bonk peach and return
        getPlayer()->bonk();
    }
        
    if(getDirection() == left) {
        if(getWorld()->isBlockingObjectAt(x-1, y)) {
            setDirection(right);
            if(getWorld()->isBlockingObjectAt(x+1, y)) {
                return;
            }
            else {
                if(getWorld()->isBlockingObjectAt(x, y-1)) moveTo(x+1, y);
                return;
            }
        }
        else {
            if(getWorld()->isBlockingObjectAt(x-1-SPRITE_WIDTH, y-1)) moveTo(x-1,y);
            else setDirection(right);
            return;
        }
    }
    else if(getDirection() == right) {
        if(getWorld()->isBlockingObjectAt(x+1, y)) {
            setDirection(left);
            if(getWorld()->isBlockingObjectAt(x-1, y)) {
                return;
            }
            else {
                if(getWorld()->isBlockingObjectAt(x, y-1)) moveTo(x-1,y);
                return;
            }
        }
        else {
            if(getWorld()->isBlockingObjectAt(x+1+SPRITE_WIDTH, y-1)) moveTo(x+1,y);
            else setDirection(left);
            return;
        }
    }
    
}

//GOOMBA
Goomba::Goomba(StudentWorld* mg, int startX, int startY) : Enemy(mg, IID_GOOMBA, startX, startY){};
void Goomba::doSomething() { doEnemy(); }

//KOOPA
Koopa::Koopa(StudentWorld* mg, int startX, int startY) : Enemy(mg, IID_KOOPA, startX, startY){};
void Koopa::doSomething() { doEnemy(); }

//PIRANHA
Piranha::Piranha(StudentWorld* mg, int startX, int startY) : Enemy(mg, IID_PIRANHA, startX, startY), m_firingDelay(0) {}

void Piranha::doSomething() {
    if(!isAlive()) return;
    increaseAnimationNumber();
    int pY = getWorld()->getPlayer()->getY();
    int pX = getWorld()->getPlayer()->getX();
    if(pY >= getY() - 1.5 * SPRITE_HEIGHT && pY <= getY() + 1.5 * SPRITE_HEIGHT) {
        //std::cerr << "i am here: " << getX() << " peach is on same level" << std::endl;
        if(pX < getX()) {
            //peach is on the left
            setDirection(left);
        }
        else {
            //peach is on the right
            setDirection(right);
        }
        if(m_firingDelay > 0) m_firingDelay--;
        else {
            //no firing delay
            if(abs(pX - getX()) < 8*SPRITE_WIDTH) {
                getWorld()->addActor(new PiranhaFireball(getWorld(), getX(), getY(), getDirection()));
                getWorld()->playSound(SOUND_PIRANHA_FIRE);
                m_firingDelay = 40;
                return;
            }
        }
    }
    else return;
    
}

Projectile::Projectile(StudentWorld* mg, int imageID, int startX, int startY, int dir) : Actor(mg, imageID, startX, startY, dir, 1, 1) {};
void Projectile::doProjectile() {
    if(!isAlive()) return;
    
    //check if overlapping with peach
    //if so bonk peach and return
    int x = getX();
    int y = getY();
        
    if(getDirection() == left) {
        if(getWorld()->isBlockingObjectAt(x+1, y)) {
            return;
        }
        else {
            if(getWorld()->isBlockingObjectAt(x, y-1)) moveTo(x+1, y);
            return;
        }
    }
    else if(getDirection() == right) {
        if(getWorld()->isBlockingObjectAt(x-1, y)) {
            return;
        }
        else {
            if(getWorld()->isBlockingObjectAt(x, y-1)) moveTo(x-1,y);
            return;
        }
    }
}

Shell::Shell(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_SHELL, startX, startY, dir) {};
void Shell::doSomething() { doProjectile(); }

PeachFireball::PeachFireball(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_PEACH_FIRE, startX, startY, dir) {};
void PeachFireball::doSomething() { doProjectile(); }

PiranhaFireball::PiranhaFireball(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_PEACH_FIRE, startX, startY, dir) {};
void PiranhaFireball::doSomething() { }



//PEACH
Peach::Peach(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_PEACH, startX, startY, 0, 0, 1) {
    m_health = 1;
    starPower = false;
    shootPower = false;
    jumpPower = false;
    remaining_jump_distance = 0;
}

void Peach::doSomething() {
    if(!isAlive()) return;
    
    int targetX = getX();
    int targetY = getY();
    
    //check temp invincibility
    //check recharge
    //check overlap
    if(getWorld()->isBlockingObjectAt(getX(), getY())) {
        getWorld()->ActorBlockingObjectAt(getX(), getY())->bonk();
    }
    //check jump
    if(remaining_jump_distance > 0) {
        targetY += 4;
        if(getWorld()->isBlockingObjectAt(targetX, targetY)) {
            getWorld()->ActorBlockingObjectAt(getX(), getY())->bonk();
            remaining_jump_distance = 0;
        }
        else {
            moveTo(targetX, targetY);
            remaining_jump_distance--;
        }
    }
    //check falling
    else if(!(getWorld()->isBlockingObjectAt(targetX, targetY - 1) || getWorld()->isBlockingObjectAt(targetX, targetY - 2) || getWorld()->isBlockingObjectAt(targetX, targetY - 3))) {
        moveTo(targetX, targetY - 4);
    }
    int key = 0;
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
            case KEY_PRESS_UP:
                if(getWorld()->isBlockingObjectAt(getX(), getY()-1)) {
                    //there is an object below to support her jump
                    //if jump power, 12
                    remaining_jump_distance = 8;
                    getWorld()->playSound(SOUND_PLAYER_JUMP);
                    
                }
                break;
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
