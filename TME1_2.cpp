
/* Athabasca University

   Comp390 - Introduction to Computer Graphics

  TME 1 - PROGRAM 2
  Danny Cortez
  2997314
  April 25/17
*/


#include "stdafx.h"
#include "gl/glut.h"
#include "math.h"
#define PI 3.14159265

GLuint myList;

void createList()
{
	myList = glGenLists(1);

	glNewList(myList, GL_COMPILE);
	glPolygonMode(GL_BACK,GL_LINE);
	glBegin(GL_POLYGON);
		glVertex2i(-2,4);
		glVertex2i(2,4);
		glVertex2i(2,0);
		glVertex2i(-2,0);
	 glEnd();
	 glBegin(GL_LINE_LOOP);
		glVertex2i(-3,4);
		glVertex2i(3,4);
		glVertex2i(0,6);
		glEnd();
	glEndList();
}

// initialize

void initialize() {

	// set background color

	glClearColor(1.0, 1.0, 1.0, 0.0);

}

// render

void render() {

	glColor3f(0.0, 0.0, 0.0);
	glCallList(myList);
}


// display registry

void display(void) {

	float phi = 60.0;
	float alpha = 0.0;
	float hyp = 0.0;
	float xOffset = 0.0;
	float yOffset = 0.0;
	float RAD = 14.0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	createList();
	// viewing

	gluLookAt(0.0, 0.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	for(int i = 0; i < 8; i++)
	{
		//printf("p%f \n",phi);
		alpha = (180.0 - phi)/2;
		//printf("a%f \n",alpha);
		hyp = sin(phi*PI/180)*RAD/sin(alpha*PI/180);
		//printf("h%f \n",hyp);
		yOffset = sin((90-alpha)*PI/180)*hyp;
		xOffset = cos((90-alpha)*PI/180)*hyp;
		//printf("x%f \n",xOffset);
		//printf("y%f \n",yOffset);
		glPushMatrix();
		glTranslatef(-xOffset,-yOffset,0);
		glRotatef(phi,0,0,1);
		render();
		glPopMatrix();
		phi = phi - 30.0;
		//phi = phi - 45.0;
	}
	glutSwapBuffers();
}

// reshape registry

void reshape(int w, int h) {

	//glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0);

	glMatrixMode(GL_MODELVIEW);

}

// main program

void main(int argc, char **argv)

{

	glutInit( &argc, argv );

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;

	glutInitWindowSize(600, 600);

  	glutInitWindowPosition(100, 100);
	
	int windowHandle = glutCreateWindow("Athabasca University - Comp390 TME1 P2");

	glutSetWindow(windowHandle);
	
	glutDisplayFunc( display );

	glutReshapeFunc( reshape );
	
	initialize();

    glutMainLoop();

}
