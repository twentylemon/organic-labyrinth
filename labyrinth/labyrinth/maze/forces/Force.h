

#ifndef MAZE_FORCES_FORCE_H
#define MAZE_FORCES_FORCE_H

#include <vector>
#include <functional>

#include "../Point.h"
#include "../LineLoop.h"

namespace maze {
    namespace forces {

// superclass for forces in the maze
class Force
{
public:
    Force(double maxMagnitude);

    // returns the displacement vector that the point `loops[loopIdx][pointIdx]` feels
    // given all the other points in it's loop and all the other points
    virtual Point act(const std::vector<LineLoop>& loops, int loopIdx, int pointIdx, std::function<double(const Point&)> delta) const = 0;

    // returns the point given to fit in the range [0..maxMagnitude]
    Point scaleToFit(const Point& point) const;

private:
    double maxMagnitude;
};
    }
}
#endif
