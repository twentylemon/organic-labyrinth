
#include "Force.h"

namespace maze {
    namespace forces {
   
Force::Force(double maxMagnitude) :
    maxMagnitude(maxMagnitude)
{
}

Point Force:: scaleToFit(const Point& point) const {
    if (point.magnitude() > maxMagnitude) {
        return point.normalize(maxMagnitude);
    }
    return point;
}

    }
}
