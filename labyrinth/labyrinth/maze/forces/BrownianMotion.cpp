

#include "BrownianMotion.h"

namespace maze {
    namespace forces {

BrownianMotion::BrownianMotion(double dist) :
    dist(dist),
    guassian(std::normal_distribution<double>())
{
#ifndef _DEBUG
    initSeed();
#endif
}
    
BrownianMotion::BrownianMotion(double dist, double mean, double stddev) :
    dist(dist),
    guassian(std::normal_distribution<double>(mean, stddev))
{
#ifndef _DEBUG
    initSeed();
#endif
}

double BrownianMotion::getDist() const {
    return dist;
}

double BrownianMotion::getMean() const {
    return guassian.mean();
}

double BrownianMotion::getStddev() const {
    return guassian.stddev();
}

void BrownianMotion::setSeed(unsigned seed) {
    gen = std::default_random_engine(seed);
}

void BrownianMotion::initSeed() {
    std::random_device rd;
    setSeed(rd());
}

void BrownianMotion::setMean(double mean) {
    guassian = std::normal_distribution<double>(mean, getStddev());
}

void BrownianMotion::setStddev(double stddev) {
    guassian = std::normal_distribution<double>(getMean(), stddev);
}

void BrownianMotion::setDist(double dist) {
    this->dist = dist;
}

Point BrownianMotion::act(const std::vector<LineLoop>& loops, int loopIdx, int pointIdx, std::function<double(const Point&)> delta) const {
    const double d = getDist() * delta(loops[loopIdx][pointIdx]);
    return Point(d * guassian(gen), d * guassian(gen));
}
    }
}
