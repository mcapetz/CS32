//
//  testCarMap.cpp
//  CS32-HW1
//
//  Created by Margaret Capetz on 1/15/22.
//

#include "CarMap.h"
    #include <iostream>
    #include <cassert>
    using namespace std;

int main() {
        
    CarMap m;
    assert(m.fleetSize() == 0);
    m.addCar("LICENSE1");
    m.print();
    assert(m.miles("LICENSE1") == 0);
    assert(m.fleetSize() == 1);
    m.addCar("LICENSE2");
    assert(m.fleetSize() == 2);
    assert(m.miles("X") == -1);
    assert(m.addCar("LICENSE1") == false);
    assert(m.fleetSize() == 2);
    m.print();
    m.drive("LICENSE2", 5);
    assert(m.miles("LICENSE2") == 5);
    m.drive("LICENSE2", 5);
    assert(m.miles("LICENSE2") == 10);
    
    cout << "passed all test from testCarMap" << endl;
    
    return 0;
}
