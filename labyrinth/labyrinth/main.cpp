

#include "main.h"

using namespace maze;

Maze laby = makeMaze();

double XMIN, XMAX, YMIN, YMAX;

int it = 0;

// displays all of the line loops in the maze given
void displayMaze(const Maze& maze) {
    std::vector<LineLoop> loops = maze.getLoops();
    std::for_each(loops.begin(), loops.end(), [](const LineLoop& loop){
        glBegin(GL_LINE_LOOP);
        std::for_each(loop.begin(), loop.end(), [](const Point& point){
            glVertex2d(point.getX(), point.getY());
        });
        glVertex2d(loop.front().getX(), loop.front().getY());
        glEnd();
    });
}


// glut display func, displays the maze at each step
void displayFunc() {
    glMatrixMode(GL_PROJECTION | GL_MATRIX_MODE);
    glLoadIdentity();
    glOrtho(XMIN, XMAX, YMIN, YMAX, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLineWidth(3.0);
    glColor3b(0, 0, 0);

    laby.applyForces();
    getBounds(laby, XMIN, XMAX, YMIN, YMAX);
    std::cout << "it: " << (++it) << ", " << laby.getNumPoints() << " points "
        << "(" << XMIN << "," << YMIN << ") --> (" << XMAX << "," << YMAX << ")"
        << std::endl;

    displayMaze(laby);
    glFlush();
    glutSwapBuffers();
}

// on key press, exit and save file
void keyboardFunc(unsigned char key, int x, int y) {
    glutLeaveMainLoop();
    std::cout << "leaving main loop, writing svg...";
    std::ofstream out("../../output.svg");
    writeSvg(out, laby, XMIN, XMAX, YMIN, YMAX);
    out.close();
    std::cout << "done!" << std::endl;
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(30, 30);
    glutCreateWindow("organic labyrinth");
    
    getBounds(laby, XMIN, XMAX, YMIN, YMAX);
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION | GL_MATRIX_MODE);
    glLoadIdentity();
    glOrtho(XMIN, XMAX, YMIN, YMAX, 0, 1);
    
    glutDisplayFunc(displayFunc);
    glutIdleFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);

    glutMainLoop();
    return 0;
}
