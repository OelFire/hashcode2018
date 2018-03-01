//
// Created by Vincent PICOT on 01/03/2018.
//

#include "Map.hpp"

Map::Map(const std::string &fileName) :
	_fileName(fileName) {

}

void Map::display() {
	for (std::vector<Vehicle>::iterator it = _vehicles.begin(); it != _vehicles.end(); it++) {
		(*it).display();
	}
}

void Map::firstLine(std::ifstream &fileStream) {
	std::string         line;
	int                 rows;
	int                 columns;
	std::stringstream   ss;

	getline(fileStream, line);
	ss.str(line);
	ss >> rows >> columns >> _nbVehicle >> _nbRides >> _bonus >> _maxTime;
	_gridSize.set_x(rows);
	_gridSize.set_y(columns);
#ifdef __DEBUG__
	std::cout << _gridSize.get_x() << " rows, "
		<< _gridSize.get_y() << " columns, "
		<< _nbVehicle << " vehicles, "
		<< _nbRides << " rides, "
		<< _bonus << " bonus and "
		<< _maxTime << " steps" << std::endl;
#endif
}

void Map::createVehicleVector() {
	Vehicle vehicle;

	_vehicles.insert(_vehicles.begin(), _nbVehicle, vehicle);
}

void Map::parseRides(std::ifstream &fileStream) {
	std::string     line;
	int             startPosX;
	int             startPosY;
	Vector2         startPos;
	Vector2         endPos;
	int             endPosX;
	int             endPosY;
	int             startTime;
	int             endTime;
	int             rideNumber = 0;

	while (getline(fileStream, line)) {
		std::stringstream   ss(line);

		ss >> startPosX >> startPosY >> endPosX >> endPosY >> startTime >> endTime;
		startPos.set_x(startPosX);
		startPos.set_y(startPosY);
		endPos.set_x(endPosX);
		endPos.set_y(endPosY);
		_rides.push_back(std::make_shared<Ride>(startPos, endPos, startTime, endTime, rideNumber));
		rideNumber++;
	}

#ifdef __DEBUG__
	std::for_each(_rides.begin(), _rides.end(), [](auto item) {
		std::cout << "ride from [" << item->getStartPos().get_x() << ", " << item->getStartPos().get_y() << "]"
			<< " to [" << item->getEndPos().get_x() << ", " << item->getEndPos().get_y() << "]"
			<< ", earliest start " << item->getStartTime()
			<< ", latest finish " << item->getEndTime()
			<< ", ride id " << item->getRideNumber() << std::endl; });
#endif

}

void Map::parse() {
	std::ifstream   fileStream(_fileName);

	if (!fileStream.is_open()) {
		throw std::exception();
	}
	firstLine(fileStream);
	createVehicleVector();
	parseRides(fileStream);
#ifdef __DEBUG__
	std::cout << "Nb ride from file:" << _nbRides << ", Nb ride from lines" << _rides.size() << std::endl;
#endif
}

void Map::GetRidesByStart(int start)
{
	_map.clear();

	for (size_t i = 0; i < _rides.size(); i++) {
		if (_rides[i]->getStartTime() == start)
			_map.insert(std::pair<int, std::shared_ptr<Ride>>(i, _rides[i]));
	}
}

void Map::Resolve()
{
	for (auto curVec : _vehicles)
	{
		int time = 0;

		GetRidesByStart(time);
		while (_map.size() <= 0)
		{
			if (time++ >= _maxTime) break;
			GetRidesByStart(time);
		}

		std::cout << _map.size() << std::endl;
		std::cout << _map[0]->getRideNumber() << std::endl;
	
		
		
		//TODO choose ride

		curVec.addRide(_map[0]);
		//TODO add ride in curVec
		//TODO remove ride from _rides
	}
}