//
// Created by Vincent PICOT on 01/03/2018.
//

#ifndef HASHCODE2018_VEHICLE_HPP
#define HASHCODE2018_VEHICLE_HPP


#include <memory>
#include <vector>
#include "Ride.hpp"

class Vehicle {

public:
    Vehicle();

private:
    std::vector< std::shared_ptr<Ride>>     _rides;
    Vector2                                 _pos;
    int                                     _time;

public:
    void addRide(std::shared_ptr<Ride> &ride);
	void display();

    const Vector2 &getVehiclePos() const { return _pos; }
    Vector2 &getVehiclePos() { return _pos; }

    int getTime() const;
    void addTime(int time);
};


#endif //HASHCODE2018_VEHICLE_HPP
