
#include <fstream>
#include <iostream>
#include <GL/glut.h>
#include <algorithm>

#include "maze/Maze.h"

#include "util.h"

typedef struct glob {
    int it;             // iteration count
    maze::Maze laby;    // the maze
    double XMIN, XMAX, YMIN, YMAX;  // extends of the maze
    
    int window;
    bool paused;
    bool step;

    int windowSize;

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
