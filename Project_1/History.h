//
//  History.hpp
//  project11
//
//  Created by Margaret Capetz on 1/7/22.
//

#ifndef History_h
#define History_h

#include <stdio.h>
#include "globals.h"
//DO NOT INCLUDE MESA.H OR U WILL HAVE CIRCULAR PROBLEMS

class Mesa;

class History
    {
      public:
        History(int nRows, int nCols);
        //~History();
        
        bool record(int r, int c);
        void display() const;
        
        
      private:
        char m_grid[MAXROWS][MAXCOLS] = {0}; //to keep record
        int m_rows;
        int m_cols;
    };


#endif /* History_hpp */
