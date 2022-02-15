//
//  Peach.hpp
//  SuperPeachSisters
//
//  Created by Margaret Capetz on 2/14/22.
//  Copyright © 2022 UCLA Computer Science Department. All rights reserved.
//

#ifndef Peach_h
#define Peach_h

#include <stdio.h>
#include "Actor.h"

class Peach: public Actor {
public:
    Peach(int startX, int startY);
    virtual void doSomething();
    virtual void bonk();
    
private:
    int m_health;
    bool starPower;
    bool shootPower;
    bool jumpPower;
};

#endif /* Peach_h */
