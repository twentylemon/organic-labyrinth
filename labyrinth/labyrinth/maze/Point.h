

#ifndef MAZE_POINT_H
#define MAZE_POINT_H

#include <cmath>

namespace maze {

// a single point in the labyrinth structure
class Point
{
public:
    // sets the position to the origin and locked to false
    Point();

    // sets the position to the origin and locked to the value given
    Point(bool locked);

    // sets the position given and locked to false
    Point(double x, double y);

    // sets the position and locked to the values given
    Point(double x, double y, bool locked);

    // returns the x position of this point
    double getX() const;

    // returns the y position of this point
    double getY() const;

    // returns true if this point is locked in place
    bool isLocked() const;

    // sets the new x position of this point
    void setX(double x);

    // sets the new y position of this point
    void setY(double y);

    // sets the new position of this point
    void setPosition(double x, double y);

    // sets whether or not this point should be locked in place
    void setLocked(bool locked);


    // returns a point at the average location between this point and the other point given
    Point avgBetween(const Point& point) const;

    // returns the squared euclidean distance between this and the other point
    double distance(const Point& point) const;

    // returns the squared magnitude of this point as a vector from the origin
    double magnitude() const;

private:
    // position of this point
    double x, y;

    // true to lock this point in place, no forces should affect it
    bool locked;
};
}
#endif
