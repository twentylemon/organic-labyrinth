

#include "util.h"

using namespace maze;
using namespace forces;


const double PI = 3.14159265358979323846;


LineLoop getCircle(const Point& center, double radius, unsigned numPoints, bool curve) {
    LineLoop loop;
    for (double angle = 0.0; angle < 2.0*PI; angle += (2.0*PI/numPoints)) {
        loop.emplace_back(center + Point(radius*std::cos(angle), radius*std::sin(angle)));
    }
    loop.setCurve(curve);
    return loop;
}

LineLoop getSquare(const Point& center, double sideLength, unsigned numPointsPerSide, bool curve) {
    LineLoop loop;
    auto off = [sideLength,numPointsPerSide](unsigned i){ return sideLength*(double)i/numPointsPerSide; };
    for (unsigned i = 0; i < numPointsPerSide; i++) {
        loop.emplace_back(center + Point(sideLength/2, sideLength/2 - off(i)));
    }
    for (unsigned i = 0; i < numPointsPerSide; i++) {
        loop.emplace_back(center + Point(sideLength/2 - off(i), -sideLength/2));
    }
    for (unsigned i = 0; i < numPointsPerSide; i++) {
        loop.emplace_back(center + Point(-sideLength/2, -sideLength/2 + off(i)));
    }
    for (unsigned i = 0; i < numPointsPerSide; i++) {
        loop.emplace_back(center + Point(-sideLength/2 + off(i), sideLength/2));
    }
    loop.setCurve(curve);
    return loop;
}

LineLoop getBoundingBox(const Point& center, double sideLength, unsigned numPointsPerSide, bool curve) {
    LineLoop loop = getSquare(center, sideLength, numPointsPerSide);
    for (unsigned i = 0; i < loop.size(); i++) {
        loop[i].setLocked(true);
    }
    loop.setCurve(curve);
    return loop;
}


Maze makeMaze(int whichOne) {
    Maze laby;
    double D = 0.0;
    switch (whichOne) {
    case 1:
        laby.addLoop(getCircle(Point::ORIGIN, 100.0, 50, true));
        laby.addLoop(getBoundingBox(Point::ORIGIN, 300, 50));
        D = laby.getAvgDistance();
        std::cout << "D = " << D << std::endl;
        laby.addForce(new BrownianMotion(D/3, 1), [](const Point&){ return 2; });
        laby.addForce(new Fairing(D/3), [](const Point&){ return 0.25; });
        laby.addForce(new LennardJones(D/3, D, 2, 2*D, 5*D), [](const Point&){ return 1; });
        laby.setSplitThreshold(1.4*D);
        laby.setMergeThreshold(0.25*D);
        break;

    case 2:
        laby.addLoop(getCircle(Point(200, 0), 100, 50, true));
        laby.addLoop(getCircle(Point(-200, 0), 100.0, 50, false));
        laby.addLoop(getBoundingBox(Point::ORIGIN, 800, 10));
        D = laby.getAvgDistance();
        std::cout << "D = " << D << std::endl;
        laby.addForce(new BrownianMotion(D/1.5, 1));
        laby.addForce(new Fairing(D/24));
        laby.addForce(new LennardJones(D/3, D, 2, 2*D, 5*D));
        laby.setSplitThreshold(1.4*D);
        laby.setMergeThreshold(0.25*D);
        break;

    default:
        laby.addLoop(getCircle(Point::ORIGIN, 100.0, 100));
    }
    return laby;
}


void getBounds(const Maze& laby, double& xmin, double& xmax, double& ymin, double& ymax) {
    xmin = ymin = std::numeric_limits<double>::max();
    xmax = ymax = std::numeric_limits<double>::min();
    std::for_each(laby.getLoops().begin(), laby.getLoops().end(), [&xmin,&xmax,&ymin,&ymax](const LineLoop& loop){
        if (!loop.empty()) {
            auto x = std::minmax_element(loop.begin(), loop.end(), [](const Point& p1, const Point& p2){
                return p1.getX() < p2.getX();
            });
            auto y = std::minmax_element(loop.begin(), loop.end(), [](const Point& p1, const Point& p2){
                return p1.getY() < p2.getY();
            });
            xmin = std::min(x.first->getX(), xmin);
            xmax = std::max(x.second->getX(), xmax);
            ymin = std::min(y.first->getY(), ymin);
            ymax = std::max(y.second->getY(), ymax);
        }
    });
}

void writeSvg(std::ostream& out, const Maze& laby) {
    double xmin, xmax, ymin, ymax;
    getBounds(laby, xmin, xmax, ymin, ymax);
    writeSvg(out, laby, xmin, xmax, ymin, ymax);
}

void writeSvg(std::ostream& out, const Maze& laby, double xmin, double xmax, double ymin, double ymax) {
    double width = xmax - xmin;
    double height = ymax - ymin;
    out << "<?xml version=\"1.0\"?>" << std::endl
        << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << std::endl
        << "<svg width=\"" << 600 << "\" height=\"" << 600 << "\" "
        << "viewBox=\"" << xmin << " " << ymin << " " << width << " " << height << "\" "
        << "version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;

    auto flip = [](double y){ return -y; };
    std::for_each(laby.getLoops().begin(), laby.getLoops().end(), [&out,flip](const LineLoop& loop) {
        out << "<path fill=\"transparent\" stroke=\"black\" d=\"M " << loop[0].getX() << " " << flip(loop[0].getY());
        if (loop.useCurve()) {
            for (unsigned i = 1; i < loop.size(); i+=2) {
                out << " Q" << loop[i].getX() << " " << flip(loop[i].getY()) << ", " << loop[i+1].getX() << " " << flip(loop[i+1].getY());
            }
        }
        else {
            for (unsigned i = 1; i < loop.size(); i++) {
                out << " L" << loop[i].getX() << " " << flip(loop[i].getY());
            }
        }
        out << " Z\"/>" << std::endl;
        //out << loop;
    });
    out << "</svg>" << std::endl;
}
