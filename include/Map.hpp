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
#include <algorithm>
#include "Vehicle.hpp"

#define __DEBUG__

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

	std::map<int, std::shared_ptr<Ride>> _map;

private:
	void    firstLine(std::ifstream &fileStream);
	void    createVehicleVector();
	void    parseRides(std::ifstream &fileStream);

	void	GetRidesByStart(int);
	void	loop(std::vector<Vehicle>::iterator);

public:
	void    Resolve();
	void    parse();
	void	display();
};


#endif //HASHCODE2018_MAP_HPP
