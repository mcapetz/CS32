//
//  Game.hpp
//  project11
//
//  Created by Margaret Capetz on 1/7/22.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Mesa.h"


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
