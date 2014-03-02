

#ifdef _WIN32
  #include <windows.h>
  #define GLEW_STATIC
#endif
#include <cstdio>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "header.h"

using namespace std;
// it needs to be defined somewhere
int global_x;

void test() {
    //set global_x here:
    global_x = 5;
    print_global_x();
}


void init()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.2f, 0.2f, 0.4f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat lightPos[4] = {-1.0,1.0,0.5,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,(GLfloat *) &lightPos);

	glEnable(GL_LIGHT1);

	GLfloat lightAmbient1[4] = {0.0,0.0,0.0,0.0};
	GLfloat lightPos1[4] = {1.0,0.0,-0.2,0.0};
	GLfloat lightDiffuse1[4] = {0.5,0.5,0.3,0.0};

	glLightfv(GL_LIGHT1,GL_POSITION,(GLfloat *) &lightPos1);
	glLightfv(GL_LIGHT1,GL_AMBIENT,(GLfloat *) &lightAmbient1);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,(GLfloat *) &lightDiffuse1);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
}

void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void arrow_keys( int a_keys, int x, int y );

int main(int argc, char **argv)
{
    main3();
    return 0;

    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("ROOM");

    printf("OpenGL version supported by this platform (%s): \n",
        glGetString(GL_VERSION));

//    init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);

	glutMainLoop();
}

int x, y, z;
/* display method called each frame*/
void display(void)
{
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glLineWidth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glDisable(GL_LIGHTING); // drawing some smooth shaded background - because I like it ;)
	glBegin(GL_POLYGON);
        glColor3f(0.8f,0.8f,1.0f);
        glVertex3f(-200.0f,-100.0f,-100.0f);
        glVertex3f(200.0f,-100.0f,-100.0f);
        glColor3f(0.4f,0.4f,0.8f);
        glVertex3f(200.0f,100.0f,-100.0f);
        glVertex3f(-200.0f,100.0f,-100.0f);
	glEnd();
	glEnable(GL_LIGHTING);

	glTranslatef(-6.5,6,-9.0f); // move camera out and center on the cloth
//	glTranslatef(x,y,z);
	glRotatef(25,0,1,0); // rotate a bit to see the cloth from the side
//	cloth1.drawShaded(); // finally draw the cloth with smooth shading

	glPushMatrix(); // to draw the ball we use glutSolidSphere, and need to draw the sphere at the position of the ball
	glTranslatef(3,3,3); // hence the translation of the sphere onto the ball position
	glColor3f(0.4f,0.8f,0.5f);
	glutSolidSphere(3-0.1,50,50); // draw the ball, but with a slightly lower radius, otherwise we could get ugly visual artifacts of cloth penetrating the ball slightly
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h==0)
		gluPerspective(80,(float)w,1.0,5000.0);
	else
		gluPerspective (80,( float )w /( float )h,1.0,5000.0 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard( unsigned char key, int x, int y )
{
	switch ( key ) {
	case 27:
		exit ( 0 );
		break;
    case 'a':
        x = 1;
        break;
    case 's':
        x = -1;
        break;
    case 'd':
        y = 1;
        break;
    case 'f':
        y = -1;
        break;
    case 'g':
        z = 1;
        break;
    case 'h':
        z = -1;
        break;
	default:
		break;
	}
}

void arrow_keys( int a_keys, int x, int y )
{
	switch(a_keys) {
	case GLUT_KEY_UP:
		glutFullScreen();
		break;
	case GLUT_KEY_DOWN:
		glutReshapeWindow (1280, 720 );
		break;
	default:
		break;
	}
}
