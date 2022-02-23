#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

StudentWorld::~StudentWorld() {
    if(GWSTATUS_LEVEL_ERROR) return;
    delete m_player;
    for(int i = 0; i < m_actors.size(); i++) {
        delete m_actors[i];
    }
}

int StudentWorld::init()
{
     Level lev(assetPath());
     //m_level
     ostringstream oss;
     oss.fill('0');
     oss << "level" << setw(2) << getLevel() << ".txt";
     string level_file = oss.str();
     Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found) {
       cerr << "Could not find level01.txt data file" << endl;
       return GWSTATUS_LEVEL_ERROR;
    }
     else if (result == Level::load_fail_bad_format) {
         cerr << "level01.txt is improperly formatted" << endl;
         return GWSTATUS_LEVEL_ERROR;
     }
     else if (result == Level::load_success)
     {
     cerr << "Successfully loaded level" << endl;
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
                     case Level::star_goodie_block:
                         //
                         break;
                     case Level::mushroom_goodie_block:
                         //
                         break;
                     case Level::flower_goodie_block:
                         //
                         break;
                     case Level::pipe:
                         m_actors.push_back(new Pipe(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                         break;
                     case Level::flag:
                         m_actors.push_back(new Flag(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                         break;
                     case Level::mario:
                         //
                         break;
                 }
             }
         }
     }

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_player->doSomething();
    for(int i = 0; i < m_actors.size(); i++) {
        m_actors[i]->doSomething();
    }
    
    if(!m_player->isAlive()) {
        playSound(SOUND_PLAYER_DIE);
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    //if peach reaches flag
    //if peach reaches mario
    //delete dead actors
    for(int i = 0; i < m_actors.size(); i++) {
        if(!m_actors[i]->isAlive()) {
            delete m_actors[i];
        }
    }
    //update status text at top of screen
    
    return GWSTATUS_CONTINUE_GAME;
    
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
//    decLives();
//    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
    StudentWorld::~StudentWorld();
}

bool StudentWorld::isBlockingObjectAt(int x, int y) {
//    if(m_player->getX() == x && m_player->getY() == y) return true;
    for(int i = 0; i < m_actors.size(); i++) {
//        if(m_actors[i]->getX() == x && m_actors[i]->getY() == y) return true;
        if(m_actors[i]->isStatic()) {
            if(x + SPRITE_WIDTH - 1 >= m_actors[i]->getX() && x - SPRITE_WIDTH + 1 <= m_actors[i]->getX() && y + SPRITE_WIDTH - 1 >= m_actors[i]->getY() && y - SPRITE_WIDTH + 1 <= m_actors[i]->getY()) return true;
        }
    }
    return false;
}

Actor* StudentWorld::ActorBlockingObjectAt(double x, double y) {
//    if(m_player->getX() == x && m_player->getY() == y) return true;
    for(int i = 0; i < m_actors.size(); i++) {
//        if(m_actors[i]->getX() == x && m_actors[i]->getY() == y) return true;
        if(x + SPRITE_WIDTH - 1 >= m_actors[i]->getX() && x - SPRITE_WIDTH + 1 <= m_actors[i]->getX() && y + SPRITE_WIDTH - 1 >= m_actors[i]->getY() && y - SPRITE_WIDTH + 1 <= m_actors[i]->getY()) return m_actors[i];
    }
    return nullptr;
}

Peach* StudentWorld::getPlayer() {return m_player;}

void StudentWorld::addActor(Actor* a) {
    m_actors.push_back(a);
}
