
#include <string>
#include <fstream>
#include <iostream>

#include "maze/Point.h"
#include "maze/LineLoop.h"
#include "maze/Maze.h"
#include "maze/forces/BrownianMotion.h"
#include "maze/forces/Fairing.h"
#include "maze/forces/LennardJones.h"
#include "maze/forces/Morse.h"

// returns a lineloop of the given shape
maze::LineLoop getCircle(const maze::Point& center, double radius, unsigned numPoints);
maze::LineLoop getSquare(const maze::Point& center, double sideLength, unsigned numPointsPerSide);
maze::LineLoop getBoundingBox(const maze::Point& center, double sideLength, unsigned numPointsPerSide);

// returns the maze to use
maze::Maze makeMaze(int whichOne = 1);

// writes the bounds of the maze into the parameters given
void getBounds(const maze::Maze& laby, double& xmin, double& xmax, double& ymin, double& ymax);

// writes out the maze?
void writeSvg(std::ostream& out, const maze::Maze& laby);
void writeSvg(std::ostream& out, const maze::Maze& laby, double xmin, double xmax, double ymin, double ymax);
