

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
        laby.addForce(new BrownianMotion(1), [](const Point&){ return 3; });
        laby.addForce(new Fairing(), [](const Point&){ return 0.25; });
        laby.addForce(new LennardJones(D, 2, 2*D, 5*D), [](const Point&){ return 1; });
        laby.setSplitThreshold(1.25*D);
        laby.setMergeThreshold(0.25*D);
        break;

    default:
        laby.addLoop(getCircle(Point::ORIGIN, 100.0, 100));
    }
    return laby;
}


void writeSvg(std::ostream& out, const Maze& laby) {
    double xmin = 10E100, xmax = -10E100, ymin = 10E100, ymax = -10E100;
    std::for_each(laby.getLoops().begin(), laby.getLoops().end(), [&xmin,&xmax,&ymin,&ymax](const LineLoop& loop){
        xmin = std::min((*std::min_element(loop.begin(), loop.end(), [](const Point& p1, const Point& p2){
            return p1.getX() < p2.getX();
        })).getX(), xmin);
        xmax = std::max((*std::max_element(loop.begin(), loop.end(), [](const Point& p1, const Point& p2){
            return p1.getX() < p2.getX();
        })).getX(), xmax);
        ymin = std::min((*std::min_element(loop.begin(), loop.end(), [](const Point& p1, const Point& p2){
            return p1.getY() < p2.getY();
        })).getY(), ymin);
        ymax = std::max((*std::max_element(loop.begin(), loop.end(), [](const Point& p1, const Point& p2){
            return p1.getY() < p2.getY();
        })).getY(), ymax);
    });
    double width = xmax - xmin;
    double height = ymax - ymin;
    out << "<?xml version=\"1.0\"?>" << std::endl
        << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << std::endl
        << "<svg width=\"" << 600 << "\" height=\"" << 600 << "\" "
        << "viewBox=\"" << xmin << " " << ymin << " " << width << " " << height << "\" "
        << "version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;

    std::for_each(laby.getLoops().begin(), laby.getLoops().end(), [&out](const LineLoop& loop) {
        out << loop;
    });
    out << "</svg>" << std::endl;
}
