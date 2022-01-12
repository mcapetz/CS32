//
//  Gark.hpp
//  project11
//
//  Created by Margaret Capetz on 1/7/22.
//

#ifndef Gark_h
#define Gark_h

#include <stdio.h>
//#include "Mesa.h"

class Mesa;  // This is needed to let the compiler know that Mesa is a
             // type name, since it's mentioned in the Gark declaration.

class Gark
{
  public:
        // Constructor
    Gark(Mesa* mp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();
    bool getAttacked(int dir);

  private:
    Mesa* m_mesa;
    int   m_row;
    int   m_col;
    int   m_health;
};

#endif /* Gark_hpp */
