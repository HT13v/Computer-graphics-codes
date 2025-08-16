#include <GL/glut.h>
#include <iostream>
using namespace std;

// Define region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Clipping window boundaries
double x_min = 50, y_min = 50, x_max = 100, y_max = 100;

// Function to compute region code for a point (x, y)
int computeCode(double x, double y) {
    int code = INSIDE;
    if (x < x_min)       code |= LEFT;
    else if (x > x_max)  code |= RIGHT;
    if (y < y_min)       code |= BOTTOM;
    else if (y > y_max)  code |= TOP;
    return code;
}

// Cohen-Sutherland Line Clipping Algorithm
void cohenSutherlandClip(double x1, double y1, double x2, double y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // Both points inside
            accept = true;
            break;
        } else if (code1 & code2) {
            // Line is outside the clipping window
            break;
        } else {
            // At least one point is outside
            int code_out;
            double x, y;

            // Choose point outside the window
            code_out = code1 ? code1 : code2;

            // Find intersection point
            if (code_out & TOP) {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (code_out & BOTTOM) {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (code_out & RIGHT) {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (code_out & LEFT) {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            // Replace outside point with intersection
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        // Draw clipped line
        glColor3f(1.0, 0.0, 0.0); // red
        glBegin(GL_LINES);
            glVertex2d(x1, y1);
            glVertex2d(x2, y2);
        glEnd();
        glFlush();
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window
    glColor3f(0.0, 0.0, 1.0); // blue
    glBegin(GL_LINE_LOOP);
        glVertex2d(x_min, y_min);
        glVertex2d(x_max, y_min);
        glVertex2d(x_max, y_max);
        glVertex2d(x_min, y_max);
    glEnd();

    // Original line
    double x1 = 20, y1 = 20, x2 = 120, y2 = 120;
    glColor3f(0.0, 1.0, 0.0); // green
    glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    glEnd();

    // Perform clipping
    cohenSutherlandClip(x1, y1, x2, y2);

    glFlush();
}

// Initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // white background
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 200, 0, 200);
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
