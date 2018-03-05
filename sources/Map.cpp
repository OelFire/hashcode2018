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
/*#ifdef __DEBUG__
	std::cout << _gridSize.get_x() << " rows, "
		<< _gridSize.get_y() << " columns, "
		<< _nbVehicle << " vehicles, "
		<< _nbRides << " rides, "
		<< _bonus << " bonus and "
		<< _maxTime << " steps" << std::endl;
#endif*/
}

void Map::createVehicleVector() {
	Vehicle vehicle;

	_vehicles.insert(_vehicles.begin(), _nbVehicle, vehicle);
/*#ifdef __DEBUG__
    std::cout << "Vehicle number " << _vehicles.size() << std::endl;
#endif*/
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
/*
#ifdef __DEBUG__
	std::for_each(_rides.begin(), _rides.end(), [](auto item) {
		std::cout << "ride from [" << item->getStartPos().get_x() << ", " << item->getStartPos().get_y() << "]"
                  << " to [" << item->getEndPos().get_x() << ", " << item->getEndPos().get_y() << "]"
                  << ", earliest start " << item->getStartTime()
                  << ", latest finish " << item->getEndTime()
                  << ", ride id " << item->getRideNumber()
                  << ", ride time " << item->getRideTime() << std::endl; });
#endif
	*/
}

void Map::parse() {
	std::ifstream   fileStream(_fileName);

	if (!fileStream.is_open()) {
		throw std::exception();
	}
	firstLine(fileStream);
	createVehicleVector();
	parseRides(fileStream);
	/*
#ifdef __DEBUG__
	std::cout << "Nb ride from file:" << _nbRides << ", Nb ride from lines" << _rides.size() << std::endl;
#endif*/
}

int getDist(const Vector2 &a, const Vector2 &b) {
    return abs((a.get_y() - b.get_y()) + (a.get_x() - a.get_x()));
}

std::shared_ptr<Ride>   Map::GetRidesByStart(const Vehicle &vehicle, int &nb)
{
    std::shared_ptr<Ride>   closest;
    bool                    first = true;
    int                     distClosest = 0;
    int                     i = 0;

    nb = -1;

    for (auto it = _rides.begin(); it != _rides.end(); it++, i++) {
        int dist = getDist(vehicle.getVehiclePos(), (*it)->getStartPos());
        if (vehicle.getTime() + dist > (*it)->getStartTime()) {
        //if (vehicle.getTime() + dist + (*it)->getRideTime() > (*it)->getEndTime()) {
            continue;
        }
        if (dist < distClosest || first) {
            distClosest = dist;
            closest = *it;
            nb = i;
            first = false;
        }
    }
    if (nb == -1) {
        i = 0;
        distClosest = 0;
        first = true;
        nb = -1;
        for (auto it = _rides.begin(); it != _rides.end(); it++, i++) {
            int dist = abs((vehicle.getVehiclePos().get_y() - (*it)->getStartPos().get_y()) + (vehicle.getVehiclePos().get_x() - (*it)->getStartPos().get_x()));
            if (vehicle.getTime() + dist + (*it)->getRideTime() > (*it)->getEndTime()) {
                continue;
            }
            if (dist < distClosest || first) {
                distClosest = dist;
                closest = *it;
                nb = i;
                first = false;
            }
        }
    }
    return closest;
}

void Map::Resolve()
{
    Vector2 orig(0, 0);
    std::sort(_rides.begin(), _rides.end(), [&orig](auto i, auto j){

       return i->getStartTime() < j->getStartTime() || (i->getStartTime() == j->getStartTime() && getDist(orig, i->getStartPos()) < getDist(orig, j->getStartPos()));
    });
    /*std::for_each(_rides.begin(), _rides.end(), [](auto item) {
        std::cout << "ride from [" << item->getStartPos().get_x() << ", " << item->getStartPos().get_y() << "]"
                  << " to [" << item->getEndPos().get_x() << ", " << item->getEndPos().get_y() << "]"
                  << ", earliest start " << item->getStartTime()
                  << ", latest finish " << item->getEndTime()
                  << ", ride id " << item->getRideNumber()
                  << ", ride time " << item->getRideTime() << std::endl; });*/
    for (auto it = _vehicles.begin(); it != _vehicles.end(); it++)
    {
        it->addRide(_rides.front());
        it->addTime(getDist(it->getVehiclePos(), _rides.front()->getStartPos()));
        it->addTime(_rides.front()->getRideTime());
        it->getVehiclePos().set_x(_rides.front()->getEndPos().get_x());
        it->getVehiclePos().set_y(_rides.front()->getEndPos().get_y());
        _rides.erase(_rides.begin());
    }
    while (_rides.size() > 0) {
        int toto = _rides.size();
        for (auto it = _vehicles.begin(); it != _vehicles.end() && _rides.size() > 0; it++)
        {
            int nb;

            auto ride = GetRidesByStart(*it, nb);
            if (nb == -1) {
                continue;
            }
            /*if (ride->getRideNumber() == 1354) {
                std::cout << "ok" << std::endl;
            }*/
            if (it->getTime() + getDist(it->getVehiclePos(), ride->getStartPos()) + ride->getRideTime() > _maxTime) {
                continue;
            }
            it->addRide(ride);
            it->addTime(getDist(it->getVehiclePos(), ride->getStartPos()));
            it->addTime(ride->getRideTime());
            it->getVehiclePos().set_x(ride->getEndPos().get_x());
            it->getVehiclePos().set_y(ride->getEndPos().get_y());
            _rides.erase(_rides.begin() + nb);
        }
        if (toto == _rides.size())
            break;
    }
}



