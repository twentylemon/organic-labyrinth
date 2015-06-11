
#ifndef MAZE_FORCES_LENNARDJONES_H
#define MAZE_FORCES_LENNARDJONES_H

#include <cmath>

#include "AttractionForce.h"

namespace maze {
    namespace forces {

// applies an attractive and repulsive force between points
class LennardJones : public AttractionForce
{
public:
    LennardJones(double maxMag, double dist, int nMin, double zeroPoint, double clampPoint);

    // returns the potential value at distance r
    virtual double potential(double r) const;
};
    }
}
#endif
