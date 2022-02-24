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

bool Actor::isPlayer() {
    return false;
}

//BLOCK
Block::Block(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_BLOCK, startX, startY, 0, 2, 1), holdsGoodie(false) {}
bool Block::isStatic() {return true;}

void Block::bonk() {
    std::cout << "block bonk" << std::endl;
    getWorld()->playSound(SOUND_PLAYER_BONK);
    return;
}

bool Block::isHoldingGoodie() {
    return holdsGoodie;
}

void Block::setIsHoldingGoodie(bool b) {
    holdsGoodie = b;
}


//GOODIE BLOCKS
starBlock::starBlock(StudentWorld* mg, int startX, int startY) : Block(mg, startX, startY) { setIsHoldingGoodie(true); }
void starBlock::bonk() {
    std::cout << "star block bonked" << std::endl;
    if(isHoldingGoodie()) {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        Star* star = new Star(getWorld(), getX(), getY() + 8);
        getWorld()->addActor(star);
        setIsHoldingGoodie(false);
    }
    else {
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }
}

mushroomBlock::mushroomBlock(StudentWorld* mg, int startX, int startY) : Block(mg, startX, startY) { setIsHoldingGoodie(true); }
void mushroomBlock::bonk() {
    std::cout << "mushroom block bonked" << std::endl;
    if(isHoldingGoodie()) {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        Mushroom* mushroom = new Mushroom(getWorld(), getX(), getY() + 8);
        getWorld()->addActor(mushroom);
        setIsHoldingGoodie(false);
    }
    else {
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }
}

flowerBlock::flowerBlock(StudentWorld* mg, int startX, int startY) : Block(mg, startX, startY){ setIsHoldingGoodie(true);
}

void flowerBlock::bonk() {
    std::cout << "flower block bonked" << std::endl;
    if(isHoldingGoodie()) {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        Flower* flower = new Flower(getWorld(), getX(), getY() + 8);
        getWorld()->addActor(flower);
        setIsHoldingGoodie(false);
    }
    else {
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }
}

//GOODIES
Goodie::Goodie(StudentWorld* mg, int imageID, int startX, int startY) : Actor(mg, imageID, startX, startY, 0, 1, 1) {}
void Goodie::doGoodie() {
    
    if(!getWorld()->isBlockingObjectAt(getX(), getY()-2)) {
        moveTo(getX(), getY()-2);
    }
    
    if(getDirection() == left) {
        if(!getWorld()->isBlockingObjectAt(getX()-2, getY())) moveTo(getX()-2, getY());
        else {
            setDirection(right);
            return;
        }
    }
    else {
        if(!getWorld()->isBlockingObjectAt(getX()+2, getY())) moveTo(getX()+2, getY());
        else {
            setDirection(left);
            return;
        }
    }
}

