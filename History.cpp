//
//  History.cpp
//  project11
//
//  Created by Margaret Capetz on 1/7/22.
//

#include "History.h"
#include <iostream>

using namespace std;


//public:
//  History(int nRows, int nCols);
//  bool record(int r, int c);
//  void display() const;

History::History(int nRows, int nCols) {
    //The constructor initializes a History object that corresponds to a Mesa with nRows rows and nCols columns.
    *m_mesa = Mesa(nRows, nCols);
}

bool History::record(int r, int c) {
    //The record function is to be called to notify the History object that the player was at row r, column c when the player attacked a neighboring gark. The function returns false if row r, column c is not within the Mesa; otherwise, it returns true after recording what it needs to. This function expects its parameters to be expressed in the same coordinate system as the Mesa (e.g., row 1, column 1 is the upper-left-most position).
    if(r < 1 || r > m_mesa->rows() || c < 1 || c > m_mesa->cols()) {
        return false;
    }
    else {
        //DO STUFF
        m_grid[r][c]++;
        return true;
    }
}

void History::display() const {
    //The display function clears the screen and displays the history grid as the posted programs do. This function does clear the screen, display the history grid, and write an empty line after the history grid; it does not print the Press enter to continue. after the display. (Note to Xcode users: It is acceptable that clearScreen() just writes a newline instead of clearing the screen if you launch your program from within Xcode, since the Xcode output window doesn't have the capability of being cleared.)
    
    // Position (row,col) in the mesa coordinate system is represented in
    // the array element grid[row-1][col-1]
  char grid[MAXROWS][MAXCOLS];
  int r, c;
  
      // Fill the grid with dots
    for (r = 0; r < m_mesa->rows(); r++){
        for (c = 0; c < m_mesa->cols(); c++) {
            if(m_grid[r][c] == 0) {
                grid[r][c] = '.';
            }
            else if(m_grid[r][c] > 0 && m_grid[r][c] < 26) {
                //1 through 25 corresponds to letters A through Y
                grid[r][c] = '@' + m_grid[r][c]; //'@' precedes 'A' in the ascii table
            }
            else {
                //26+ corresponds to the letter Z
                grid[r][c] = 'Z';
            }
        }
    }
      
    

      // Draw the grid
  clearScreen();
  for (r = 0; r < m_mesa->rows(); r++)
  {
      for (c = 0; c < m_mesa->cols(); c++)
          cout << grid[r][c];
      cout << endl;
  }
  cout << endl;

}

History::~History()
{
    delete m_mesa;
}
