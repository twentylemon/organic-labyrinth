

#include "Maze.h"

namespace maze {

using forces::Force;

Maze::Maze() :
    mergeThreshold(1.0),
    splitThreshold(5.0),
    delta([](const Point&){ return 1.0; })
{
}


Maze::Maze(double mergeThreshold, double splitThreshold, std::function<double(const Point&)> delta) :
    mergeThreshold(mergeThreshold),
    splitThreshold(splitThreshold),
    delta(delta)
{
}


void Maze::addForce(Force* force, std::function<double(const Point&)> field) {
    forces.emplace_back(force, field);
}

void Maze::addLoop(const LineLoop& loop) {
    loops.emplace_back(loop);
    copy.emplace_back(loop);
}

double Maze::getMergeThreshold() const {
    return mergeThreshold;
}

double Maze::getSplitThreshold() const {
    return splitThreshold;
}

int Maze::getNumPoints() const {
    int sum = 0;
    std::for_each(loops.begin(), loops.end(), [&sum](const LineLoop& loop){
        sum += loop.size();
    });
    return sum;
}

void Maze::setDelta(std::function<double(const Point&)> delta) {
    this->delta = delta;
}
    
void Maze::setMergeThreshold(double mergeThreshold) {
    this->mergeThreshold = mergeThreshold;
}

void Maze::setSplitThreshold(double splitThreshold) {
    this->splitThreshold = splitThreshold;
}

const std::vector<LineLoop>& Maze::getLoops() const {
    return loops;
}

double Maze::getAvgDistance() const {
    avgDist = 0.0;
    int num = 0;
    for (unsigned i = 0; i < loops.size(); i++) {
        num += loops[i].size();
        for (unsigned j = 0; j < loops[i].size(); j++) {
            avgDist += loops[i][j].distance(loops[i][j+1]);
        }
    }
    avgDist = avgDist / num;
    return avgDist;
}


void Maze::calcEpoch() {
    // apply the forces
    std::for_each(forces.begin(), forces.end(), [&](std::pair<Force*,std::function<double(const Point&)>> forcePair){
        for (unsigned i = 0; i < loops.size(); i++) {
            for (unsigned j = 0; j < loops[i].size(); j++) {
                Point act = forcePair.first->act(loops, i, j, delta).scale(forcePair.second(loops[i][j]));
                double max = avgDist / (forces.size() + loops.size() - 1);
                if (act.magnitude() > max) {
                    act = act.normalize(max);
                }
                copy[i][j] += act;
            }
        }
    });

    // split/merge points if they fall in their threshold values
    for (unsigned i = 0; i < copy.size(); i++) {
        for (unsigned j = 0; j < copy[i].size(); j++) {
            double distance = copy[i][j].distance(copy[i][j+1]);
            if (distance > getSplitThreshold()) {
                copy[i].split(j, j+1);
                j++;    // skip checking the newly created point
            }
            else if (distance < getMergeThreshold()) {
                copy[i].merge(j, j+1);
                //j--;  // check the next point as well? likely not required
            }
        }
    }
}

void Maze::applyForces() {
    calcEpoch();
    loops = copy;
}
}
