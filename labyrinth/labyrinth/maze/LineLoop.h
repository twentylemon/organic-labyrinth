

#ifndef MAZE_LINELOOP_H
#define MAZE_LINELOOP_H

#include <vector>
#include <iostream>

#include "Point.h"

namespace maze {

// list of points in the maze structure
class LineLoop : public std::vector<Point>
{
public:
    LineLoop();

    // splits the two points into 3, placing a third point at their average position
    void split(unsigned pt1, unsigned pt2);

    // merges the point `lost` into `merged`
    void merge(unsigned merged, unsigned lost);

    // returns the point in the loop at the given index, the index is automatically cyclicized
    Point& at(int idx);
    const Point& at(int idx) const;
    Point& operator[](unsigned idx);
    const Point& operator[](unsigned idx) const;

    // write to stream
    friend std::ostream& operator<<(std::ostream& out, const LineLoop& loop);

private:
    // returns the cyclic index of `idx`
    unsigned get_idx(unsigned idx) const;
};
}
#endif
