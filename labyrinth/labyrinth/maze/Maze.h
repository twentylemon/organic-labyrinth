

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include <vector>
#include <utility>
#include <algorithm>
#include <functional>

#include "LineLoop.h"
#include "forces/Force.h"

namespace maze {

class Maze
{
public:
    Maze();

    // sets the thresholds and the delta function, if given
    Maze(double mergeThreshold, double splitThreshold, std::function<double(const Point&)> delta = [](){ return 1.0; });

    // adds a new force to apply at the end of each epoch
    void addForce(forces::Force* force, std::function<double(const Point&)> field = [](const Point&){ return 1.0; });

    // adds a new loop of points
    void addLoop(const LineLoop& loop);

    // applies each of the forces to each point in the structure
    void applyForces();

    // returns the merge thresold
    double getMergeThreshold() const;

    // returns the split threshold
    double getSplitThreshold() const;

    // returns the number of points
    int getNumPoints() const;

    // sets the delta function
    void setDelta(std::function<double(const Point&)> delta);
    
    // sets the merge threshold; if two points are closer than this, they are merged into one
    void setMergeThreshold(double mergeThreshold);

    // sets the split threshold; if two points are further than this, they are split into three
    void setSplitThreshold(double splitThreshold);

    // returns all the points in the maze
    std::vector<LineLoop>& getLoops();
    const std::vector<LineLoop>& getLoops() const;

    // returns D - the average distance between points
    double getAvgDistance() const;

    void addToLast(double x, double y, bool lock);
    void addToLast(const Point& point);

private:
    // returns the new point sets after an epoch
    void calcEpoch();


    // the forces that act on each particle each tick
    std::vector<std::pair<forces:: Force*, std::function<double(const Point&)>>> forces;

    // all of the points
    std::vector<LineLoop> loops;

    // copy of loops for `applyForces()`
    std::vector<LineLoop> copy;

    // the delta function
    std::function<double(const Point&)> delta;

    // merge and split thresholds
    double mergeThreshold, splitThreshold;
};
}
#endif
