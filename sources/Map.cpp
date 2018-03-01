//
// Created by Vincent PICOT on 01/03/2018.
//

#include "Map.hpp"

Map::Map(const std::string &fileName) :
        _fileName(fileName) {

}

std::map<int, std::shared_ptr<Ride>>	&Map::getRidesByStart(int start)
{
	std::map<int, std::shared_ptr<Ride>> map;

	for (int i = 0; i < _rides.size(); i++) {
		if (_rides[i]->getStartTime() == start)
			map.insert(std::pair<int, std::shared_ptr<Ride>>(i, _rides[i]));
	}
	return map;
}

