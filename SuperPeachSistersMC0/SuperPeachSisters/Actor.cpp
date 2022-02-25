#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(StudentWorld* mg, int imageID, int startX, int startY, int dir, int depth, double size) : GraphObject(imageID, startX, startY, dir, depth, size) {
    m_isAlive = true;
    m_world = mg;
}

void Actor::bonk() {
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

bool Actor::overlappingPeach() {
    return getWorld()->ActorBlockingObjectAtAND(getX(), getY()) != nullptr && getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isPlayer();
}

bool Actor::reachedFlagOrMario() {
    if(overlappingPeach()) {
        getWorld()->increaseScore(1000);
        setDead();
        return true;
    }
    return false;
}

//OBSTACLE
Obstacle::Obstacle(StudentWorld* mg, int imageID, int startX, int startY) : Actor(mg, imageID, startX, startY, 0, 2, 1) {}
bool Obstacle::isStatic() { return true; }


//BLOCK
Block::Block(StudentWorld* mg, int startX, int startY) : Obstacle(mg, IID_BLOCK, startX, startY), holdsGoodie(false) {}

void Block::bonk() {
    getWorld()->playSound(SOUND_PLAYER_BONK);
    return;
}

bool Block::isHoldingGoodie() {
    return holdsGoodie;
}

void Block::setIsHoldingGoodie(bool b) {
    holdsGoodie = b;
}

bool Block::powerUp() {
    if(isHoldingGoodie()) {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        setIsHoldingGoodie(false);
        return true;
    }
    else {
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return false;
    }
}


//GOODIE BLOCKS
starBlock::starBlock(StudentWorld* mg, int startX, int startY) : Block(mg, startX, startY) { setIsHoldingGoodie(true); }
void starBlock::bonk() {
    if(powerUp()) {
        Star* star = new Star(getWorld(), getX(), getY() + 8);
        getWorld()->addActor(star);
    }
    else return;
}

mushroomBlock::mushroomBlock(StudentWorld* mg, int startX, int startY) : Block(mg, startX, startY) { setIsHoldingGoodie(true); }
void mushroomBlock::bonk() {
    if(powerUp()) {
        Mushroom* mushroom = new Mushroom(getWorld(), getX(), getY() + 8);
        getWorld()->addActor(mushroom);
    }
    else return;
}

flowerBlock::flowerBlock(StudentWorld* mg, int startX, int startY) : Block(mg, startX, startY){ setIsHoldingGoodie(true);
}

void flowerBlock::bonk() {
    if(powerUp()) {
        Flower* flower = new Flower(getWorld(), getX(), getY() + 8);
        getWorld()->addActor(flower);
    }
    else return;
}

//GOODIES
Goodie::Goodie(StudentWorld* mg, int imageID, int startX, int startY) : Actor(mg, imageID, startX, startY, 0, 1, 1) {}

bool Goodie::powerUpPeach(int score) {
    if(overlappingPeach()) {
        getWorld()->increaseScore(score);
        getWorld()->getPlayer()->setHealth(2);
        setDead();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return true;
    }
    return false;
}

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
    if(powerUpPeach(100)) {
        getWorld()->getPlayer()->setStarPower(true);
        getWorld()->getPlayer()->setStarInvincibility(150);
        return;
    }
    else doGoodie();
}

Mushroom::Mushroom(StudentWorld* mg, int startX, int startY) : Goodie(mg, IID_MUSHROOM, startX, startY) {}
void Mushroom::doSomething() {
    if(powerUpPeach(75)) {
        getWorld()->getPlayer()->setJumpPower(true);
        return;
    }
    else doGoodie();
}

Flower::Flower(StudentWorld* mg, int startX, int startY) : Goodie(mg, IID_FLOWER, startX, startY) {}
void Flower::doSomething() {
    
    if(powerUpPeach(50)) {
        getWorld()->getPlayer()->setShootPower(true);
        return;
    }
    else doGoodie();
    
}

//PIPE
Pipe::Pipe(StudentWorld* mg, int startX, int startY) : Obstacle(mg, IID_PIPE, startX, startY) {
}


//class levelEnder: public Actor {
//public:
//    levelEnder(StudentWorld* mg, int imageID, int startX, int startY);
//    virtual void doSomething();
//    virtual void endLevel() = 0;
//};

levelEnder::levelEnder(StudentWorld* mg, int imageID, int startX, int startY) : Actor(mg, imageID, startX, startY, 0, 1, 1) {}

void levelEnder::doSomething() {
    if(!isAlive()) return;
    if(reachedFlagOrMario()) endLevel();
}

//FLAG
Flag::Flag(StudentWorld* mg, int startX, int startY) : levelEnder(mg, IID_FLAG, startX, startY) {}
void Flag::endLevel() {
    getWorld()->reachedFlag();
}

Mario::Mario(StudentWorld* mg, int startX, int startY) : levelEnder(mg, IID_MARIO, startX, startY) {}
void Mario::endLevel() {
    getWorld()->reachedMario();
}

//ENEMY
Enemy::Enemy(StudentWorld* mg, int imageID, int startX, int startY) : Actor(mg, imageID, startX, startY, randInt(0, 1)*180, 1, 0) {};

