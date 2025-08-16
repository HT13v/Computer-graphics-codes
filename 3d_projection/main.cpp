#include <GL/glut.h>

// Rotation angles
float angleX = 0.0f;
float angleY = 0.0f;
float zoom = -6.0f;

// Mouse control variables
int lastX = 0, lastY = 0;
bool mouseLeftDown = false;
bool mouseRightDown = false;

void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void drawCube() {
    glBegin(GL_QUADS);
    // Front face (z = 1.0f)
    glColor3f(0.0f, 0.0f, 0.9f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Back face (z = -1.0f)
    glColor3f(0.0f, 0.0f, 0.7f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Top face
    glColor3f(0.0f, 0.0f, 0.5f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Bottom face
    glColor3f(0.0f, 0.0f, 0.3f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right face
    glColor3f(0.0f, 0.0f, 0.8f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Left face
    glColor3f(0.0f, 0.0f, 0.6f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, zoom);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    drawCube();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 1.0f, 100.0f);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            lastX = x;
            lastY = y;
            mouseLeftDown = true;
        } else {
            mouseLeftDown = false;
        }
    } else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            lastY = y;
            mouseRightDown = true;
        } else {
            mouseRightDown = false;
        }
    }
}

void motion(int x, int y) {
    if (mouseLeftDown) {
        angleY += (x - lastX);
        angleX += (y - lastY);
        lastX = x;
        lastY = y;
    }
    if (mouseRightDown) {
        zoom += (y - lastY) * 0.1f;
        lastY = y;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Cube - Presentation");
    initOpenGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}
