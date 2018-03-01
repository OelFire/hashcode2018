//
// Created by Vincent PICOT on 01/03/2018.
//

#ifndef HASHCODE2018_MAP_HPP
#define HASHCODE2018_MAP_HPP

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <map>
#include <iostream>
#include "Vehicle.hpp"

#define __DEBUG__

class Map {

public:
	Map(const std::string &fileName);
	void HardInit();
	void Resolve();
	std::map<int, std::shared_ptr<Ride>> GetRidesByStart(int) {
		return std::map<int, std::shared_ptr<Ride>>();
	};
private:
	std::string                         _fileName;
	std::vector<Vehicle>                _vehicles;
	std::vector<std::shared_ptr<Ride>>  _rides;

    Vector2                 _gridSize;
    unsigned int            _nbVehicle;
    unsigned int            _nbRides;
    unsigned int            _bonus;
    unsigned long long int  _maxTime;

private:
    void    firstLine(std::ifstream &fileStream);
    void    createVehicleVector();
    void    parseRides(std::ifstream &fileStream);

public:

    void    parse();

public:
	std::map<int, std::shared_ptr<Ride>>	&getRidesByStart(int);
};


#endif //HASHCODE2018_MAP_HPP
