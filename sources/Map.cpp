//
// Created by Vincent PICOT on 01/03/2018.
//

#include "Map.hpp"

Map::Map(const std::string &fileName) :
	_fileName(fileName) {

}

void Map::HardInit()
{
	//_gridSize = new Vector2(10, 10)
}

void Map::Resolve()
{
	for each (auto curVec in _vehicles)
	{
		int time = 0;



		auto tmpRides = GetRidesByStart(time);
		while (tmpRides.size <= 0)
		{
			if (time++ >= _maxTime) break;
			tmpRides = GetRidesByStart(time);
		}
		//TODO choose ride
		auto rideChosen = tmpRides[0];
		//TODO add ride in curVec
		//TODO remove ride from _rides
		std::cout << tmpRides[0] << std::endl;
	}
}