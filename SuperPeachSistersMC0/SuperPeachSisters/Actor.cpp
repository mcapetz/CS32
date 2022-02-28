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

bool Actor::isAlive() const {
    return m_isAlive;
}

void Actor::setDead() {
    m_isAlive = false;
}

StudentWorld* Actor::getWorld() const {
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

bool Actor::overlappingPeach() const {
    //use AND function bc checking if player is overlapping
    return getWorld()->ActorBlockingObjectAtAND(getX(), getY()) != nullptr && getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isPlayer();
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

bool Block::isHoldingGoodie() const {
    return holdsGoodie;
}

void Block::setIsHoldingGoodie(bool b) {
    holdsGoodie = b;
}

bool Block::powerUp() {
    //check if holding goodie
    if(isHoldingGoodie()) {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        setIsHoldingGoodie(false);
        return true;
    }
    else {
        //regular block bonk() behavior
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return false;
    }
}


//GOODIE BLOCKS
starBlock::starBlock(StudentWorld* mg, int startX, int startY) : Block(mg, startX, startY) { setIsHoldingGoodie(true); }
void starBlock::bonk() {
    if(powerUp()) {
        //if holding goodie, powerUp() returns true and also plays powerup appears sound and sets holdsGoodie to false
        Star* star = new Star(getWorld(), getX(), getY() + 8);
        getWorld()->addActor(star);
    }
    else return;
}

mushroomBlock::mushroomBlock(StudentWorld* mg, int startX, int startY) : Block(mg, startX, startY) { setIsHoldingGoodie(true); }

void mushroomBlock::bonk() {
    if(powerUp()) {
        //if holding goodie, powerUp() returns true and also plays powerup appears sound and sets holdsGoodie to false
        Mushroom* mushroom = new Mushroom(getWorld(), getX(), getY() + 8);
        getWorld()->addActor(mushroom);
    }
    else return;
}

flowerBlock::flowerBlock(StudentWorld* mg, int startX, int startY) : Block(mg, startX, startY){ setIsHoldingGoodie(true);
}

void flowerBlock::bonk() {
    if(powerUp()) {
        //if holding goodie, powerUp() returns true and also plays powerup appears sound and sets holdsGoodie to false
        Flower* flower = new Flower(getWorld(), getX(), getY() + 8);
        getWorld()->addActor(flower);
    }
    else return;
}

//GOODIES
Goodie::Goodie(StudentWorld* mg, int imageID, int startX, int startY) : Actor(mg, imageID, startX, startY, 0, 1, 1) {}

bool Goodie::powerUpPeach(int score) {
    if(overlappingPeach()) {
        getWorld()->increaseScore(score); //take in an int because different goodies increase score by different amounts
        getWorld()->getPlayer()->setHealth(2); //all goodies set health to 2 hit points
        setDead();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return true;
    }
    return false;
}

void Goodie::doGoodie() {
    
    //attempt to move down
    if(!getWorld()->isBlockingObjectAt(getX(), getY()-2)) {
        moveTo(getX(), getY()-2);
    }
    
    //direction is left
    if(getDirection() == left) {
        if(!getWorld()->isBlockingObjectAt(getX()-2, getY())) moveTo(getX()-2, getY());
        else {
            //change direction if cannot move in current direction
            setDirection(right);
            return;
        }
    }
    else {
        //direction is right
        if(!getWorld()->isBlockingObjectAt(getX()+2, getY())) moveTo(getX()+2, getY());
        else {
            //change direction if cannot move in current direction
            setDirection(left);
            return;
        }
    }
}

Star::Star(StudentWorld* mg, int startX, int startY) : Goodie(mg, IID_STAR, startX, startY) {}
void Star::doSomething() {
    if(powerUpPeach(100)) { //increase score by 100
        getWorld()->getPlayer()->setStarPower(true);
        getWorld()->getPlayer()->setStarInvincibility(150); //set star invincibility to 150 ticks
        return;
    }
    else doGoodie();
}

Mushroom::Mushroom(StudentWorld* mg, int startX, int startY) : Goodie(mg, IID_MUSHROOM, startX, startY) {}
void Mushroom::doSomething() {
    if(powerUpPeach(75)) { //increase score by 75
        getWorld()->getPlayer()->setJumpPower(true);
        return;
    }
    else doGoodie();
}

Flower::Flower(StudentWorld* mg, int startX, int startY) : Goodie(mg, IID_FLOWER, startX, startY) {}
void Flower::doSomething() {
    
    if(powerUpPeach(50)) { //increase score by 50
        getWorld()->getPlayer()->setShootPower(true);
        return;
    }
    else doGoodie();
    
}

//PIPE
Pipe::Pipe(StudentWorld* mg, int startX, int startY) : Obstacle(mg, IID_PIPE, startX, startY) {
}
//pipes use default bonk() and doSomething() implementations from the base Actor class that do nothing

//LEVEL ENDER
levelEnder::levelEnder(StudentWorld* mg, int imageID, int startX, int startY) : Actor(mg, imageID, startX, startY, 0, 1, 1) {}

void levelEnder::doSomething() {
    if(!isAlive()) return;
    if(reachedFlagOrMario()) endLevel(); //endLevel() is pure virtual so it is up to the derived classes to define this
}

bool levelEnder::reachedFlagOrMario() {
    if(overlappingPeach()) {
        getWorld()->increaseScore(1000); //both Mario and Flag increase score by 1000
        setDead();
        return true;
    }
    return false;
}

//FLAG
Flag::Flag(StudentWorld* mg, int startX, int startY) : levelEnder(mg, IID_FLAG, startX, startY) {}
void Flag::endLevel() {
    getWorld()->reachedFlag(); //tell the world that a flag has been reached, level has been finished
}

Mario::Mario(StudentWorld* mg, int startX, int startY) : levelEnder(mg, IID_MARIO, startX, startY) {}
void Mario::endLevel() {
    getWorld()->reachedMario(); //tell the world that a Mario has been reached, game has been finished
}

//ENEMY
Enemy::Enemy(StudentWorld* mg, int imageID, int startX, int startY) : Actor(mg, imageID, startX, startY, randInt(0, 1)*180, 1, 0) {}; //random direction either 0 or 180

bool Enemy::isEnemy() {
    return true;
}

Peach* Enemy::getPlayer() const { return getWorld()->getPlayer(); }

void Enemy::enemyBonk() {
    if(getPlayer()->isStarPower()) {
        getWorld()->playSound(SOUND_PLAYER_KICK); //only runs if player has star power
    }
    if(getWorld()->getPlayer()->isAlive()) getWorld()->increaseScore(100); //runs regardless of whether or not player has star power
    setDead();
}

void Enemy::enemyOverlappingPeach() {
    if(overlappingPeach()) {
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
void Goomba::doSomething() { doEnemy(); } //Goomba only does common enemy doSomething() behavior
void Goomba::bonk() { enemyBonk(); } //Goomba only does common enemy bonk() behavior

//KOOPA
Koopa::Koopa(StudentWorld* mg, int startX, int startY) : Enemy(mg, IID_KOOPA, startX, startY){};
void Koopa::doSomething() { doEnemy(); } //Koopa only does common enemy doSomething() behavior
void Koopa::bonk() {
    enemyBonk(); //do common enemy bonk behavior
    getWorld()->addActor(new Shell(getWorld(), getX(), getY(), getDirection())); //introduce new shell to world
}

//PIRANHA
Piranha::Piranha(StudentWorld* mg, int startX, int startY) : Enemy(mg, IID_PIRANHA, startX, startY), m_firingDelay(0) {}

void Piranha::bonk() { enemyBonk(); } //Piranha only does common enemy bonk() behavior

void Piranha::doSomething() {
    if(!isAlive()) return; //does not do common enemy doSomething() behavior
    
    //check if overlapping with peach
    enemyOverlappingPeach();
    
    increaseAnimationNumber(); //piranha's mouth moves every tick
    
    //save player's x and y coordinates in variables for cleaner code
    int pY = getWorld()->getPlayer()->getY();
    int pX = getWorld()->getPlayer()->getX();
    
    //check if peach is on the same level
    if(pY >= getY() - 1.5 * SPRITE_HEIGHT && pY <= getY() + 1.5 * SPRITE_HEIGHT) {
        if(pX < getX()) {
            //peach is on the left
            setDirection(left);
        }
        else {
            //peach is on the right
            setDirection(right);
        }
        if(m_firingDelay > 0) { //decrement firing delay if necessary
            m_firingDelay--;
            return;
        }
        else {
            //no firing delay
            if(abs(pX - getX()) < 8*SPRITE_WIDTH) { //if peach is within range
                getWorld()->addActor(new PiranhaFireball(getWorld(), getX(), getY(), getDirection())); //introduce new piranha fireball to world
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

    //attempt to move down
    if(!getWorld()->isBlockingObjectAt(getX(), getY()-2)) moveTo(getX(), getY()-2);

    //attempt to move left
    if(getDirection() == left) {
        if(!getWorld()->isBlockingObjectAt(getX()-2, getY())) moveTo(getX()-2, getY());
        else {
            setDead(); //if movement is blocked, die
            return;
        }
    }
    else {
        //attempt to move right
        if(!getWorld()->isBlockingObjectAt(getX()+2, getY())) moveTo(getX()+2, getY());
        else {
            setDead(); //if movement is blocked, die
            return;
        }
    }
}

Shell::Shell(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_SHELL, startX, startY, dir) {};
void Shell::doSomething() {
    //if shell overlaps an enemy, attempt to damage the enemy
    if(getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isEnemy() && getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isAlive()) {
            getWorld()->ActorBlockingObjectAtAND(getX(), getY())->bonk();
            setDead();
            return;
    }
    moveWithFalling(); //otherwise move with common projectile movement
    
}

PeachFireball::PeachFireball(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_PEACH_FIRE, startX, startY, dir) {};
void PeachFireball::doSomething() {
    //if peach fireball overlaps an enemy, attempt to damage the enemy
    if(getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isEnemy()) {
        setDead();
        if(getWorld()->ActorBlockingObjectAtAND(getX(), getY())->isAlive()) {
            getWorld()->ActorBlockingObjectAtAND(getX(), getY())->bonk();
        }
        return;
    }
    
    moveWithFalling(); //otherwise move with common projectile movement
    
}

PiranhaFireball::PiranhaFireball(StudentWorld* mg, int startX, int startY, int dir) : Projectile(mg, IID_PIRANHA_FIRE, startX, startY, dir) {};
void PiranhaFireball::doSomething() {
    //if piranha fireball overlaps with peach, attempt to damage her
    if(overlappingPeach()) {
        getWorld()->getPlayer()->bonk();
        setDead();
        return;
    }
    
    moveWithFalling(); //otherwise move with common projectile movement
    
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

bool Peach::isStarPower() const {
    return starPower;
}

bool Peach::isShootPower() const {
    return shootPower;
}

bool Peach::isJumpPower() const {
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

void Peach::setTempInvincibility(int x) { //star and temp invincibility differentiated in spec
    temp_invincibility = x;
}

void Peach::setStarInvincibility(int x) { //star and temp invincibility differentiated in spec
    star_invincibility = x;
}

void Peach::bonk() {
    //check if peach is invincible, if so, immediately return
    if(starPower || tempInvincibility) return;
    //decrement health
    m_health--;
    //set temp_invincibility
    temp_invincibility = 10;
    //set powers to false
    if(shootPower) shootPower = false;
    if(jumpPower) jumpPower = false;
    //play sound if health points > 0
    if(m_health > 0) getWorld()->playSound(SOUND_PLAYER_HURT);
    //else die
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
    
    //check user input
    int key = 0;
    if(getWorld()->getKey(key)) {
        switch(key) {
            case KEY_PRESS_LEFT: //attempt to move left without overlapping obstacles
                setDirection(left);
                if(getWorld()->isBlockingObjectAt(getX()-4, getY())) {
                    getWorld()->ActorBlockingObjectAt(getX()-4, getY())->bonk();
                }
                else {
                    moveTo(getX()-4, getY());
                }
                break;
            case KEY_PRESS_RIGHT: //attempt to move right without overlapping obstacles
                setDirection(right);
                if(getWorld()->isBlockingObjectAt(getX()+4, getY())) {
                    getWorld()->ActorBlockingObjectAt(getX()+4, getY())->bonk();
                }
                else {
                    moveTo(getX()+4, getY());
                }
                break;
            case KEY_PRESS_UP: //attempt to jump with something below to support jump
                if(getWorld()->isBlockingObjectAt(getX(), getY()-1)) {
                    //there is an object below to support her jump
                    if(jumpPower) remaining_jump_distance = 12;
                    else remaining_jump_distance = 8;
                    getWorld()->playSound(SOUND_PLAYER_JUMP);
                }
                break;
            case KEY_PRESS_SPACE: //attempt to fire
                if(!shootPower) break; //cannot fire if there is no shoot power
                if(time_to_recharge_before_next_fire > 0) break; //cannot fire if there is still time to recharge before next fire
                else {
                    //otherwise peach can fire
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    time_to_recharge_before_next_fire = 8; //reset time to recharge to 8 ticks
                    if(getDirection() == left) { //fire to the left
                        getWorld()->addActor(new PeachFireball(getWorld(), getX()-4, getY(), left));
                    }
                    else { //fire to the right
                        getWorld()->addActor(new PeachFireball(getWorld(), getX()+4, getY(), right));
                    }
                }
                break;
        }
    }
}
