
#ifndef MAZE_FORCES_MORSE_H
#define MAZE_FORCES_MORSE_H

#include <cmath>

#include "AttractionForce.h"

namespace maze {
    namespace forces {

// different form of attraction/repulsion
class Morse : public AttractionForce
{
public:
    Morse(double maxMag, double dist, int nMin, double zeroPoint, double clampPoint);

    // returns the potential value at distance r
    virtual double potential(double r) const;
};
    }
}
#endif
