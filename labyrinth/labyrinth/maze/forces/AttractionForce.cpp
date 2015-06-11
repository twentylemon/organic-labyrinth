
#include "AttractionForce.h"

namespace maze {
    namespace forces {

AttractionForce::AttractionForce(double maxMag, double dist, int nMin, double zeroPoint, double clampPoint) :
    Force(maxMag),
    dist(dist),
    nMin(nMin),
    zeroPoint(zeroPoint),
    clampPoint(clampPoint)
{
}

double AttractionForce::getDist() const {
    return dist;
}

int AttractionForce::getNMin() const {
    return nMin;
}

double AttractionForce::getZeroPoint() const {
    return zeroPoint;
}
    
double AttractionForce::getClampPoint() const {
    return clampPoint;
}

void AttractionForce::setDist(double dist) {
    this->dist = dist;
}

void AttractionForce::setNMin(int nMin) {
    this->nMin = nMin;
}

void AttractionForce::setZeroPoint(double zeroPoint) {
    this->zeroPoint = zeroPoint;
}

void AttractionForce::setClampPoint(double clampPoint) {
    this->clampPoint = clampPoint;
}

Point AttractionForce::act(const std::vector<LineLoop>& loops, int loopIdx, int pointIdx, std::function<double(const Point&)> delta) const {
    Point force = Point(0, 0);
    double d = delta(loops[loopIdx][pointIdx]);
    for (int i = 0; i < (int)loops.size(); i++) {
        for (int j = 0; j < (int)loops[i].size(); j++) {
            // only consider points not on our loop, or those further than nMin points away from us
            if (i != loopIdx || loops[i].neighbours(pointIdx, j) > getNMin()) {
                const Point x = loops[loopIdx][pointIdx].closestOnSegment(loops[i][j], loops[i][j+1]);
                const Point f = loops[loopIdx][pointIdx] - x;
                // ignore if beyond the clamp distance
                if (f.magnitude() < getClampPoint()*std::min(d, delta(x))){
                    force += f.scale(potential(f.magnitude() / d) / f.magnitude());
                }
            }
        }
    }
    return force;
}
    }
}
