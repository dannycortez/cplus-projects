/*

COMP 390 FINAL PROJECT
DANNY CORTEZ

*/

#include "stdafx.h"
#include "windows.h"
#include "gl/glut.h"
#include "math.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//3D VARS
GLUquadric *cylObject;
GLUquadric *diskObject;

//Lights
GLfloat light_position0[] = { 20.0, 5.0, 20.0, 0.0 };
GLfloat light_position1[] = { 20.0, 5.0, 20.0, 0.0 };
GLfloat white_light[] = { 0.75, 0.75, 0.75, 1.0 };
GLfloat black_light[] = { 0.025, 0.025, 0.025, 1.0 };
GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

// image vars
GLubyte *image;
GLubyte * l_texture;
BITMAPFILEHEADER fileheader; 
BITMAPINFOHEADER infoheader;
RGBTRIPLE rgb;
GLuint texName;

//function to create chess board
void createBoard()
{

	GLfloat black = 0.1;
	GLfloat white = 0.9;
	GLfloat squareColor = 0.0;
	int row = 0;
	int col = 0;

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
		glVertex3f(0.0, -0.1, 0.0);
		glVertex3f(8.0, -0.1, 0.0);
		glVertex3f(8.0, -0.1, 8.0);
		glVertex3f(0.0, -0.1, 8.0);
	glEnd();
		
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			row = i%2;
			col = j%2;
			//Draw indvidual squares
			if (row == col)
				squareColor = white;
			else
				squareColor = black;
			glColor3f(squareColor,squareColor,squareColor);
		
			glBegin(GL_QUADS);
				glVertex3f(j, -0.1, i);
				glVertex3f(j+1, -0.1, i);
				glVertex3f(j+1, -0.1, i+1);
				glVertex3f(j, -0.1, i+1);
			glEnd();

		}
	}

}

//classes of chess pcs
class pawn
{
	
	public:
	
	float colorCode;
	GLuint newPawn;
		pawn(float cCode)
		{colorCode = cCode;}
		
		void create()
		{
			newPawn = glGenLists(1);
			glNewList(newPawn, GL_COMPILE);
			glColor3f(colorCode, colorCode, colorCode);

			//first flat base
			glPushMatrix();
			glScaled(2.0, 0.25, 2.0);
			glutSolidSphere(2.0,16,16);
			glPopMatrix();

			//second flat base
			glPushMatrix();
			glTranslated(0.0,0.5,0.0);
			glScaled(2.0, 0.25, 2.0);
			glutSolidSphere(2.0,16,16);
			glPopMatrix();

			//body
			glPushMatrix();
			glTranslated(0.0,0.5,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(cylObject, 3.0,1.0,6.0,16,16);
			glPopMatrix();

			//square
			glPushMatrix();
			glTranslated(0.0,7.0,0.0);
			glScaled(1.0,0.5,1.0);
			glutSolidCube(2.0);
			glPopMatrix();

			//top ball
			glPushMatrix();
			glTranslated(0.0,8.6,0.0);
			glutSolidSphere(1.5,16,16);
			glPopMatrix();
			glEndList();
	}

};

class rook
{
	
	public:
	
	float colorCode;
	GLuint newRook;
	GLuint rookTop;
		rook(float cCode)
		{colorCode = cCode;}
					
