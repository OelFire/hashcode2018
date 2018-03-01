//
// Created by Vincent PICOT on 01/03/2018.
//

#ifndef HASHCODE2018_MAP_HPP
#define HASHCODE2018_MAP_HPP

#include <vector>
#include "Vehicle.hpp"

class Map {


private:
    std::vector<Vehicle>                _vehicles;
    std::vector<std::shared_ptr<Ride>>  _rides;
};


#endif //HASHCODE2018_MAP_HPP
