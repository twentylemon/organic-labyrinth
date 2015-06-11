
#ifndef MAZE_FORCES_FAIRING_H
#define MAZE_FORCES_FAIRING_H

#include "Force.h"

namespace maze {
    namespace forces {

// applies the Faring force, a local smoothing
// essentially, each point is attracted to the line created by neighbouring points
class Fairing : public Force
{
public:
    Fairing(double maxMag);

    // returns the displacement vector that the point `loops[loopIdx][pointIdx]` feels
    // given all the other points in it's loop and all the other points
    virtual Point act(const std::vector<LineLoop>& loops, int loopIdx, int pointIdx, std::function<double(const Point&)> delta) const;
};
    }
}
#endif
