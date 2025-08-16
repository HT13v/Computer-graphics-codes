#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>
float x1,y1,x2,y2;


void display (){
    glClear(GL_COLOR_BUFFER_BIT);
float dx=y2-y1;
float dy = y2-y1;
float step;
if(abs(dx)>abs(dy)){

    step = abs(dx);

}
else{
    step=abs(dy);

}
float xinc=abs(dx)/step;
float yinc=abs(dy)/step;
float x= x1;
float y=y1;
glBegin(GL_POINTS);
glVertex2i(x,y);
glEnd();
for(int k=1;k<=step;k++){
    x=x+xinc;
    y=y+yinc;
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
glFlush();
}
void myInit(){
glClearColor(0.0,0.0,0.0,0.0);
glColor3f(0.0,1.0,0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,640.0,0.0,480.0);

}
int main(int argc, char **argv){
scanf("%f %f %f %f", & x1,& y1,& x2,& y2);
glutInit(& argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(640,480);
glutInitWindowPosition(100,500);
glutCreateWindow(" ");
glutDisplayFunc(display);
myInit();
glutMainLoop();
return 0;
}