Star::Star(StudentWorld* mg, int startX, int startY) : Goodie(mg, IID_STAR, startX, startY) {}
void Star::doSomething() {
    if(getWorld()->ActorBlockingObjectAtAND(getX(), getY()) != nullptr && getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isPlayer()) {
        std::cout << "star touching peach" << std::endl;
        getWorld()->increaseScore(100);
        getWorld()->getPlayer()->setStarPower(true);
        getWorld()->getPlayer()->setHealth(2);
        setDead();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    doGoodie();
}

Mushroom::Mushroom(StudentWorld* mg, int startX, int startY) : Goodie(mg, IID_MUSHROOM, startX, startY) {}
void Mushroom::doSomething() {
    if(getWorld()->ActorBlockingObjectAtAND(getX(), getY()) != nullptr && getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isPlayer()) {
        std::cout << "mushroom touching peach" << std::endl;
        getWorld()->increaseScore(75);
        getWorld()->getPlayer()->setJumpPower(true);
        getWorld()->getPlayer()->setHealth(2);
        setDead();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    doGoodie();
}

Flower::Flower(StudentWorld* mg, int startX, int startY) : Goodie(mg, IID_FLOWER, startX, startY) {}
void Flower::doSomething() {
    if(getWorld()->ActorBlockingObjectAtAND(getX(), getY()) != nullptr && getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isPlayer()) {
        std::cout << "flower touching peach" << std::endl;
        getWorld()->increaseScore(50);
        getWorld()->getPlayer()->setShootPower(true);
        getWorld()->getPlayer()->setHealth(2);
        setDead();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    doGoodie();
}

//PIPE
Pipe::Pipe(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_PIPE, startX, startY, 0, 2, 1) {
}
bool Pipe::isStatic() {return true;}

//FLAG
Flag::Flag(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_FLAG, startX, startY, 0, 1, 1) {}

void Flag::doSomething() {
    if(!isAlive()) return;
    if(getWorld()->ActorBlockingObjectAtAND(getX(), getY()) && getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isPlayer()) {
        std::cout << "reached flag" << std::endl;
        getWorld()->increaseScore(1000);
        setDead();
        getWorld()->reachedFlag();
    }
}

Mario::Mario(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_MARIO, startX, startY, 0, 1, 1) {}
void Mario::doSomething() {
    if(!isAlive()) return;
    if(getWorld()->ActorBlockingObjectAt(getX(), getY()) && getWorld()->ActorBlockingObjectAt(getX(), getY())->isPlayer()) {
        getWorld()->increaseScore(1000);
        setDead();
        getWorld()->reachedMario();
    }
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
    }
    getWorld()->increaseScore(100);
    setDead();
}

void Enemy::doEnemy() {
    if(!isAlive()) return;
    
    //check if overlapping with peach
    if(getX() + SPRITE_WIDTH - 1 >= getWorld()->getPlayer()->getX() && getX() - SPRITE_WIDTH + 1 <= getWorld()->getPlayer()->getX() && getY() + SPRITE_WIDTH - 1 >= getWorld()->getPlayer()->getY() && getY() - SPRITE_WIDTH + 1 <= getWorld()->getPlayer()->getY()) {
        //if so bonk peach and return
        std::cout << "bonk player" << std::endl;
        getPlayer()->bonk();
    }
    
    if(getDirection() == left) {
        if(getWorld()->isBlockingObjectAt(getX()-1, getY()) || !getWorld()->isBlockingObjectAt(getX()-1-SPRITE_WIDTH, getY()-1)) {
            setDirection(right);
            return;
        }
    }
    else {
        if(getWorld()->isBlockingObjectAt(getX()+1, getY()) || !getWorld()->isBlockingObjectAt(getX()+1+SPRITE_WIDTH, getY()-1)) {
            setDirection(left);
            return;
        }
    }
    
    if(getDirection() == left) {
        if(getWorld()->isBlockingObjectAt(getX()-1, getY())) return;
        else moveTo(getX()-1, getY());
    }
    else {
        if(getWorld()->isBlockingObjectAt(getX()+1, getY())) return;
        else moveTo(getX()+1, getY());
    }
        
//    if(getDirection() == left) {
//        if(getWorld()->isBlockingObjectAt(getX()-1, getY())) {
//            setDirection(right);
//            if(getWorld()->isBlockingObjectAt(getX()+1, getY())) {
//                return;
//            }
//            else {
//                if(getWorld()->isBlockingObjectAt(getX(), getY()-1)) moveTo(getX()+1, getY());
//                return;
//            }
//        }
//        else {
//            if(getWorld()->isBlockingObjectAt(getX()-1-SPRITE_WIDTH, getY()-1)) moveTo(getX()-1,getY());
//            else setDirection(right);
//            return;
//        }
//    }
//    else if(getDirection() == right) {
//        if(getWorld()->isBlockingObjectAt(getX()+1, getY())) {
//            setDirection(left);
//            if(getWorld()->isBlockingObjectAt(getX()-1, getY())) {
//                return;
//            }
//            else {
//                if(getWorld()->isBlockingObjectAt(getX(), getY()-1)) moveTo(getX()-1,getY());
//                return;
//            }
//        }
//        else {
//            if(getWorld()->isBlockingObjectAt(getX()+1+SPRITE_WIDTH, getY()-1)) moveTo(getX()+1,getY());
//            else setDirection(left);
//            return;
//        }
//    }
    
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
    std::cout << "koopa bonked" << std::endl;
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
    
//    if(!getWorld()->isBlockingObjectAt(getX(), getY()-1)) {
//        std::cout << "floating" << std::endl;
//        setDead();
//        return;
//    }
            
    if(getDirection() == left) {
        if(getWorld()->isBlockingObjectAt(getX()-2, getY())) {
            setDead();
            return;
        }
        else {
            if(getWorld()->isBlockingObjectAt(getX()-2, getY()-1)) moveTo(getX()-2, getY());
            return;
        }
    }
    else if(getDirection() == right) {
        if(getWorld()->isBlockingObjectAt(getX()+2, getY())) {
            setDead();
            return;
        }
        else {
            if(getWorld()->isBlockingObjectAt(getX()+2, getY()-1)) moveTo(getX()+2,getY());
            else setDead();
            return;
        }
    }
}

void Projectile::moveWithFalling() {
    if(!isAlive()) return;

        if(!getWorld()->isBlockingObjectAt(getX(), getY()-2)) moveTo(getX(), getY()-2);
        if(getDirection() == left) {
            if(!getWorld()->isBlockingObjectAt(getX()-2, getY())) moveTo(getX()-2, getY());
            else {
                setDead();
                return;
            }
        }
        else {
            if(!getWorld()->isBlockingObjectAt(getX()+2, getY())) moveTo(getX()+2, getY());
            else {
                setDead();
                return;
            }
        }
    
}

Shell::Shell(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_SHELL, startX, startY, dir) {};
void Shell::doSomething() {
//    if(getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isEnemy()) {
//        std::cout << "bonked enemy SHELL" << std::endl;
//        setDead();
//        if(getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isAlive()) {
//            getWorld()->ActorBlockingObjectAtAND(getX(), getY())->bonk();
//        }
//        return;
//    }
    moveWithFalling();
    
}

PeachFireball::PeachFireball(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_PEACH_FIRE, startX, startY, dir) {};
void PeachFireball::doSomething() {
    //if(getWorld()->ActorBlockingObjectAt(getX(), getY())) std::cout << "BONK" << std::endl;
    if(getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isEnemy()) {
        std::cout << "bonked enemy HERE" << std::endl;
        setDead();
        if(getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isAlive()) {
            getWorld()->ActorBlockingObjectAtAND(getX(), getY())->bonk();
        }
        return;
    }
    
    moveWithFalling();
    
}

PiranhaFireball::PiranhaFireball(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_PIRANHA_FIRE, startX, startY, dir) {};
void PiranhaFireball::doSomething() {
    //std::cout << getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isPlayer() << std::endl;
    if(getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isPlayer()) {
        std::cout << "princess is ded" << std::endl;
        getWorld()->getPlayer()->bonk();
        setDead();
        return;
    }
    
    moveWithFalling();
    
}



//PEACH
Peach::Peach(StudentWorld* mg, int startX, int startY) : Actor(mg, IID_PEACH, startX, startY, 0, 0, 1) {
    m_health = 1;
    starPower = false;
    shootPower = false;
    jumpPower = false;
    remaining_jump_distance = 0;
    time_to_recharge_before_next_fire = 0;
    temp_invincibility = 0;
}

bool Peach::isStarPower() {
    return starPower;
}

bool Peach::isShootPower() {
    return shootPower;
}

bool Peach::isJumpPower() {
    return jumpPower;
}

void Peach::setStarPower(bool b) {
    starPower = b;
}
void Peach::setShootPower(bool b) {
    shootPower = b;
}
void Peach::setJumpPower(bool b) {
    jumpPower = b;
}

bool Peach::isPlayer() {
    return true;
}

void Peach::setHealth(int x) {
    m_health = x;
}

void Peach::bonk() {
    if(starPower) return;
    m_health--;
    temp_invincibility = 10;
    if(shootPower) shootPower = false;
    if(jumpPower) jumpPower = false;
    if(m_health > 0) getWorld()->playSound(SOUND_PLAYER_HURT);
    //else setDead();
}

void Peach::doSomething() {
    if(!isAlive()) return;
    
    //check temp invincibility
    //check recharge
    if(time_to_recharge_before_next_fire > 0) time_to_recharge_before_next_fire--;
    //check overlap
    if(getWorld()->isBlockingObjectAt(getX(), getY())) {
        getWorld()->ActorBlockingObjectAt(getX(), getY())->bonk();
    }
    //check jump
    if(remaining_jump_distance > 0) {
        if(getWorld()->isBlockingObjectAt(getX(), getY()+4)) {
            std::cout << "trying to jump" << std::endl;
            getWorld()->ActorBlockingObjectAt(getX(), getY()+4)->bonk();
            remaining_jump_distance = 0;
        }
        else {
            moveTo(getX(), getY()+4);
            remaining_jump_distance--;
        }
    }
    //check falling
    else if(!(getWorld()->isBlockingObjectAt(getX(), getY() - 1) || getWorld()->isBlockingObjectAt(getX(), getY() - 2) || getWorld()->isBlockingObjectAt(getX(), getY() - 3))) {
        moveTo(getX(), getY() - 4);
    }
    int key = 0;
    if(getWorld()->getKey(key)) {
        switch(key) {
            case KEY_PRESS_LEFT:
                setDirection(left);
                if(getWorld()->isBlockingObjectAt(getX()-4, getY())) {
                    getWorld()->ActorBlockingObjectAt(getX()-4, getY())->bonk();
                }
                else {
                    moveTo(getX()-4, getY());
                }
                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                if(getWorld()->isBlockingObjectAt(getX()+4, getY())) {
                    getWorld()->ActorBlockingObjectAt(getX()+4, getY())->bonk();
                }
                else {
                    moveTo(getX()+4, getY());
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
