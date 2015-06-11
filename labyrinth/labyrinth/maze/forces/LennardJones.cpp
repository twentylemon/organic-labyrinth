
#include "LennardJones.h"

namespace maze {
    namespace forces {

LennardJones::LennardJones(double maxMag, double dist, int nMin, double zeroPoint, double clampPoint) :
    AttractionForce(maxMag, dist, nMin, zeroPoint, clampPoint)
{
}

double LennardJones::potential(double r) const {
    return std::pow(getZeroPoint()/r, 12) - std::pow(getZeroPoint()/r, 6);
}
    }
}
