//
// Created by Vincent PICOT on 01/03/2018.
//

#ifndef HASHCODE2018_VECTOR2_HPP
#define HASHCODE2018_VECTOR2_HPP

class Vector2 {

public:
    Vector2() :
            _x(0),
            _y(0) {
    }

    Vector2(int x, int y) :
            _x(x),
            _y(y) {
    }

private:
    int _x;
    int _y;

public:
    void set_x(int x) {
        _x = x;
    }

    void set_y(int y) {
        _y = y;
    }

    int get_x() const {
        return _x;
    }

    int get_y() const {
        return _y;
    }

};

#endif //HASHCODE2018_VECTOR2_HPP
