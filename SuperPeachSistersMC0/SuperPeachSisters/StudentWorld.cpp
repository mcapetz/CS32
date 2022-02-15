#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
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

int StudentWorld::init()
{
     Level lev(assetPath());
     string level_file = "level01.txt";
     Level::LoadResult result = lev.loadLevel(level_file);
     if (result == Level::load_fail_file_not_found)
     cerr << "Could not find level01.txt data file" << endl;
     else if (result == Level::load_fail_bad_format)
     cerr << "level01.txt is improperly formatted" << endl;
     else if (result == Level::load_success)
     {
     cerr << "Successfully loaded level" << endl;
     Level::GridEntry ge;
         for(int i = 0; i < 32; i++) {
             for(int j = 0; j < 32; j++)  {
                 ge = lev.getContentsOf(i, j);
                 
                 switch(ge) {
                     case Level::empty:
                         cerr << "Location " << i << "," << j << "is empty" << endl;
                         break;
                     case Level::peach:
                         m_player = new Peach(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                         break;
                     case Level::koopa:
                         //
                         break;
                     case Level::goomba:
                         //
                         break;
                     case Level::piranha:
                         //
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
                         //
                         break;
                     case Level::flag:
                         //
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
}

bool StudentWorld::isBlockingObjectAt(int x, int y) {
    if(m_player->getX() == x && m_player->getY() == y) return true;
    for(int i = 0; i < m_actors.size(); i++) {
        if(m_actors[i]->getX() == x && m_actors[i]->getY() == y) return true;
    }
    return false;
}
