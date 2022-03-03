#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    //intialize booleans to false because the level has not ended
    isFlagReached = false;
    isMarioReached = false;
    
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

void StudentWorld::reachedFlag() {
    isFlagReached = true;
}

void StudentWorld::reachedMario() {
    isMarioReached = true;
}

int StudentWorld::init()
{
    
    isFlagReached = false;
    isMarioReached = false;
    
    Level lev(assetPath());
     ostringstream oss;
     oss.fill('0');
     oss << "level" << setw(2) << getLevel() << ".txt";
     string level_file = oss.str();
     Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found) {
       cerr << "Could not find data file "<< level_file << endl;
       return GWSTATUS_LEVEL_ERROR;
    }
     else if (result == Level::load_fail_bad_format) {
         cerr << "level01.txt is improperly formatted" << endl;
         return GWSTATUS_LEVEL_ERROR;
     }
     else if (result == Level::load_success)
     {
     cerr << "Successfully loaded level " << level_file << endl;
     Level::GridEntry ge;
         for(int i = 0; i < 32; i++) {
             for(int j = 0; j < 32; j++)  {
                 ge = lev.getContentsOf(i, j);
                 
                 switch(ge) {
                     case Level::empty:
                         //cerr << "Location " << i << "," << j << "is empty" << endl;
                         break;
                     case Level::peach:
                         m_player = new Peach(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                         break;
                     case Level::koopa:
                         m_actors.push_back(new Koopa(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                         break;
                     case Level::goomba:
                         m_actors.push_back(new Goomba(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                         break;
                     case Level::piranha:
                         m_actors.push_back(new Piranha(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                         break;
                     case Level::block:
                         m_actors.push_back(new Block(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                         break;
                     case Level::star_goodie_block:
                         m_actors.push_back(new starBlock(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                         break;
                     case Level::mushroom_goodie_block:
                         m_actors.push_back(new mushroomBlock(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                         break;
                     case Level::flower_goodie_block:
                         m_actors.push_back(new flowerBlock(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                         break;
                     case Level::pipe:
                         m_actors.push_back(new Pipe(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                         break;
                     case Level::flag:
                         m_actors.push_back(new Flag(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                         break;
                     case Level::mario:
                         m_actors.push_back(new Mario(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                         break;
                 }
             }
         }
     }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //if the player is alive, call player's doSomething()
    if(m_player->isAlive()) m_player->doSomething();
    
    //for all actors, if they are alive, call doSomething()
    for(int i = 0; i < m_actors.size(); i++) {
        if(m_actors[i]->isAlive()) m_actors[i]->doSomething();
    }
    
    //if player is not alive
    if(!m_player->isAlive()) {
        playSound(SOUND_PLAYER_DIE);
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    //if peach reaches flag
    if(isFlagReached) {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    //if peach reaches mario
    if(isMarioReached) {
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON;
    }
    
    //delete dead actors
    for(int i = 0; i < m_actors.size(); i++) {
        if(!m_actors[i]->isAlive()) {
            delete m_actors[i];
            m_actors.erase(m_actors.begin() + i);
        }
    }
    //update status text at top of screen
    ostringstream oss;
    oss.fill('0');
    oss << "Lives: " << getLives() << "  Level: " << setw(2) << getLevel() << " Points: ";
    oss.fill('0');
    oss << setw(6) << getScore();
    if(getPlayer()->isStarPower()) oss << " StarPower!";
    if(getPlayer()->isShootPower()) oss << " ShootPower!";
    if(getPlayer()->isJumpPower()) oss << " JumpPower!";
    string text = oss.str();
    
    setGameStatText(text);
    
    return GWSTATUS_CONTINUE_GAME;
    

}

void StudentWorld::cleanUp()
{
    //delete player and all actors and clear the vector data structure
    delete m_player;
    for(int i = 0; i < m_actors.size(); i++) {
        delete m_actors[i];
    }
    m_actors.clear();
}

bool StudentWorld::isBlockingObjectAt(int x, int y) const {
    //checks for overlap with Obstacles
    for(int i = 0; i < m_actors.size(); i++) {
        if(!m_actors[i]->isAlive()) continue;
        if(m_actors[i]->isStatic()) {
            if(x + SPRITE_WIDTH - 1 >= m_actors[i]->getX() && x - SPRITE_WIDTH + 1 <= m_actors[i]->getX() && y + SPRITE_WIDTH - 1 >= m_actors[i]->getY() && y - SPRITE_WIDTH + 1 <= m_actors[i]->getY()) {
                return true;
            }
        }
    }
    return false;
}

Actor* StudentWorld::ActorBlockingObjectAt(double x, double y) const {
    //checks overlap with other actors
    for(int i = 0; i < m_actors.size(); i++) {
        if(!m_actors[i]->isAlive()) continue;
        if(m_actors[i]->isStatic()) {
            if(x + SPRITE_WIDTH - 1 >= m_actors[i]->getX() && x - SPRITE_WIDTH + 1 <= m_actors[i]->getX() && y + SPRITE_WIDTH - 1 >= m_actors[i]->getY() && y - SPRITE_WIDTH + 1 <= m_actors[i]->getY()) {
                return m_actors[i];
            }
        }
           
    }
    return nullptr;
}

Actor* StudentWorld::ActorBlockingObjectAtAND(double x, double y) const{
    //checks overlap with player AND other actors
    if((x + SPRITE_WIDTH - 1 >= m_player->getX() && x - SPRITE_WIDTH + 1 <= m_player->getX()) && (y + SPRITE_WIDTH - 1 >= m_player->getY() && y - SPRITE_WIDTH + 1 <= m_player->getY())) return m_player;
    for(int i = 0; i < m_actors.size(); i++) {
        if((x + SPRITE_WIDTH - 1 >= m_actors[i]->getX() && x - SPRITE_WIDTH + 1 <= m_actors[i]->getX()) && (y + SPRITE_WIDTH - 1 >= m_actors[i]->getY() && y - SPRITE_WIDTH + 1 <= m_actors[i]->getY())) return m_actors[i];
    }
    return nullptr;
}

Peach* StudentWorld::getPlayer() const {return m_player;}

void StudentWorld::addActor(Actor* a) { //allows actors to add actors to the world through getWorld() call
    m_actors.push_back(a);
}
