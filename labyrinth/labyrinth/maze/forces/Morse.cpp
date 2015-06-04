

#include "Morse.h"

namespace maze {
    namespace forces {

Morse::Morse(double dist, int nMin, double zeroPoint, double clampPoint) :
    AttractionForce(dist, nMin, zeroPoint, clampPoint)
{
}

double Morse::potential(double r) const {
    return std::exp(2.0*(getZeroPoint()-r)) - std::exp(getZeroPoint()-r);
}
    }
}
