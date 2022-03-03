//
//  Game.hpp
//  project11
//
//  Created by Margaret Capetz on 1/7/22.
//

#ifndef Game_h
#define Game_h

#include <stdio.h>
//#include "Mesa.h"
//#include "Player.h"
//#include "globals.h"

class Mesa;

int decodeDirection(char dir);

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

        // Mutators
    void play();

  private:
    Mesa* m_mesa;
};



#endif /* Game_hpp */
