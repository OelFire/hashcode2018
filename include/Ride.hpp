//
// Created by Vincent PICOT on 01/03/2018.
//

#ifndef HASHCODE2018_RIDE_HPP
#define HASHCODE2018_RIDE_HPP

#include "Vector2.hpp"

class Ride {

public:
    Ride(const Vector2 &startPos, const Vector2 &endPos, int startTime, int endTime, int rideNumber);

private:
    Vector2 _startPos;
    Vector2 _endPos;
    int     _startTime;
    int     _endTime;
    int     _rideNumber;

public:
    const Vector2 &getStartPos() const;
    const Vector2 &getEndPos() const;
    int getStartTime() const;
    int getEndTime() const;
    int getRideNumber() const;
};


#endif //HASHCODE2018_RIDE_HPP
