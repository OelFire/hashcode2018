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
		auto rides = GetRidesByStart(0);
		//TODO check if ride exists
		//TODO choose ride
		auto rideChosen = rides[0];
		std::cout << rides[0] << std::endl;
	}
}