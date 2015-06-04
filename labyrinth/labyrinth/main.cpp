

#include "main.h"

using namespace maze;

Maze laby = makeMaze();

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLineWidth(3.0);
    glColor3b(0, 0, 0);
    displayMaze(laby);
    glFlush();
}

// timer function, apply forces each step
void timerFunc(int i) {
    std::cout << laby.getLoops().front().size() << std::endl;
    laby.applyForces();
    glutPostRedisplay();
    glutTimerFunc(1000, timerFunc, i+1);
    /*
    std::cout << laby.getLoops().front() << std::endl;
    system("pause");
    */
}


int main(int argc, char** argv) {
    int width = 300, height = 300;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(30, 30);
    glutCreateWindow("organic labyrinth");

    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION | GL_MATRIX_MODE);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glOrtho(-width/2, width/2, height/2, -height/2, 0, 1);

    glutDisplayFunc(displayFunc);
    glutTimerFunc(1000, timerFunc, 0);

    glutMainLoop();
    return 0;
}
