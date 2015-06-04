

#include "Point.h"

namespace maze {

static const Point origin = Point(0, 0);

Point::Point() :
    x(0),
    y(0),
    locked(false)
{
}

Point::Point(bool locked) :
    x(0),
    y(0),
    locked(locked)
{
}

Point::Point(double x, double y) :
    x(x),
    y(y),
    locked(false)
{
}

Point::Point(double x, double y, bool locked) :
    x(x),
    y(y),
    locked(locked)
{
}


double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

bool Point::isLocked() const {
    return locked;
}

void Point::setX(double x) {
    this->x = x;
}

void Point::setY(double y) {
    this->y = y;
}

void Point::setPosition(double x, double y) {
    setX(x);
    setY(y);
}

void Point::setLocked(bool locked) {
    this->locked = locked;
}


Point Point::avgBetween(const Point& point) const {
    return Point((getX()+point.getX())/2.0, (getY()+point.getY())/2.0);
}

double Point::distance(const Point& point) const {
    return std::pow(getX()-point.getX(), 2) + std::pow(getY()-point.getY(), 2);
}

double Point::magnitude() const {
    return distance(origin);
}
}
