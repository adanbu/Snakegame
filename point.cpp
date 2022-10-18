#include "snakey.h"

Point::Point(int xp, int yp) :x(xp), y(yp) {};
Point::Point(const Point& other) {
    this->x = other.x;
    this->y = other.y;
}

//void operator=(Point& other);
