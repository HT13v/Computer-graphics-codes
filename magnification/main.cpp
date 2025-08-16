#include <GL/glut.h>
//magnify
// Hardcoded triangle vertices
float triangle[3][2] = {
    {100.0f, 100.0f},
    {200.0f, 100.0f},
    {150.0f, 200.0f},

};

// Fixed point for scaling
float xf = 150.0f, yf = 120.0f;

// Scaling factors
float sx = 1.5f, sy = 1.5f;

// Scaled triangle vertices
float scaled[3][2];

void applyScaling() {
    for (int i = 0; i < 3; i++) {
        scaled[i][0] = xf + sx * (triangle[i][0] - xf);
        scaled[i][1] = yf + sy * (triangle[i][1] - yf);
    }
}

void drawTriangle(float t[3][2]) {
    glBegin(GL_LINE_LOOP);  // Line loop for outline only
    for (int i = 0; i < 3; i++)
        glVertex2f(t[i][0], t[i][1]);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw original triangle in blue
    glColor3f(0.0f, 0.0f, 1.0f);
    drawTriangle(triangle);

    // Draw scaled triangle in red
    glColor3f(1.0f, 0.0f, 0.0f);
    drawTriangle(scaled);

    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100.0, 400.0, -100.0, 400.0);  // Coordinate system
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    applyScaling();  // Calculate scaled triangle

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Triangle Magnification About a Point");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