bool Enemy::isEnemy() {
    return true;
}

Peach* Enemy::getPlayer() { return getWorld()->getPlayer(); }

void Enemy::enemyBonk() {
    //If the bonker is not Peach, then ignore the bonk
    if(getPlayer()->isStarPower()) {
        getWorld()->playSound(SOUND_PLAYER_KICK);
    }
    if(getWorld()->getPlayer()->isAlive()) getWorld()->increaseScore(100);
    setDead();
}

void Enemy::enemyOverlappingPeach() {
    if(getX() + SPRITE_WIDTH - 1 >= getWorld()->getPlayer()->getX() && getX() - SPRITE_WIDTH + 1 <= getWorld()->getPlayer()->getX() && getY() + SPRITE_WIDTH - 1 >= getWorld()->getPlayer()->getY() && getY() - SPRITE_WIDTH + 1 <= getWorld()->getPlayer()->getY()) {
        //if so bonk peach and return
        getPlayer()->bonk();
        bonk();
        return;
    }
}

void Enemy::doEnemy() {
    if(!isAlive()) return;
    
    //check if overlapping with peach
    enemyOverlappingPeach();
    
    //check if falling off block
    if(getDirection() == left) {
        if(!getWorld()->isBlockingObjectAt(getX()-SPRITE_WIDTH, getY()-1)) {
            setDirection(right);
        }
    }
    else {
        if(!getWorld()->isBlockingObjectAt(getX()+SPRITE_WIDTH, getY()-1)) {
            setDirection(left);
        }
    }
    
    //check if can move in curr direction
    if(getDirection() == left) {
        if(getWorld()->isBlockingObjectAt(getX()-1, getY())) {
            setDirection(right);
        }
    }
    else {
        if(getWorld()->isBlockingObjectAt(getX()+1, getY())) {
            setDirection(left);
        }
    }
    
    //try to move
    if(getDirection() == left) {
        if(getWorld()->isBlockingObjectAt(getX()-1, getY())) return;
        else moveTo(getX()-1, getY());
    }
    else {
        if(getWorld()->isBlockingObjectAt(getX()+1, getY())) return;
        else moveTo(getX()+1, getY());
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
    
    //check if overlapping with peach
    enemyOverlappingPeach();
    
    increaseAnimationNumber();
    int pY = getWorld()->getPlayer()->getY();
    int pX = getWorld()->getPlayer()->getX();
    if(pY >= getY() - 1.5 * SPRITE_HEIGHT && pY <= getY() + 1.5 * SPRITE_HEIGHT) {
        if(pX < getX()) {
            //peach is on the left
            setDirection(left);
        }
        else {
            //peach is on the right
            setDirection(right);
        }
        if(m_firingDelay > 0) {
            m_firingDelay--;
            return;
        }
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

Projectile::Projectile(StudentWorld* mg, int imageID, int startX, int startY, int dir) : Actor(mg, imageID, startX, startY, dir, 1, 1) {}

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
    if(getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isEnemy() && getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isAlive()) {
            getWorld()->ActorBlockingObjectAtAND(getX(), getY())->bonk();
            setDead();
            return;
    }
    moveWithFalling();
    
}

PeachFireball::PeachFireball(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_PEACH_FIRE, startX, startY, dir) {};
void PeachFireball::doSomething() {
    if(getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isEnemy()) {
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
    if(overlappingPeach()) {
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
    temp_invincibility = false;
    remaining_jump_distance = 0;
    time_to_recharge_before_next_fire = 0;
    temp_invincibility = 0;
    star_invincibility = 0;
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

void Peach::setTempInvincibility(int x) {
    temp_invincibility = x;
}

void Peach::setStarInvincibility(int x) {
    star_invincibility = x;
}

void Peach::bonk() {
    if(starPower || tempInvincibility) return;
    m_health--;
    temp_invincibility = 10;
    if(shootPower) shootPower = false;
    if(jumpPower) jumpPower = false;
    if(m_health > 0) getWorld()->playSound(SOUND_PLAYER_HURT);
    if(m_health <= 0) {
        setDead();
    }
}

void Peach::doSomething() {
    if(!isAlive()) return;
    
    //check invincibility
    if(starPower) star_invincibility--;
    if(star_invincibility == 0) starPower = false;
    if(temp_invincibility > 0) temp_invincibility--;
    if(temp_invincibility == 0) tempInvincibility = false;
    //check recharge
    if(time_to_recharge_before_next_fire > 0) time_to_recharge_before_next_fire--;
    
    //check overlap
    if(getWorld()->isBlockingObjectAt(getX(), getY()) && getWorld()->ActorBlockingObjectAtAND(getX(), getY())) {
        getWorld()->ActorBlockingObjectAtAND(getX(), getY())->bonk();
    }
    //check jump
    if(remaining_jump_distance > 0) {
        if(getWorld()->isBlockingObjectAt(getX(), getY()+4)) {
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
                        PeachFireball* fire = new PeachFireball(getWorld(), getX()+4, getY(), right);
                        getWorld()->addActor(fire);
                    }
                }
                break;
        }
    }
}
