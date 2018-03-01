//
// Created by Vincent PICOT on 01/03/2018.
//

#ifndef HASHCODE2018_RIDE_HPP
#define HASHCODE2018_RIDE_HPP

#include "Vector2.hpp"

class Ride {

public:
    Ride(const Vector2 &_startPos, const Vector2 &_endPos, int _startTime, int _endTime);

private:
    Vector2 _startPos;
    Vector2 _endPos;
    int     _startTime;
    int     _endTime;

public:
    const Vector2 &getStartPos() const;
    const Vector2 &getEndPos() const;
    int getStartTime() const;
    int getEndTime() const;
};


#endif //HASHCODE2018_RIDE_HPP