		void create()
		{
			newRook = glGenLists(1);
			glNewList(newRook, GL_COMPILE);
			glColor3f(colorCode, colorCode, colorCode);

			//flat base
			glPushMatrix();
			glScaled(2.0, 0.25, 2.0);
			glutSolidSphere(2.2,16,16);
			glPopMatrix();

			//second flat base
			glPushMatrix();
			glTranslated(0.0,0.5,0.0);
			glScaled(2.0, 0.25, 2.0);
			glutSolidSphere(2.1,16,16);
			glPopMatrix();

			//body
			glPushMatrix();
			glTranslated(0.0,0.5,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(cylObject, 3.0,1.0,7.0,16,16);
			glPopMatrix();

			//square
			glPushMatrix();
			glTranslated(0.0,1.0,0.0);
			glScaled(1.0,0.5,1.0);
			glutSolidCube(2.0);
			glPopMatrix();

			//top 
			glPushMatrix();
			glTranslated(0.0,7.0,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(cylObject, 2.0,2.0,2.0,16,16);
			glPopMatrix();
			
			//crown
			glPushMatrix();
			glTranslated(0.0,9.0,1.5);
			glScaled(1.0,2.0,0.5);
			glutSolidCube(1.0);
			glPopMatrix();
			
			glPushMatrix();
			glTranslated(0.0,9.0,-1.5);
			glScaled(1.0,2.0,0.5);
			glutSolidCube(1.0);
			glPopMatrix();

			glPushMatrix();
			glTranslated(-1.5,9.0,0.0);
			glRotated(90.0, 0.0, 1.0, 0.0);
			glScaled(1.0,2.0,0.5);
			glutSolidCube(1.0);
			glPopMatrix();

			glPushMatrix();
			glTranslated(1.5,9.0,0.0);
			glRotated(90.0, 0.0, 1.0, 0.0);
			glScaled(1.0,2.0,0.5);
			glutSolidCube(1.0);
			glPopMatrix();

		glEndList();
	
	}

};

class bishop
{
	
	public:
	
	float colorCode;
	GLuint newBishop;
	GLuint rookTop;
		bishop(float cCode)
		{colorCode = cCode;}
				
		void create()
		{
			newBishop = glGenLists(1);
			glNewList(newBishop, GL_COMPILE);
			glColor3f(colorCode, colorCode, colorCode);

			//flat base
			glPushMatrix();
			glScaled(2.0, 0.25, 2.0);
			glutSolidSphere(2.2,16,16);
			glPopMatrix();

			//second flat base
			glPushMatrix();
			glTranslated(0.0,0.5,0.0);
			glScaled(2.0, 0.25, 2.0);
			glutSolidSphere(2.1,16,16);
			glPopMatrix();

			//tapered cylinder
			glPushMatrix();
			glTranslated(0.0,0.5,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(cylObject, 2.0,1.0,7.0,16,16);
			glPopMatrix();
			
			//second flat ball
			glPushMatrix();
			glTranslated(0.0,7.0,0.0);
			glScaled(1.0, 0.25, 1.0);
			glutSolidSphere(2.1,16,16);
			glPopMatrix();

			//top ball
			glPushMatrix();
			glTranslated(0.0,9.0,0.0);
			glScaled(1.0, 1.5, 1.0);
			glutSolidSphere(1.5,16,16);
			glPopMatrix();

			glPushMatrix();
			glTranslated(0.0,11.2,0.0);
			glutSolidSphere(0.3,16,16);
			glPopMatrix();
			
		glEndList();
	
	}

};

class knight
{
	
	public:
	
	float colorCode;
	GLuint newKnight;
		knight(float cCode)
		{colorCode = cCode;}
		
		void create()
		{
			newKnight = glGenLists(1);
			glNewList(newKnight, GL_COMPILE);
			glColor3f(colorCode, colorCode, colorCode);

			//flat base
			glPushMatrix();
			glScaled(2.0, 0.25, 2.0);
			glutSolidSphere(2.0,16,16);
			glPopMatrix();

			//second flat base
			glPushMatrix();
			glTranslated(0.0,0.5,0.0);
			glScaled(2.0, 0.25, 2.0);
			glutSolidSphere(2.0,16,16);
			glPopMatrix();

			//1st tapered cylinder
			glPushMatrix();
			glTranslated(0.0,0.5,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(cylObject, 3.0,1.0,3.0,16,16);
			glPopMatrix();

			//2nd tapered cylinder
			glPushMatrix();
			glTranslated(0.0,6.5,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			glRotated(180.0, 0.0, 1.0, 0.0);
			gluCylinder(cylObject, 3.0,1.0,3.0,16,16);
			glPopMatrix();

			//3rdt tapered cylder
			glPushMatrix();
			glTranslated(0.0,6.5,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(cylObject, 3.0,0.0,3.0,16,16);
			glPopMatrix();

			//nose
			glPushMatrix();
			glTranslated(0.0,6.5,1.0);
			glRotated(30.0, 1.0, 0.0, 0.0);
			gluCylinder(cylObject, 1.0,0.0,4.0,16,16);
			glPopMatrix();

			glEndList();
	}


};

class king
{
	
	public:
	
	float colorCode;
	GLuint newKing;
	king(float cCode)
	{colorCode = cCode;}
				
		void create()
		{
			newKing = glGenLists(1);
			glNewList(newKing, GL_COMPILE);
			glColor3f(colorCode, colorCode, colorCode);

			//flat disk
			glPushMatrix();
			glScaled(2.0, 0.25, 2.0);
			glutSolidSphere(2.2,16,16);
			glPopMatrix();

			//second disk
			glPushMatrix();
			glTranslated(0.0,0.5,0.0);
			glScaled(2.0, 0.25, 2.0);
			glutSolidSphere(2.1,16,16);
			glPopMatrix();

			//tapered cylinder
			glPushMatrix();
			glTranslated(0.0,0.5,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(cylObject, 3.0,1.75,8.5,16,16);
			glPopMatrix();
			
			//third disk
			glPushMatrix();
			glTranslated(0.0,9.0,0.0);
			glScaled(1.0, 0.25, 1.0);
			glutSolidSphere(2.1,16,16);
			glPopMatrix();

			//collar
			glPushMatrix();
			glTranslated(0.0,9.0,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(cylObject, 1.5,1.5,1.5,16,16);
			glPopMatrix();

			//"head"
			glPushMatrix();	
			glTranslated(0.0,12.5,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			glRotated(180.0, 0.0, 1.0, 0.0);
			gluCylinder(cylObject, 2.0,2.0,2.0,16,16);
			glPopMatrix();

			//fourth disk
			glPushMatrix();
			glTranslated(0.0,12.5,0.0);
			glScaled(1.0, 0.5, 1.0);
			glutSolidSphere(2.0,16,16);
			glPopMatrix();

			//cross
			glPushMatrix();
			glTranslated(0.0,13.5,0.0);
			glScaled(1.0, 4.0, 1.0);
			glutSolidCube(1.0);
			glPopMatrix();

			glPushMatrix();
			glTranslated(0.0,14.5,0.0);
			glScaled(3.0, 1.0, 1.0);
			glutSolidCube(1.0);
			glPopMatrix();


		glEndList();
	
	}

};

class queen
{
	
	public:
	
	float colorCode;
	GLuint newQueen;
	queen(float cCode)
	{colorCode = cCode;}
				
		void create()
		{
			newQueen = glGenLists(1);
			glNewList(newQueen, GL_COMPILE);
			glColor3f(colorCode, colorCode, colorCode);

			//flat disk
			glPushMatrix();
			glScaled(2.0, 0.25, 2.0);
			glutSolidSphere(2.2,16,16);
			glPopMatrix();

			//second disk
			glPushMatrix();
			glTranslated(0.0,0.5,0.0);
			glScaled(2.0, 0.25, 2.0);
			glutSolidSphere(2.1,16,16);
			glPopMatrix();

			//tapered cylinder
			glPushMatrix();
			glTranslated(0.0,0.5,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(cylObject, 3.0,1.75,8.0,16,16);
			glPopMatrix();
			
			//third disk
			glPushMatrix();
			glTranslated(0.0,8.5,0.0);
			glScaled(1.0, 0.25, 1.0);
			glutSolidSphere(2.1,16,16);
			glPopMatrix();

			//collar
			glPushMatrix();
			glTranslated(0.0,8.5,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(cylObject, 1.5,1.5,1.5,16,16);
			glPopMatrix();

			//"head"
			glPushMatrix();	
			glTranslated(0.0,12.0,0.0);
			glRotated(-90.0, 1.0, 0.0, 0.0);
			glRotated(180.0, 0.0, 1.0, 0.0);
			gluCylinder(cylObject, 2.1,1.55,2.0,16,16);
			glPopMatrix();

			//fourth disk
			glPushMatrix();
			glTranslated(0.0,11.5,0.0);
			glScaled(1.0, 0.5, 1.0);
			glutSolidSphere(1.90,16,16);
			glPopMatrix();

			//ball
			glPushMatrix();
			glTranslated(0.0,12.95,0.0);
			glutSolidSphere(0.5,16,16);
			glPopMatrix();
			
		glEndList();
	
	}

};
//end of classes

//function to create image
void makeImage(void) {

	int i, j=0;

	FILE *l_file;
	string fn = "sparse-crowd.bmp";

	const char * filename = fn.c_str();

	// open image file, return if error

	fopen_s(&l_file, filename, "rb");

	if (l_file == NULL)
	{
		printf("file did not open\n");
		return;
	}

	// read file header and header info

	fread(&fileheader, sizeof(fileheader), 1, l_file);

	fseek(l_file, sizeof(fileheader), SEEK_SET);

	fread(&infoheader, sizeof(infoheader), 1, l_file);

	// allocate space for the image file

	l_texture = (GLubyte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);

	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

	// read da data

	j = 0;

	for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)

	{ 

		fread(&rgb, sizeof(rgb), 1, l_file); 

		l_texture[j+0] = (GLubyte) rgb.rgbtRed; // Red component

		l_texture[j+1] = (GLubyte) rgb.rgbtGreen; // Green component

		l_texture[j+2] = (GLubyte) rgb.rgbtBlue; // Blue component

		l_texture[j+3] = (GLubyte) 255; // Alpha value

		j += 4; // Go to the next position

	}

	fclose(l_file); // Closes the file stream

}

void initialize(void) {

	// set background color

	cylObject = gluNewQuadric();
	diskObject = gluNewQuadric();
	gluQuadricNormals(cylObject, GLU_SMOOTH);
	gluQuadricNormals(diskObject, GLU_SMOOTH);

	//glEnable lights
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// image

	makeImage();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texName);

	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 

		infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,

		l_texture);
		
}

//DRAWS THE QUADS FOR THE IMAGE
void drawPicture() {

	glBegin( GL_QUADS );

		glTexCoord3d(0.0, 0.0, 0.0);
		glVertex3f(0.0, -0.1, 0.0);
		
		glTexCoord3d(1.0, 0.0, 0.0);
		glVertex3d(8.0, -0.1, 0.0);

		glTexCoord3d(1.0, 1.0, 0.0);
		glVertex3d(8.0, 8.0, 0.0);
			
		glTexCoord3d(0.0, 1.0, 0.0);
		glVertex3d(0.0, 8.0, 0.0);

	glEnd();

	glBegin( GL_QUADS );

		glTexCoord3d(0.0,0.0, 0.0);
		glVertex3f(0.0, -0.1, 8.0);
		
		glTexCoord3d(1.0, 0.0, 0.0);
		glVertex3d(0.0, -0.1, 0.0);

		glTexCoord3d(1.0, 1.0, 0.0);
		glVertex3d(0.0, 8.0, 0.0);

	
		glTexCoord3d(0.0, 1.0, 0.0);
		glVertex3d(0.0, 8.0, 8.0);

	glEnd();

}

void render() {
	
	createBoard();
	
}

void display() {

	glEnable(GL_DEPTH_TEST);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(7.5, 4.5, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	//an atmospheric attenuation affect
	GLfloat fogColor[4] = {0.6, 0.6, 0.6, 1.0};
	GLfloat scaleFactor = 0.1; // scale factor of pcs for board
	//white pcs
	pawn whitePawn(1.0);
	rook whiteRook(1.0);
	bishop whiteBishop(1.0);
	knight whiteKnight(1.0);
	king whiteKing(1.0);
	queen whiteQueen(1.0);
	//black pcs
	pawn blackPawn(0.0);
	rook blackRook(0.0);
	bishop blackBishop(0.0);
	knight blackKnight(0.0);
	king blackKing(0.0);
	queen blackQueen(0.0);

	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.05);
	glFogf(GL_FOG_START, 0.0); 
	glFogf(GL_FOG_END, 200.0); 
	glEnable(GL_FOG);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
			
	//draw white pawns
	glPushMatrix();
	glTranslated(0.5, 0.0, 6.5);
	glScaled(0.10, 0.10, 0.10);
	whitePawn.create();
	glCallList(whitePawn.newPawn);
	glPushMatrix();
	glTranslated(20.0, 0.0, 0.0);
	glCallList(whitePawn.newPawn);
	glPopMatrix();
	for (int i = 1; i < 8; i++)
	{
		glPushMatrix();
		glTranslated((i/0.1), 0.0, 0.0);
		glCallList(whitePawn.newPawn);
		glPopMatrix();
	}	
	glPopMatrix();
	//draw white rooks
	glPushMatrix();
	glTranslated(0.5, 0.0, 7.5);
	glScaled(0.10, 0.10, 0.10);
	whiteRook.create();
	glCallList(whiteRook.newRook);
	glPushMatrix();
	glTranslated((7.0/0.1), 0.0, 0.0);
	glCallList(whiteRook.newRook);
	glPopMatrix();
	glPopMatrix();
	//draw white Bishops
	glPushMatrix();
	glTranslated(2.5, 0.0, 7.5);
	glScaled(scaleFactor, scaleFactor, scaleFactor);
	whiteBishop.create();
	glCallList(whiteBishop.newBishop);
	glPushMatrix();
	glTranslated((3/scaleFactor), 0.0, 0.0);
	glCallList(whiteBishop.newBishop);
	glPopMatrix();
	glPopMatrix();
	//draw white Knight
	glPushMatrix();
	glTranslated(1.5, 0.0, 7.5);
	glScaled(scaleFactor, scaleFactor, scaleFactor);
	whiteKnight.create();
	glCallList(whiteKnight.newKnight);
	glPushMatrix();
	glTranslated((5/scaleFactor), 0.0, 0.0);
	glCallList(whiteKnight.newKnight);
	glPopMatrix();
	glPopMatrix();
	//draw white King
	glPushMatrix();
	glTranslated(4.5, 0.0, 7.5);
	glScaled(scaleFactor, scaleFactor, scaleFactor);
	whiteKing.create();
	glCallList(whiteKing.newKing);
	glPopMatrix();
	//draw white Queen
	glPushMatrix();
	glTranslated(3.5, 0.0, 7.5);
	glScaled(scaleFactor, scaleFactor, scaleFactor);
	whiteQueen.create();
	glCallList(whiteQueen.newQueen);
	glPopMatrix();

	glDisable(GL_LIGHT0);

	//draw the black pcs now
	
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, black_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, black_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	//draw black pawns
	glPushMatrix();
	glTranslated(0.5, 0.0, 1.5);
	glScaled(scaleFactor, scaleFactor, scaleFactor);
	blackPawn.create();
	glCallList(blackPawn.newPawn);
	glPushMatrix();
	glCallList(blackPawn.newPawn);
	glPopMatrix();
	for (int i = 1; i < 8; i++)
	{
		glPushMatrix();
		glTranslated((i/scaleFactor), 0.0, 0.0);
		glCallList(blackPawn.newPawn);
		glPopMatrix();
	}	
	glPopMatrix();
	//draw black rooks
	glPushMatrix();
	glTranslated(0.5, 0.0, 0.5);
	glScaled(scaleFactor, scaleFactor, scaleFactor);
	blackRook.create();
	glCallList(blackRook.newRook);
	glPushMatrix();
	glTranslated((7.0/scaleFactor), 0.0, 0.0);
	glCallList(blackRook.newRook);
	glPopMatrix();
	glPopMatrix();
	//draw black Bishops
	glPushMatrix();
	glTranslated(2.5,0.0,0.5);
	glScaled(scaleFactor, scaleFactor, scaleFactor);
	blackBishop.create();
	glCallList(blackBishop.newBishop);
	glPushMatrix();
	glTranslated((3/scaleFactor), 0.0, 0.0);
	glCallList(blackBishop.newBishop);
	glPopMatrix();
	glPopMatrix();
	//draw black knights
	glPushMatrix();
	glTranslated(1.5, 0.0, 0.5);
	glScaled(scaleFactor, scaleFactor, scaleFactor);
	blackKnight.create();
	glCallList(blackKnight.newKnight);
	glPushMatrix();
	glTranslated((5/scaleFactor), 0.0, 0.0);
	glCallList(blackKnight.newKnight);
	glPopMatrix();
	glPopMatrix();
	//draw black King
	glPushMatrix();
	glTranslated(4.5, 0.0, 0.5);
	glScaled(scaleFactor, scaleFactor, scaleFactor);
	blackKing.create();
	glCallList(blackKing.newKing);
	glPopMatrix();
	//draw black Queen
	glPushMatrix();
	glTranslated(3.5, 0.0, 0.5);
	glScaled(scaleFactor, scaleFactor, scaleFactor);
	blackQueen.create();
	glCallList(blackQueen.newQueen);
	glPopMatrix();
	
	//disable all lighting
	glDisable(GL_LIGHTING);
	
	render(); //draw the board
	//draw the texture
	//enable the texture
	glEnable(GL_TEXTURE_2D);
	drawPicture();
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_DEPTH_TEST);

	glFlush();

	glutSwapBuffers();

}



void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0);

	glMatrixMode(GL_MODELVIEW);

}



void main(int argc, char **argv)

{

	glutInit( &argc, argv );

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;

	glutInitWindowSize(500, 500);

  	glutInitWindowPosition(100, 100);

	int windowHandle = glutCreateWindow("Comp390 FINAL PROJECT");

	glutSetWindow(windowHandle);

	glutDisplayFunc( display );

	glutReshapeFunc( reshape );

	initialize();

    glutMainLoop();

}
//END PROGRAM
