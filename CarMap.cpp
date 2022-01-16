//
//  CarMap.cpp
//  CS32-HW1
//
//  Created by Margaret Capetz on 1/15/22.
//

#include "CarMap.h"

CarMap::CarMap() {
    
}       // Create an empty car map.

bool CarMap::addCar(std::string license) {
    if(m_map.contains(license)) {
        return false;
    }
    if(m_map.insert(license, 0)) {
        return true;
    }
    return false;
}
  // If a car with the given license plate is not currently in the map,
  // and there is room in the map, add an entry for that car recording
  // that it has been driven 0 miles, and return true.  Otherwise,
  // make no change to the map and return false.

double CarMap::miles(std::string license) const { //NEEDS WORK
    if(!m_map.contains(license)) {
        return -1;
    }
    ValueType miles;
    m_map.get(license, miles);
    return miles;
}
  // If a car with the given license plate is in the map, return how
  // many miles it has been driven; otherwise, return -1.

bool CarMap::drive(std::string license, double distance) {
    if(!m_map.contains(license) || (distance < 0)) {
        return false;
    }
    ValueType miles;
    m_map.get(license, miles);
    distance += miles;
    return true;
}
  // If no car with the given license plate is in the map or if
  // distance is negative, make no change to the map and return
  // false.  Otherwise, increase by the distance parameter the number
  // of miles the indicated car has been driven and return true.

int CarMap::fleetSize() const {
    return m_map.size();
} // Return the number of cars in the CarMap.

void CarMap::print() const {
    for(int i = 0; i < m_map.size(); i++) {
        KeyType key;
        ValueType value;
        m_map.get(i, key, value);
        std::cout << key << " " << value << std::endl;
    }
}
  // Write to cout one line for every car in the map.  Each line
  // consists of the car's license plate, followed by one space,
  // followed by the number of miles that car has been driven.  Write
  // no other text.  The lines need not be in any particular order.
