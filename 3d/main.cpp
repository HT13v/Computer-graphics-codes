#include <GL/glut.h>

float angle = 0.0;

// Function to initialize OpenGL settings
void init() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
}

// Function to draw a cube
void drawCube() {
    glBegin(GL_QUADS);

    // Front face (z = 1.0)
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.0);

    // Back face (z = -1.0)
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);

    // Top face (y = 1.0)
    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0, -1.0);

    // Bottom face (y = -1.0)
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0,  1.0);

    // Right face (x = 1.0)
    glColor3f(0.0, 1.0, 1.0); // Cyan
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);

    // Left face (x = -1.0)
    glColor3f(1.0, 0.0, 1.0); // Magenta
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0, -1.0);

    glEnd();
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -7.0); // Move cube back
    glRotatef(angle, 1.0, 1.0, 1.0); // Rotate cube

    drawCube();

    glutSwapBuffers();
}

// Idle callback for animation
void idle() {
    angle += 0.2f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
}

// Reshape function
void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Rotating 3D Cube - OpenGL");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
