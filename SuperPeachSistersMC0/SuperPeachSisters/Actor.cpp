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

void Actor::setDead() {
    m_isAlive = false;
}

StudentWorld* Actor::getWorld() {
    return m_world;
}

bool Actor::isStatic() {
    return false;
}

bool Actor::isEnemy() {
    return false;
}

//BLOCK
Block::Block(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_BLOCK, startX, startY, 0, 2, 1) {}
bool Block::isStatic() {return true;}

void Block::bonk() {
    std::cout << "block cannot be damanged by bonk" << std::endl;
}

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

bool Enemy::isEnemy() {
    return true;
}

Peach* Enemy::getPlayer() { return getWorld()->getPlayer(); }

void Enemy::enemyBonk() {
    std::cout << "enemy bonked" << std::endl;
    //If the bonker is not Peach, then ignore the bonk
    if(getPlayer()->isStarPower()) {
        getWorld()->playSound(SOUND_PLAYER_KICK);
        getWorld()->incScore(100);
    }
    setDead();
}

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
void Goomba::bonk() { enemyBonk(); }

//KOOPA
Koopa::Koopa(StudentWorld* mg, int startX, int startY) : Enemy(mg, IID_KOOPA, startX, startY){};
void Koopa::doSomething() { doEnemy(); }
void Koopa::bonk() {
    enemyBonk();
    Shell* shell = new Shell(getWorld(), getX(), getY(), getDirection());
    getWorld()->addActor(shell);
}

//PIRANHA
Piranha::Piranha(StudentWorld* mg, int startX, int startY) : Enemy(mg, IID_PIRANHA, startX, startY), m_firingDelay(0) {}

void Piranha::bonk() { enemyBonk(); }

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
void Projectile::moveWithoutFalling() {
    if(!isAlive()) return;
    
    //check if overlapping with peach
//    if(getWorld()->ActorBlockingObjectAt(getX(), getY()) == getWorld()->getPlayer()) {
//        std::cout << "princess is ded" << std::endl;
//        getWorld()->getPlayer()->bonk();
//        return;
//    }

    int x = getX();
    int y = getY();
        
    if(getDirection() == left) {
        if(getWorld()->isBlockingObjectAt(x-2, y)) {
            setDead();
            return;
        }
        else {
            if(getWorld()->isBlockingObjectAt(x, y-1)) moveTo(x-2, y);
            return;
        }
    }
    else if(getDirection() == right) {
        if(getWorld()->isBlockingObjectAt(x+2, y)) {
            setDead();
            return;
        }
        else {
            if(getWorld()->isBlockingObjectAt(x, y-1)) moveTo(x+2,y);
            return;
        }
    }
}

void Projectile::moveWithFalling() {
    if(!isAlive()) return;
    
    //check if overlapping with peach
    if(getWorld()->ActorBlockingObjectAt(getX(), getY()) == getWorld()->getPlayer()) {
        getWorld()->getPlayer()->bonk();
        std::cout << "princess is ded" << std::endl;
        return;
    }

    int x = getX();
    int y = getY();
        
    if(getDirection() == left) {
        if(getWorld()->isBlockingObjectAt(x-2, y)) {
            if(getWorld()->ActorBlockingObjectAt(x-2,y)->isStatic()) {
                if(getWorld()->isBlockingObjectAt(x-2, y-2)) setDead();
                //std::cout << "fireball cannot move" << std::endl;
                return;
            }
        }
        else {
            //left is not blocked
            if(getWorld()->isBlockingObjectAt(x-2, y-2)) {
                //there is something beneath
                moveTo(x-2, y);
            }
            else {
                //there is nothing beneath
                moveTo(x-2, y-1);
            }
            return;
        }
    }
    else if(getDirection() == right) {
        if(getWorld()->isBlockingObjectAt(x+2, y)) {
            if(getWorld()->ActorBlockingObjectAt(x+2,y)->isStatic()) {
                if(getWorld()->isBlockingObjectAt(x+2, y-2)) setDead();
                return;
            }
        }
        else {
            //right is not blocked
            if(getWorld()->isBlockingObjectAt(x+2, y-2)) {
                //there is something beneath
                moveTo(x+2, y);
            }
            else {
                //there is nothing beneath
                moveTo(x+2, y-2);
            }
            return;
        }
    }
    
}

Shell::Shell(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_SHELL, startX, startY, dir) {};
void Shell::doSomething() {
    if(getWorld()->ActorBlockingObjectAt(getX(), getY())->isEnemy()) {
        getWorld()->ActorBlockingObjectAt(getX(), getY())->bonk();
        std::cout << "bonked enemy" << std::endl;
        return;
    }
    moveWithoutFalling();
}

PeachFireball::PeachFireball(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_PEACH_FIRE, startX, startY, dir) {};
void PeachFireball::doSomething() {
    if(getWorld()->ActorBlockingObjectAt(getX(), getY())) std::cout << "BONK" << std::endl;
    if(getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isEnemy()) {
        std::cout << "bonked enemy HERE" << std::endl;
        getWorld()->ActorBlockingObjectAtAND(getX(), getY())->bonk();
        setDead();
        return;
    }
    
    moveWithFalling();
    
}

PiranhaFireball::PiranhaFireball(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_PIRANHA_FIRE, startX, startY, dir) {};
void PiranhaFireball::doSomething() { moveWithFalling(); }



//PEACH
Peach::Peach(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_PEACH, startX, startY, 0, 0, 1) {
    m_health = 1;
    starPower = false;
    shootPower = true;
    jumpPower = false;
    remaining_jump_distance = 0;
    time_to_recharge_before_next_fire = 0;
}

bool Peach::isStarPower() {
    return starPower;
}

void Peach::doSomething() {
    if(!isAlive()) return;
    
    int targetX = getX();
    int targetY = getY();
    
    //check temp invincibility
    //check recharge
    if(time_to_recharge_before_next_fire > 0) time_to_recharge_before_next_fire--;
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
                    getWorld()->ActorBlockingObjectAt(targetX, targetY)->bonk();
                }
                else {
                    moveTo(targetX, targetY);
                }
                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                targetX += 4;
                if(getWorld()->isBlockingObjectAt(targetX, targetY)) {
                    getWorld()->ActorBlockingObjectAt(targetX, targetY)->bonk();
                }
                else {
                    moveTo(targetX, targetY);
                }
                break;
            case KEY_PRESS_UP:
                if(getWorld()->isBlockingObjectAt(getX(), getY()-1)) {
                    //there is an object below to support her jump
                    if(jumpPower) remaining_jump_distance = 12;
                    else remaining_jump_distance = 8;
                    getWorld()->playSound(SOUND_PLAYER_JUMP);
                    
                }
                break;
            case KEY_PRESS_SPACE:
                if(!shootPower) break;
                if(time_to_recharge_before_next_fire > 0) break;
                else {
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    time_to_recharge_before_next_fire = 8;
                    if(getDirection() == left) {
                        PeachFireball* fire = new PeachFireball(getWorld(), getX()-4, getY(), left);
                        getWorld()->addActor(fire);
                    }
                    else {
                        PeachFireball* fire = new PeachFireball(getWorld(), getX()-4, getY(), right);
                        getWorld()->addActor(fire);
                    }
                }
                break;
        }
    }
}
