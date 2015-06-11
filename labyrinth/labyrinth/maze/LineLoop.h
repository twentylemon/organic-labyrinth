

#ifndef MAZE_LINELOOP_H
#define MAZE_LINELOOP_H

#include <vector>
#include <iostream>
#include <algorithm>

#include "Point.h"

namespace maze {

// list of points in the maze structure
class LineLoop : public std::vector<Point>
{
public:
    LineLoop();

    // splits the two points into 3, placing a third point at their average position
    void split(int pt1, int pt2);

    // merges the point `lost` into `merged`
    void merge(int merged, int lost);

    // returns true to use curves
    bool useCurve() const;

    // sets whether or not to use curves
    void setCurve(bool curve);

    // returns true if all the points in the loop are locked
    bool allLocked() const;

    // returns the point in the loop at the given index, the index is automatically cyclicized
    Point& at(int idx);
    const Point& at(int idx) const;
    Point& operator[](int idx);
    const Point& operator[](int idx) const;

    // returns the number of points between pt1 and pt2
    int neighbours(int pt1, int pt2) const;

    // write to stream
    friend std::ostream& operator<<(std::ostream& out, const LineLoop& loop);

private:
    // returns the cyclic index of `idx`
    int get_idx(int idx) const;

    // to loop or straight line when `<<`
    bool curve;
};
}
#endif
