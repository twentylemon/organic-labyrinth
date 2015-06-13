

#include "main.h"

using namespace maze;

Global g;

int MAZE_DEFAULT = 1;
int MAZE_COMPARE = 2;
int MAZE_INSIDE = 3;
int MAZE_DELTA = 4;

// displays all of the line loops in the maze given
void displayMaze(const Maze& maze) {
    std::vector<LineLoop> loops = maze.getLoops();
    std::for_each(loops.begin(), loops.end(), [](const LineLoop& loop){
        if (!loop.empty()) {
            glBegin(GL_LINE_LOOP);
            std::for_each(loop.begin(), loop.end(), [](const Point& point){
                glVertex2d(point.getX(), point.getY());
            });
            glVertex2d(loop.front().getX(), loop.front().getY());
            glEnd();
        }
    });
}


// glut display func, displays the maze at each step
void displayFunc() {
    glMatrixMode(GL_PROJECTION | GL_MATRIX_MODE);
    glLoadIdentity();

    if (!g.paused || g.step) {
        g.laby.applyForces();
        g.it++;
    }
    getBounds(g.laby, g.XMIN, g.XMAX, g.YMIN, g.YMAX);
    glOrtho(g.XMIN, g.XMAX, g.YMIN, g.YMAX, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    displayMaze(g.laby);
    if (g.step) {
        keyboardFunc('i', 0, 0);
        g.step = false;
    }

    glFlush();
    glutSwapBuffers();
}


int main(int argc, char** argv) {
    g.windowWidth = 1200;
    g.windowHeight = 600;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(g.windowWidth, g.windowHeight);
    glutInitWindowPosition(30, 30);
    g.window = glutCreateWindow("organic labyrinth");

    g.editMode = false;
    g.lockPoint = false;
    g.leftClicking = false;
    g.minDistance = 8.0;

    g.paused = true;
    g.step = false;
    g.it = 0;
    g.laby = makeMaze(MAZE_COMPARE);
    getBounds(g.laby, g.XMIN, g.XMAX, g.YMIN, g.YMAX);

    glClearColor(1, 1, 1, 1);
    glColor3b(0, 0, 0);
    glLineWidth(3.0);

    glMatrixMode(GL_PROJECTION | GL_MATRIX_MODE);
    glLoadIdentity();
    glOrtho(g.XMIN, g.XMAX, g.YMIN, g.YMAX, 0, 1);
    
    glutDisplayFunc(displayFunc);
    glutIdleFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);

    keyboardFunc('t', 0, 0);

    glutMainLoop();
    return 0;
}
