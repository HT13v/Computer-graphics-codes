#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
float x=0,y,x2,y2,m,i,j,p;
int dx=0,dy=0,r;
void display(void)
{

    glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    p=1-r;
    while((x<=y)){
        if(p<0){
          x=x+1;
          y=y;
            p=p+(2*x)+1;
            }


            else{
            x=x+1;
            y=y-1;
            p=p+(2*x)+1-(2*y);
            }
            glVertex2f (((x/100)), ((y/100)));
            glVertex2f (((y/100)), ((x/100)));
            glVertex2f ((-(x/100)), (-(y/100)));
            glVertex2f ((-(x/100)), ((y/100)));
            glVertex2f (((x/100)), (-(y/100)));
            glVertex2f (((y/100)), (-(x/100)));
            glVertex2f ((-(y/100)), (-(x/100)));
            glVertex2f ((-(y/100)), ((x/100)));
        }
glEnd();

glFlush ();
}
void init (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

}

int main(int argc, char** argv)
{

    printf("Enter radius: ");
    scanf("%d",&r);
    y=r;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
