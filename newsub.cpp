/*
    * Developer : Suraj Kumar Jana
    * @surajjana2
    * about.me/surajjana
*/


#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<GL/glut.h>

GLfloat v[4][3]={{0.0,0.0,1.0},{0.0,0.94,-0.33},
                     {-0.81,-0.47,-0.33}, {0.81,-0.47,-0.33}};
GLfloat colors[4][3]={{1.0,0.0,0.0},{1.0,0.0,0.0},{1.0,0.0,0.0},{0.0,0.0,0.0}};
int n = 3;
void triangle(GLfloat *a,GLfloat *b,GLfloat *c)
{
    glColor3fv(colors[0]);
    glVertex3fv(a);
    glColor3fv(colors[1]);
    glVertex3fv(b);
    glColor3fv(colors[2]);
    glVertex3fv(c);
}

void normalize(GLfloat *p)
{
    double d=0.0;
    int i;
    for(i=0;i<3;i++) d+=p[i]*p[i];
    d=sqrt(d);
    if(d>0.0) for(i=0;i<3;i++) p[i]/=d;
}

void divide_tetra(GLfloat *a,GLfloat *b,GLfloat *c,int m)
{
    GLfloat v1[3],v2[3],v3[3];
    int j;
    if(m>0)
    {    /*compute six midpoints*/
        for(j=0;j<3;j++)
            v1[j]=(a[j]+b[j])/2;
        normalize(v1);
        for(j=0;j<3;j++)
            v2[j]=(a[j]+c[j])/2;
        normalize(v2);
        for(j=0;j<3;j++)
            v3[j]=(c[j]+b[j])/2;
        normalize(v3);
        divide_tetra(a,v2,v1,m-1);
        divide_tetra(c,v3,v2,m-1);
        divide_tetra(b,v1,v3,m-1);
        divide_tetra(v1,v2,v3,m-1);
    }
    else
        triangle( a, b, c);      //draw triangle at end of recursion//
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    divide_tetra(v[0],v[1],v[2],n);
    divide_tetra(v[3],v[2],v[1],n);
    divide_tetra(v[0],v[3],v[1],n);
    divide_tetra(v[0],v[2],v[3],n);
    glEnd();
    glFlush();
}

void myReshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0,2.0,-2.0,2.0 ,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("3d gasket");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0,1.0,1.0,1.0);
    glutMainLoop();
    return 0;
}
