

#ifndef MAZE_FORCES_BROWNIANMOTION_H
#define MAZE_FORCES_BROWNIANMOTION_H

#include <random>

#include "Force.h"

namespace maze {
    namespace forces {

// brownian motion force: exerts a random displacement on the point at each time step
class BrownianMotion : public Force
{
public:
    // sets the guassian parameters to mean of 0, stddev of 1
    BrownianMotion(double maxMag, double dist);
    
    // sets the guassian parameters to those given
    BrownianMotion(double maxMag, double dist, double mean, double stddev);

    // average starting distances to each other point
    double getDist() const;

    // returns the mean of the guassian
    double getMean() const;

    // returns the stddev of the guassian
    double getStddev() const;

    // sets the seed for the random device
    void setSeed(unsigned seed);

    // sets the seed for the random device a truly random number
    void initSeed();

    // sets the new mean of the guassian
    void setMean(double mean);

    // sets the new stddev of the guassian
    void setStddev(double stddev);

    // sets the new average starting displacement from other points
    void setDist(double dist);
    
    // returns the displacement vector that the point `loops[loopIdx][pointIdx]` feels
    // given all the other points in it's loop and all the other points
    virtual Point act(const std::vector<LineLoop>& loops, int loopIdx, int pointIdx, std::function<double(const Point&)> delta) const;

private:
    // the "big D" distance in the paper; average starting distances to each other point
    double dist;

    // the normal distribution to use for adding random displacements to points
    mutable std::normal_distribution<double> guassian;  // mutable gen number as const... whatever

    // the random device to use as the generator for the guassian
    mutable std::default_random_engine gen;
};
    }
}
#endif
