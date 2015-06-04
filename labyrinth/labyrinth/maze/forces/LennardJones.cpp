
#include "LennardJones.h"

namespace maze {
    namespace forces {

LennardJones::LennardJones(double dist, int nMin, double clampPoint, double zeroPoint) :
    AttractionForce(dist, nMin, zeroPoint, clampPoint)
{
}

double LennardJones::potential(double r) const {
    return std::pow(getZeroPoint()/r, 12) - std::pow(getZeroPoint()/r, 6);
}
    }
}
