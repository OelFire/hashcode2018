//
// Created by Vincent PICOT on 01/03/2018.
//

#ifndef HASHCODE2018_VEHICLE_HPP
#define HASHCODE2018_VEHICLE_HPP


#include <memory>
#include <vector>
#include "Ride.hpp"

class Vehicle {


private:
    std::vector< std::shared_ptr<Ride>>   _rides;

public:
    void addRide(std::shared_ptr<Ride> &ride);
	void display();
};


#endif //HASHCODE2018_VEHICLE_HPP
