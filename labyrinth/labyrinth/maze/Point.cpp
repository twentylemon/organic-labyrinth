

#include "Point.h"

namespace maze {

const Point Point::ORIGIN = Point(0.0, 0.0);

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


Point Point::operator+(const Point& rhs) const {
    return Point(getX()+rhs.getX(), getY()+rhs.getY());
}

Point Point::add(const Point& rhs) const {
    return *this + rhs;
}

Point Point::operator-(const Point& rhs) const {
    return Point(getX()-rhs.getX(), getY()-rhs.getY());
}

Point Point::subtract(const Point& rhs) const {
    return *this - rhs;
}

Point Point::scale(double scale) const {
    return Point(scale*getX(), scale*getY());
}

Point Point::normalize(double length) const {
    double len = magnitude();
    if (len > 0) {
        return scale(length / len);
    }
    return *this;
}

bool Point::operator==(const Point& rhs) const {
    return getX() == rhs.getX() && getY() == rhs.getY();
}

double Point::dot(const Point& rhs) const {
    return getX()*rhs.getX() + getY()*rhs.getY();
}

Point& Point::operator+=(const Point& rhs) {
    setPosition(getX()+rhs.getX(), getY()+rhs.getY());
    return *this;
}

Point& Point::operator-=(const Point& rhs) {
    setPosition(getX()-rhs.getX(), getY()-rhs.getY());
    return *this;
}

Point Point::avgBetween(const Point& point) const {
    return Point((getX()+point.getX())/2.0, (getY()+point.getY())/2.0);
}

double Point::distance(const Point& point) const {
    return std::sqrt(std::pow(getX()-point.getX(), 2) + std::pow(getY()-point.getY(), 2));
}

double Point::magnitude() const {
    return distance(ORIGIN);
}

Point Point::closestOnSegment(const Point& start, const Point& end) const {
    Point segment = end.subtract(start);
    double dist = subtract(start).dot(segment) / std::pow(segment.magnitude(), 2);
    if (dist < 0) {
        return start;
    }
    else if (dist > 1) {
        return end;
    }
    return start + segment.scale(dist);
}

std::string Point::toString() const {
    return "(" + std::to_string(getX()) + "," + std::to_string(getY()) + ")";
}
}
