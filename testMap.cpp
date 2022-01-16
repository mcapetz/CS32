//
//  main.cpp
//  CS32-HW1
//
//  Created by Margaret Capetz on 1/15/22.
//

#include "Map.h"
#include <cassert>

using namespace std;

    int main()
    {
        Map mm;
            mm.insert("Little Ricky", 3.206);
            mm.insert("Ethel", 3.538);
            mm.insert("Ricky", 3.350);
            mm.insert("Lucy", 2.956);
            mm.insert("Ethel", 3.538);
            mm.insert("Fred", 2.956);
            mm.insert("Lucy", 2.956);
            assert(mm.size() == 5);  // duplicate "Ethel" and "Lucy" were not added
            string x;
            double y;
            mm.get(0, x, y);
            assert(x == "Ethel");  // "Ethel" is greater than exactly 0 items in mm
            mm.get(4, x, y);
            assert(x == "Ricky");  // "Ricky" is greater than exactly 4 items in mm
            mm.get(2, x, y);
            assert(x == "Little Ricky");  // "Little Ricky" is greater than exactly 2 items in mm
            assert(y == 3.206);  // the value corresponding to the key "Little Ricky"
        cout << "all tests passed" << endl;
    }

