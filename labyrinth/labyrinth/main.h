
#include <string>
#include <fstream>
#include <iostream>
#include <GL/glut.h>
#include <algorithm>

#include "maze/Point.h"
#include "maze/LineLoop.h"
#include "maze/Maze.h"
#include "maze/forces/BrownianMotion.h"
#include "maze/forces/Fairing.h"
#include "maze/forces/LennardJones.h"
#include "maze/forces/Morse.h"

typedef struct glob {
    int it;             // iteration count
    maze::Maze laby;    // the maze
    double XMIN, XMAX, YMIN, YMAX;  // extends of the maze
    
    int window;
    bool paused;
    bool step;

    int windowWidth;
    int windowHeight;

    bool editMode;
    bool lockPoint;
    double minDistance;
    bool leftClicking;
} Global;

extern Global g;


void displayFunc();

// menu.cpp
void keyboardFunc(unsigned char key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void motionFunc(int x, int y);

// returns a lineloop of the given shape
maze::LineLoop getCircle(const maze::Point& center, double radius, unsigned numPoints, bool curve = false);
maze::LineLoop getSquare(const maze::Point& center, double sideLength, unsigned numPointsPerSide, bool curve = false);
maze::LineLoop getBoundingBox(const maze::Point& center, double width, double height, unsigned numPointsPerSide, bool curve = false);
maze::LineLoop getBoundingBox(const maze::Point& center, double sideLength, unsigned numPointsPerSide, bool curve = false);

// returns the maze to use
maze::Maze makeMaze(int whichOne = 1);

// writes the bounds of the maze into the parameters given
void getBounds(const maze::Maze& laby, double& xmin, double& xmax, double& ymin, double& ymax);

// writes out the maze
void writeSvg(std::ostream& out, const maze::Maze& laby);
void writeSvg(std::ostream& out, const maze::Maze& laby, double xmin, double xmax, double ymin, double ymax);
