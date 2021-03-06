#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <vector>
#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  bool isBlockingObjectAt(int x, int y) const;
  Actor* ActorBlockingObjectAt(double x, double y) const;
  Actor* ActorBlockingObjectAtAND(double x, double y) const;
  Peach* getPlayer() const;
  void addActor(Actor* a);
  void reachedFlag();
  void reachedMario();

private:
    Peach* m_player;
    std::vector<Actor*> m_actors;
    int m_score;
    bool isFlagReached;
    bool isMarioReached;
    
};

#endif // STUDENTWORLD_H_
