
#include "main.h"

using namespace maze;
using namespace forces;

/*
    e - turn of edit mode; clear maze; keep a bounding box of the window size
    k - toggle locked points
    l - add a new loop
    o - toggle current loop curve
    f - finalize maze
    i - info
    n - step one frame
    p - pause/unpause
    s - save svg
    q - quit program
    t - controls
*/
void keyboardFunc(unsigned char key, int x, int y) {
    std::ofstream out;
    double D;
    switch (key) {
    case 't':
        std::cout << "controls (press the key in the graphics window):" << std::endl
            << " e - clear maze; turn edit mode on" << std::endl
            << " k - toggle placing locked points in edit mode" << std::endl
            << " l - add a new loop in edit mode" << std::endl
            << " o - toggle using bezier curves when drawing the current curve; default off" << std::endl
            << " f - finalize maze; must be called before running the custom simulation" << std::endl
            << " i - display basic labyrinth information" << std::endl
            << " n - step one iteration" << std::endl
            << " p - toggle running the simulation" << std::endl
            << " s - save the screen to \"output.svg\"" << std::endl
            << " q - quit" << std::endl
            << " t - display this message" << std::endl << std::endl;
        break;

    case 'e':
        g.laby = Maze();
        g.laby.addLoop(getBoundingBox(Point::ORIGIN, (double)g.windowWidth, (double)g.windowHeight, 10));
        std::cout << "edit mode is on; maze cleared, bounding box kept" << std::endl
            << "left-click drag to draw many points; right click to draw one point" << std::endl;
        keyboardFunc('l', x, y);
        g.editMode = true;
        g.step = false;
        if (!g.paused) {
            keyboardFunc('p', x, y);
        }
        glutPostRedisplay();
        break;
        
    case 'k':
        g.lockPoint = !g.lockPoint;
        std::cout << "newly added points will now be " << (g.lockPoint ? "locked" : "not locked") << std::endl;
        break;

    case 'l':
        g.laby.addLoop(LineLoop());
        std::cout << "empty loop added to the maze; clicking will add to loop #" << g.laby.getLoops().size() << std::endl;
        break;

    case 'o':
        g.laby.flipLastCurve();
        std::cout << "current loop will now be " << (g.laby.getLoops().back().useCurve() ? "curved" : "not curved") << std::endl;
        break;

    case 'f':
        g.editMode = false;
        D = g.laby.getAvgDistance();
        g.laby.addForce(new BrownianMotion(D/1.5, 1));
        g.laby.addForce(new Fairing(D/24));
        g.laby.addForce(new Morse(D/3, D, 2, 2*D, 5*D));
        g.laby.setSplitThreshold(1.4*D);
        g.laby.setMergeThreshold(0.25*D);
        std::cout << "edit mode is off; " << g.laby.getLoops().size() << " loops with " << g.laby.getNumPoints() << " points" << std::endl;
        break;

    case 'i':
        std::cout << "it: " << g.it << ", " << g.laby.getNumPoints() << " points "
            << "(" << g.XMIN << "," << g.YMIN << ") --> (" << g.XMAX << "," << g.YMAX << ")"
            << std::endl;
        break;

    case 'n':
        g.step = true;
        glutPostRedisplay();
        break;

    case 'p':
        if (g.paused) {
            g.paused = false;
            glutIdleFunc(displayFunc);
        }
        else {
            g.paused = true;
            glutIdleFunc(NULL);
        }
        std::cout << "sim is " << (g.paused ? "paused" : "running") << std::endl;
        break;
        
    case 's':
        std::cout << "writing svg...";
        out.open("../../output.svg");
        writeSvg(out, g.laby, g.XMIN, g.XMAX, g.YMIN, g.YMAX);
        out.close();
        std::cout << "done!" << std::endl;
        break;

    case 'q':
        glutIdleFunc(NULL);
        glutLeaveMainLoop();
        std::cout << "leaving main loop" << std::endl;
        break;
    }
}

void motionFunc(int x, int y) {
    if (g.leftClicking && g.editMode) {
        Point point = Point(x - g.windowWidth/2, g.windowHeight - (y + g.windowHeight/2), g.lockPoint);
        if (g.laby.getLoops().back().empty() || point.distance(g.laby.getLoops().back().back()) > g.minDistance) {
            g.laby.addToLast(point);
            std::cout << "point (" << x << "," << y << "," << (g.lockPoint ? "true" : "false") << ") added to loop #" << g.laby.getLoops().size() << std::endl;
        }
        glutPostRedisplay();
    }
}

void mouseFunc(int button, int state, int x, int y) {
    g.leftClicking = button == GLUT_LEFT_BUTTON && state == GLUT_DOWN;
    if (button == GLUT_RIGHT_BUTTON && g.editMode && state == GLUT_UP) {
        x = x - g.windowWidth/2;
        y = g.windowHeight - (y + g.windowHeight/2);
        g.laby.addToLast(x, y, g.lockPoint);
        std::cout << "point (" << x << "," << y << "," << (g.lockPoint ? "true" : "false") << ") added to loop #" << g.laby.getLoops().size() << std::endl;
        glutPostRedisplay();
    }
}

