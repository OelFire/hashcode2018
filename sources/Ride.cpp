//
// Created by Vincent PICOT on 01/03/2018.
//

#include "Ride.hpp"

Ride::Ride(const Vector2 &_startPos,
           const Vector2 &_endPos,
           int _startTime,
           int _endTime) :
        _startPos(_startPos),
        _endPos(_endPos),
        _startTime(_startTime),
        _endTime(_endTime) {

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
