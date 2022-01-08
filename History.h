//
//  History.hpp
//  project11
//
//  Created by Margaret Capetz on 1/7/22.
//

#ifndef History_hpp
#define History_hpp

#include <stdio.h>
#include "globals.h"

class History
    {
      public:
        History(int nRows, int nCols);
//        ~History();
        
        bool record(int r, int c);
        void display() const;
        
        
      private:
        char m_grid[MAXROWS][MAXCOLS] = {0};
    };


#endif /* History_hpp */
