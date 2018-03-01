//
// Created by Vincent PICOT on 01/03/2018.
//

#include "Ride.hpp"

Ride::Ride(const Vector2 &startPos,
           const Vector2 &endPos,
           int startTime,
           int endTime,
           int rideNumber) :
        _startPos(startPos),
        _endPos(endPos),
        _startTime(startTime),
        _endTime(endTime),
        _rideNumber(rideNumber){

}

const Vector2 &Ride::getStartPos() const {
    return _startPos;
}

const Vector2 &Ride::getEndPos() const {
    return _endPos;
}

int Ride::getStartTime() const {
    return _startTime;
}

int Ride::getEndTime() const {
    return _endTime;
}

int Ride::getRideNumber() const {
    return _rideNumber;
}
