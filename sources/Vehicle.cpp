//
// Created by Vincent PICOT on 01/03/2018.
//

#include "Vehicle.hpp"

void Vehicle::addRide(std::shared_ptr<Ride> &ride) {
    _rides.push_back(ride);
}
