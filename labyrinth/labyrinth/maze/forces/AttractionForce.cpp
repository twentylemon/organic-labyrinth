
#include "AttractionForce.h"

namespace maze {
    namespace forces {

AttractionForce::AttractionForce(double dist, int nMin, double zeroPoint, double clampPoint) :
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
    double sumX = 0.0, sumY = 0.0;
    double d = getDist() * delta(loops[loopIdx][pointIdx]);
    for (int i = 0; i < (int)loops.size(); i++) {
        for (int j = 0; j < (int)loops[i].size(); j++) {
            if (i != loopIdx || std::max(std::abs(j-pointIdx), std::abs(j-pointIdx+1)) > getNMin()) {
                // calculate x, the point closest to pointIdx on the line j|j+1
                // calculate p = pointIdx - x
                // sumX += p.getX()/p.magnitude() * potential(p.magnitude() / d)
                // sumY += p.getY()/p.magnitude() * potential(p.magnitude() / d)
            }
        }
    }
    return Point(sumX, sumY);
}
    }
}
