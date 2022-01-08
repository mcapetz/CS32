//
//  History.cpp
//  project11
//
//  Created by Margaret Capetz on 1/7/22.
//

#include "History.h"
#include <iostream>
#include "Mesa.h"

using namespace std;


//TODO:
//  History(int nRows, int nCols);
//  bool record(int r, int c);
//  void display() const;

History::History(int nRows, int nCols) {
    //The constructor initializes a History object that corresponds to a Mesa with nRows rows and nCols columns.
    m_rows = nRows;
    m_cols = nCols;
    
}

//destructor

//History::~History()
//{
//    delete m_mesa;
//}

bool History::record(int r, int c) {
    //The record function is to be called to notify the History object that the player was at row r, column c when the player attacked a neighboring gark. The function returns false if row r, column c is not within the Mesa; otherwise, it returns true after recording what it needs to. This function expects its parameters to be expressed in the same coordinate system as the Mesa (e.g., row 1, column 1 is the upper-left-most position).
    if(r < 1 || r > m_rows || c < 1 || c > m_cols) {
        return false;
    }
    else {
        //DO STUFF
        m_grid[r][c] = m_grid[r][c] + 1;
//        cout << "row " << r << endl;
//        cout << "col " << c << endl;
//        cout << m_grid[r][c] << endl;
        return true;
    }
    
    return false;
}

void History::display() const {
    //The display function clears the screen and displays the history grid as the posted programs do. This function does clear the screen, display the history grid, and write an empty line after the history grid; it does not print the Press enter to continue. after the display. (Note to Xcode users: It is acceptable that clearScreen() just writes a newline instead of clearing the screen if you launch your program from within Xcode, since the Xcode output window doesn't have the capability of being cleared.)
    
    // Position (row,col) in the mesa coordinate system is represented in
    // the array element grid[row-1][col-1]
  char grid[MAXROWS][MAXCOLS];
  int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < m_rows; r++)
        for (c = 0; c < m_cols; c++)
            grid[r][c] = '.';
            
    
    //m_grid[3][5] = grid[4-1][6-1]
  
      // Fill the grid
    for (r = 1; r <= m_rows; r++){
        for (c = 1; c <= m_cols; c++) {
            if(m_grid[r][c] > 0 && m_grid[r][c] < 26) {
//                cout << "row " << r << endl;
//                cout << "col " << c << endl;
//                cout << '@' + m_grid[r][c] << endl;
                //1 through 25 corresponds to letters A through Y
                grid[r-1][c-1] = '@' + m_grid[r][c]; //'@' precedes 'A' in the ascii table
            }
            else if(m_grid[r][c] >= 26) {
                //26+ corresponds to the letter Z
                grid[r-1][c-1] = 'Z';
            }
        }
    }
      
    

      // Draw the grid
  clearScreen();
  for (r = 0; r < m_rows; r++)
  {
      for (c = 0; c < m_cols; c++)
          cout << grid[r][c];
      cout << endl;
  }
  cout << endl;
//
}


