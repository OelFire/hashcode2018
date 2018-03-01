//
// Created by Vincent PICOT on 01/03/2018.
//

#include <iostream>
#include "Vehicle.hpp"


Vehicle::Vehicle() : _pos(0, 0) {

}


void Vehicle::addRide(std::shared_ptr<Ride> &ride) {
    _rides.push_back(ride);
}

void Vehicle::display() {
	std::cout << _rides.size();
	for (std::vector<std::shared_ptr<Ride>>::iterator it = _rides.begin(); it != _rides.end(); it++) {
		std::cout << " " << (*it)->getRideNumber();
	}
	std::cout << std::endl;
}
