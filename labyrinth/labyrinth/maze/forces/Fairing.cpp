

#include "Fairing.h"

namespace maze {
    namespace forces {

Fairing::Fairing()
{
}


Point Fairing::act(const std::vector<LineLoop>& loops, int loopIdx, int pointIdx, std::function<double(const Point&)> delta) const {
    Point pi = loops[loopIdx][pointIdx-1];
    Point pj = loops[loopIdx][pointIdx+1];
    double dpi = delta(pi);
    double dpj = delta(pj);
    return (pi.scale(dpi / (dpi + dpj)) + pj.scale(dpj / (dpi + dpj))) - loops[loopIdx][pointIdx];
}

    }
}
