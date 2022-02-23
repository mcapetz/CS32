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
  bool isBlockingObjectAt(int x, int y);
  Actor* ActorBlockingObjectAt(double x, double y);
  Actor* ActorBlockingObjectAtAND(double x, double y);
  Peach* getPlayer();
  void addActor(Actor* a);

private:
    Peach* m_player;
    std::vector<Actor*> m_actors;
};

#endif // STUDENTWORLD_H_
