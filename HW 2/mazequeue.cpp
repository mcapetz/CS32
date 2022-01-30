//
//  main.cpp
//  CS32-HW2
//
//  Created by Margaret Capetz on 1/27/22.
//

#include <iostream>
#include <string>
#include <queue>

using namespace std;



class Coord
        {
          public:
            Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
            int r() const { return m_r; }
            int c() const { return m_c; }
          private:
            int m_r;
            int m_c;
        };

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr, sc));
    maze[sr][sc] = '#';
    while(!coordQueue.empty()) {
        Coord x = coordQueue.front();
        int xr = x.r();
        int xc = x.c();
        coordQueue.pop();
                
        if(xr == er && xc == ec) {
            return true;
        }
                
        if(xc > 0 && maze[xr][xc-1] == '.') { //west
            coordQueue.push(Coord(xr, xc-1));
            maze[xr][xc-1] = '#';
        }
        if(xr < nRows-1 && maze[xr+1][xc] == '.') { //south
            coordQueue.push(Coord(xr+1, xc));
            maze[xr+1][xc] = '#';
        }
        if(xc < nCols-1 && maze[xr][xc+1] == '.') { //east
            coordQueue.push(Coord(xr, xc+1));
            maze[xr][xc+1] = '#';
        }
        if(xr > 0 && maze[xr-1][xc] == '.') { //north
            coordQueue.push(Coord(xr-1, xc));
            maze[xr-1][xc] = '#';
        }
    }
    return false;
}

int main()
        {
            string maze[10] = {
                "XXXXXXXXXX",
                "X.X..X...X",
                "X....XXX.X",
                "X.XXXX.X.X",
                "X......XXX",
                "X.XX.X...X",
                "X.X..X.X.X",
                "X.X.XXXX.X",
                "X.X...X..X",
                "XXXXXXXXXX"
            };
        
            if (pathExists(maze, 10,10, 4,6, 1,1))
                cout << "Solvable!" << endl;
            else
                cout << "Out of luck!" << endl;
        }
