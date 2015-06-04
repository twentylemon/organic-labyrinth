

#include "util.h"

using namespace maze;
using namespace forces;


const double PI = 3.14159265358979323846;


LineLoop getCircle(const Point& center, double radius, unsigned numPoints) {
    LineLoop loop;
    for (double angle = 0.0; angle < 2.0*PI; angle += (2.0*PI/numPoints)) {
        loop.emplace_back(center + Point(radius*std::cos(angle), radius*std::sin(angle)));
    }
    return loop;
}


Maze makeMaze(int whichOne) {
    Maze laby;
    double D = 0.0;
    switch (whichOne) {
    case 1:
        laby.addLoop(getCircle(Point::ORIGIN, 100.0, 10));
        D = laby.getAvgDistance();
        std::cout << "D = " << D << std::endl;
        laby.addForce(new BrownianMotion(D), [](const Point&){ return 0.25; });
        laby.addForce(new Fairing(), [](const Point&){ return 0.5; });
        laby.addForce(new LennardJones(D, 2, D, 2*D), [](const Point&){ return std::pow(10, -30); });
        laby.setSplitThreshold(D);
        laby.setMergeThreshold(0.25*D);
        break;

    default:
        laby.addLoop(getCircle(Point::ORIGIN, 100.0, 100));
    }
    return laby;
}
