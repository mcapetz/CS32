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
    isFlagReached = false;
    isMarioReached = false;
    
}

StudentWorld::~StudentWorld() {
    if(GWSTATUS_LEVEL_ERROR) return;
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
     //m_level
     ostringstream oss;
     oss.fill('0');
     oss << "level" << setw(2) << getLevel() << ".txt";
     string level_file = oss.str();
//     level_file = "level03.txt";
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
    if(isFlagReached) {
        cout << "flag reached at level " << getLevel() << endl;
        cout << "finished level" << endl;
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
    oss << "Lives: " << getLives() << "  Level: " << setw(2) << getLevel() << "  Points: " << setw(6) << getScore();
    if(getPlayer()->isStarPower()) oss << " StarPower!";
    if(getPlayer()->isShootPower()) oss << " ShootPower!";
    if(getPlayer()->isJumpPower()) oss << " JumpPower!";
    string text = oss.str();
    
    setGameStatText(text);
    
    return GWSTATUS_CONTINUE_GAME;
    
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
//    decLives();
//    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
    cout << "IN CLEANUP " << endl;
    
    cout << "IN CLEANUP 2" << endl;
    delete m_player;
    for(int i = 0; i < m_actors.size(); i++) {
        delete m_actors[i];
    }
    m_actors.clear();
    
    cout << "is m_actors empty? " <<
    m_actors.empty() << endl;
    
    cout << "actors cleared" << endl;
}

bool StudentWorld::isBlockingObjectAt(int x, int y) {
//    if(m_player->getX() == x && m_player->getY() == y) return true;
    for(int i = 0; i < m_actors.size(); i++) {
//        if(m_actors[i]->getX() == x && m_actors[i]->getY() == y) return true;
        if(!m_actors[i]->isAlive()) continue;
        if(m_actors[i]->isStatic()) {
            if(x + SPRITE_WIDTH - 1 >= m_actors[i]->getX() && x - SPRITE_WIDTH + 1 <= m_actors[i]->getX() && y + SPRITE_WIDTH - 1 >= m_actors[i]->getY() && y - SPRITE_WIDTH + 1 <= m_actors[i]->getY()) {
//                cout << "IN BLOCKING" << endl;
//                cout << m_actors[i]->getX() << ", " << m_actors[i]->getY() << endl;
//                cout << x << ", " << y << endl;
                return true;
            }
        }
    }
    return false;
}

Actor* StudentWorld::ActorBlockingObjectAt(double x, double y) {
//    int tempX = int(x);
//    int tempY = int(y);
    for(int i = 0; i < m_actors.size(); i++) {
        if(!m_actors[i]->isAlive()) continue;
        if(m_actors[i]->isStatic()) {
            if(x + SPRITE_WIDTH - 1 >= m_actors[i]->getX() && x - SPRITE_WIDTH + 1 <= m_actors[i]->getX() && y + SPRITE_WIDTH - 1 >= m_actors[i]->getY() && y - SPRITE_WIDTH + 1 <= m_actors[i]->getY()) {
//                cout << "IN BLOCKING" << endl;
//                cout << m_actors[i]->getX() << ", " << m_actors[i]->getY() << endl;
//                cout << x << ", " << y << endl;
                return m_actors[i];
            }
        }
        
//        if((x + SPRITE_WIDTH - 1 >= m_actors[i]->getX() && x - SPRITE_WIDTH + 1 <= m_actors[i]->getX()) || (y + SPRITE_WIDTH - 1 >= m_actors[i]->getY() && y - SPRITE_WIDTH + 1 <= m_actors[i]->getY())) {
//            cout << "IN ACTOR" << endl;
//            cout << m_actors[i]->getX() << ", " << m_actors[i]->getY() << endl;
//            cout << x << ", " << y << endl;
//            return m_actors[i];
//        }
//        if(tempX - tempX%SPRITE_WIDTH == m_actors[i]->getX() && tempY - tempY%SPRITE_HEIGHT == m_actors[i]->getY()){
//            return m_actors[i];
//        }
           
    }
//    cout << "returning null" << endl;
    return nullptr;
}

Actor* StudentWorld::ActorBlockingObjectAtAND(double x, double y) {
    if((x + SPRITE_WIDTH - 1 >= m_player->getX() && x - SPRITE_WIDTH + 1 <= m_player->getX()) && (y + SPRITE_WIDTH - 1 >= m_player->getY() && y - SPRITE_WIDTH + 1 <= m_player->getY())) return m_player;
    for(int i = 0; i < m_actors.size(); i++) {
        if((x + SPRITE_WIDTH - 1 >= m_actors[i]->getX() && x - SPRITE_WIDTH + 1 <= m_actors[i]->getX()) && (y + SPRITE_WIDTH - 1 >= m_actors[i]->getY() && y - SPRITE_WIDTH + 1 <= m_actors[i]->getY())) return m_actors[i];
    }
    //cout << "returning null" << endl;
    return nullptr;
}

Peach* StudentWorld::getPlayer() {return m_player;}

void StudentWorld::addActor(Actor* a) {
    m_actors.push_back(a);
}
