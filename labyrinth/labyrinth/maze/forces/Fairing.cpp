

#include "Fairing.h"

namespace maze {
    namespace forces {

Fairing::Fairing()
{
}


Point Fairing::act(const std::vector<LineLoop>& loops, int loopIdx, int pointIdx, std::function<double(const Point&)> delta) const {
    const Point& pi = loops[loopIdx][pointIdx-1];
    const Point& p  = loops[loopIdx][pointIdx];
    const Point& pj = loops[loopIdx][pointIdx+1];
    const double dpi = delta(pi);
    const double dpj = delta(pj);
    return Point((pi.getX()*dpi + pj.getX()*dpj) / (dpi+dpj) - p.getX(), (pi.getY()*dpi + pj.getY()*dpj) / (dpi+dpj) - p.getY());
}

    }
}
