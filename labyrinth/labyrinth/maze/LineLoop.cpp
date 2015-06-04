

#include "LineLoop.h"

namespace maze {

LineLoop::LineLoop()
{
}

void LineLoop::split(unsigned pt1, unsigned pt2) {
    insert(begin() + pt2, get(pt1).avgBetween(get(pt2)));
}

void LineLoop::merge(unsigned merged, unsigned lost) {
    at(merged) = get(merged).avgBetween(get(lost));
    erase(begin() + lost);
}

unsigned LineLoop::get_idx(unsigned idx) const {
    return (idx + size()) % size();
}

Point& LineLoop::get(int idx) {
    return at(get_idx(idx));
}

const Point& LineLoop::get(int idx) const {
    return at(get_idx(idx));
}

Point& LineLoop::operator[](unsigned idx) {
    return get(idx);
}

const Point& LineLoop::operator[](unsigned idx) const {
    return get(idx);
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
