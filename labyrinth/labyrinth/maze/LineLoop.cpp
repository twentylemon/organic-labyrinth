

#include "LineLoop.h"

namespace maze {

LineLoop::LineLoop() :
    curve(false)
{
}

void LineLoop::split(int pt1, int pt2) {
    pt1 = get_idx(pt1);
    pt2 = get_idx(pt2);
    insert(begin() + pt2, std::vector<Point>::at(pt1).avgBetween(std::vector<Point>::at(pt2)));
}

void LineLoop::merge(int merged, int lost) {
    if (size() > 3) {
        merged = get_idx(merged);
        lost = get_idx(lost);
        std::vector<Point>::at(merged) = std::vector<Point>::at(merged).avgBetween(std::vector<Point>::at(lost));
        erase(begin() + lost);
    }
}

int LineLoop::get_idx(int idx) const {
    return (idx + size()) % size();
}

Point& LineLoop::at(int idx) {
    return std::vector<Point>::at(get_idx(idx));
}

const Point& LineLoop::at(int idx) const {
    return std::vector<Point>::at(get_idx(idx));
}

Point& LineLoop::operator[](int idx) {
    return at(idx);
}

const Point& LineLoop::operator[](int idx) const {
    return at(idx);
}


int LineLoop::neighbours(int pt1, int pt2) const {
    pt1 = get_idx(pt1);
    pt2 = get_idx(pt2);
    return std::min(std::abs(pt2-pt1), std::min(pt1,pt2)-std::max(pt1,pt2)+(int)size());
}



bool LineLoop::useCurve() const {
    return curve;
}

void LineLoop::setCurve(bool curve) {
    this->curve = curve;
}

std::ostream& operator<<(std::ostream& out, const LineLoop& loop) {
    out << "<path fill=\"transparent\" stroke=\"black\" d=\"M " << loop[0].getX() << " " << loop[0].getY();
    if (loop.useCurve()) {
        for (unsigned i = 1; i < loop.size(); i+=2) {
            out << " Q" << loop[i].getX() << " " << loop[i].getY() << ", " << loop[i+1].getX() << " " << loop[i+1].getY();
        }
    }
    else {
        for (unsigned i = 1; i < loop.size(); i++) {
            out << " L" << loop[i].getX() << " " << loop[i].getY();
        }
    }
    out << " Z\"/>" << std::endl;
    return out;
}
}
