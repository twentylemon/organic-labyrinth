

#include "maze/Point.h"
#include "maze/LineLoop.h"
#include "maze/Maze.h"
#include "maze/forces/BrownianMotion.h"
#include "maze/forces/Fairing.h"
#include "maze/forces/LennardJones.h"
#include "maze/forces/Morse.h"

// returns a lineloop that is a circle with the parameters given
maze::LineLoop getCircle(const maze::Point& center, double radius, unsigned numPoints);

// returns the maze to use
maze::Maze makeMaze(int whichOne = 1);
