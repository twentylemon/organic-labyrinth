

#include "LineLoop.h"

namespace maze {

LineLoop::LineLoop()
{
}

void LineLoop::split(int pt1, int pt2) {
    pt1 = get_idx(pt1);
    pt2 = get_idx(pt2);
    insert(begin() + pt2, std::vector<Point>::at(pt1).avgBetween(std::vector<Point>::at(pt2)));
}

void LineLoop::merge(int merged, int lost) {
    merged = get_idx(merged);
    lost = get_idx(lost);
    std::vector<Point>::at(merged) = std::vector<Point>::at(merged).avgBetween(std::vector<Point>::at(lost));
    erase(begin() + lost);
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

std::ostream& operator<<(std::ostream& out, const LineLoop& loop) {
    for (unsigned i = 0; i < loop.size(); i++) {
        out << "<line x1=\"" << loop[i].getX() << "\" y1=\"" << loop[i].getY() << "\""
            << " x2=\"" << loop[i+1].getX() << "\" y2=\"" << loop[i+1].getY() << "\"/>"
            << std::endl;
    }
    return out;
}
}
