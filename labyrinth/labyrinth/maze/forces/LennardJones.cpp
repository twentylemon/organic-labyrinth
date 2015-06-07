
#include "LennardJones.h"

namespace maze {
    namespace forces {

LennardJones::LennardJones(double dist, int nMin, double zeroPoint, double clampPoint) :
    AttractionForce(dist, nMin, zeroPoint, clampPoint)
{
}

double LennardJones::potential(double r) const {
    //std::cout << "jones(" << r << "): " << (std::pow(getZeroPoint()/r, 12) - std::pow(getZeroPoint()/r, 6)) << std::endl;
    return std::pow(getZeroPoint()/r, 12) - std::pow(getZeroPoint()/r, 6);
}
    }
}
