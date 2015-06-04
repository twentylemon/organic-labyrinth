
#ifndef MAZE_FORCES_ATTRACTICEFORCE_H
#define MAZE_FORCES_ATTRACTICEFORCE_H

#include "Force.h"

namespace maze {
    namespace forces {

// super class for all attraction based forces; the only difference between
// them all is the potential function
class AttractionForce : public Force
{
public:
    AttractionForce(double dist, int nMin, double zeroPoint, double clampPoint);

    // average starting distances to each other point
    double getDist() const;

    // returns the number of neighbours to ignore, in each direction
    int getNMin() const;

    // returns the distance at which the potential is zero (naturally)
    double getZeroPoint() const;
    
    // returns the squared distance at which to clamp to potential to zero
    double getClampPoint() const;

    // sets the new average starting displacement from other points
    void setDist(double dist);

    // sets the new number of neighbours to ignore
    void setNMin(int nMin);

    // sets the new zero point, where the potential is naturally zero
    // note: this is NOT SQUARED distance
    void setZeroPoint(double zeroPoint);

    // sets the new clamp point, points further than this will be clamped to a potential of 0
    // note: this is a SQUARED distance
    void setClampPoint(double clampPoint);

    // returns the potential value at distance r
    virtual double potential(double r) const = 0;

    // returns the displacement vector that the point `loops[loopIdx][pointIdx]` feels
    // given all the other points in it's loop and all the other points
    virtual Point act(const std::vector<LineLoop>& loops, int loopIdx, int pointIdx, std::function<double(const Point&)> delta) const;

private:
    // the "big D" distance in the paper; average starting distances to each other point
    double dist;

    // the number of neighbours to ignore, in each direction
    int nMin;

    // the point at which the potential is zero (naturally)
    double zeroPoint;

    // the point at which to clamp to potential to zero
    double clampPoint;
};
    }
}
#endif
