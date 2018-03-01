//
// Created by Vincent PICOT on 01/03/2018.
//

#ifndef HASHCODE2018_MAP_HPP
#define HASHCODE2018_MAP_HPP

#include <vector>
#include <string>
#include <map>
#include "Vehicle.hpp"

class Map {

public:
    Map(const std::string &fileName);

private:
    std::string                         _fileName;
    std::vector<Vehicle>                _vehicles;
    std::vector<std::shared_ptr<Ride>>  _rides;

    Vector2                 _gridSize;
    unsigned int            _nbVehicle;
    unsigned int            _nbRides;
    unsigned int            _bonus;
    unsigned long long int  _maxTime;

public:
	std::map<int, std::shared_ptr<Ride>>	&getRidesByStart(int);
};


#endif //HASHCODE2018_MAP_HPP
