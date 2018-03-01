//
// Created by Vincent PICOT on 01/03/2018.
//

#include "Map.hpp"

int abs(int x) {
    if (x < 0)
        return -x;
    return x;
}

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
#ifdef __DEBUG__
    std::cout << "Vehicle number " << _vehicles.size() << std::endl;
#endif
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
		_rides.push_back(std::make_shared<Ride>(startPos, endPos, startTime, endTime, rideNumber, abs((endPosX - startPosX) + (endPosY - startPosY))));
		rideNumber++;
	}

#ifdef __DEBUG__
	std::for_each(_rides.begin(), _rides.end(), [](auto item) {
		std::cout << "ride from [" << item->getStartPos().get_x() << ", " << item->getStartPos().get_y() << "]"
                  << " to [" << item->getEndPos().get_x() << ", " << item->getEndPos().get_y() << "]"
                  << ", earliest start " << item->getStartTime()
                  << ", latest finish " << item->getEndTime()
                  << ", ride id " << item->getRideNumber()
                  << ", ride time " << item->getRideTime() << std::endl; });
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

void Map::Resolve()
{

    for (auto it = _vehicles.begin(); it != _vehicles.end(); it++)
    {
        //std::cout << "vehicule" << std::endl;

        loop(it);
    }
}

std::shared_ptr<Ride>   Map::GetRidesByStart(const Vector2 &vehiclePos, int &distClosest, int &nb)
{
    std::shared_ptr<Ride> closest;
    bool first = true;
    distClosest = 0;
    int     i = 0;
    nb = -1;

    for (auto it = _rides.begin(); it != _rides.end(); it++) {
        int dist = abs((vehiclePos.get_y() - (*it)->getStartPos().get_y()) + (vehiclePos.get_x() - (*it)->getStartPos().get_x()));
        if (dist == 0) {
            nb = i;
            distClosest = dist;
            return *it;
        }
        if (dist < distClosest || first) {
            distClosest = dist;
            closest = *it;
            nb = i;
            first = false;
        }
        i++;
    }
    return closest;
}


void Map::loop(std::vector<Vehicle>::iterator it)
{
	int time = 0;
	while (time < _maxTime) {

        int dist;
        int nb;
        auto ride = GetRidesByStart(it->getVehiclePos(), dist, nb);
        if (nb == -1)
            break;
        it->addRide(ride);
        it->getVehiclePos().set_x(ride->getEndPos().get_x());
        it->getVehiclePos().set_y(ride->getEndPos().get_y());
        time += dist + ride->getRideTime();
		_rides.erase(_rides.begin() + nb);
	}
}