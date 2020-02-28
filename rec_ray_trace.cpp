/* 

   Ray Trace W/ SHADOW
  
*/

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include "gl/glut.h"
#include "plane.h"
using namespace std;

//image variables
#define imageWidth 500
#define imageHeight 500
#define imageDepth 60



//class ray; a model of the "ray" of light
class ray
{
		
	public:
		
		vector3 direction;// a point along the direction of the ray
		vector3 origin;// the point of origin
		
		ray(vector3 o, vector3 d): direction(d), origin(o){}
		
		vector3 ray:: getVector(vector3 p, vector3 q)
		{
		 vector3 newVector =  p.subtract(q);
		 return newVector;
		}
		
		vector3 ray::getRayOrigin()
		{
			return origin;
		}
		vector3 ray::getRayDirection()
		{
			
			return direction;
		}
	
		void setRayDirection(float x, float y, float z)
		{
			direction.setX(x);
			direction.setY(y);
			direction.setZ(z);
		}
		void setRayOriginReflection(bool r)
		{
			origin.setReflective(r);
		}
		bool getRayOriginReflection()
		{
			return origin.isReflective();
		}

		void setRayOriginVector(vector3 newOrigin)
		{
			origin = newOrigin;
		}
		void setRayDirectionVector(vector3 newDirection)
		{
			direction = newDirection;
		}
		
};


	//added functions
	vector3 *testintersect(ray *currentRay);
	vector3 rrTrace(ray *r, int d);
	vector3 aggColorCont(vector3 point);
	bool inShadow(vector3 point);


	int dmax = 4; //max calls of rrt
	
	vector3 localColor(vector3 intersect, vector3 baseColor, vector3 normal);

	vector3 background(0.5, 0.7, 0.5);

	// viewer

	vector3 viewer(-40.0, 40.0, 120.0);
	
	// floor

	vector3 floorNormal(0.0, 1.0, 0.0);

	plane   floorDef(0.0, 4.0, 0.0, 0.0);
	
	
	
	vector3 floorLimit1(-75.0, 0, -75.0);
		
	vector3 floorLimit2(-75.0, 0, 75.0);

	vector3 floorLimit3(75.0, 0, 75.0);

	vector3 floorLimit4(75.0, 0, -75.0);
	

	vector3 wallNormal(0.0, 0.0, 1.0);

	plane   wall(0.0, 0.0, 4.0, 0.0);

	vector3 wallLimit1(-25.0, 0.0, 0.0);

	vector3 wallLimit2(-25.0, 50.0, 0.0);

	vector3 wallLimit3(25.0, 50.0, 0.0);

	vector3 wallLimit4(25.0, 0.0, 0.0);
	
	// colors

	vector3 grey(0.75, 0.75, 0.75);

	vector3 shadow(0.25, 0.25, 0.25);
		
	vector3 lightRed(0.75, 0.1, 0.1);
	
	// lighting position

	vector3 lightPosition(25, 25, 100.0);

	vector3 inter = floorDef.intersect(lightPosition,viewer);

	// lighting elements

	float ambient_coef = 0.3;

	float diffuse_coef = 0.7;

	float reflect_coef = 0.4;

	float local_coef   = 0.6;


bool floorOriginTest(ray * currentRay)
{
	
	//if the origin of the ray is on the floor it is coming off the floor towards the light or another object.
	if ((currentRay->getRayOrigin().getX() >= -75) && (currentRay->getRayOrigin().getX() <=75) && (currentRay->getRayOrigin().getZ() >= -75)
		&& currentRay->getRayOrigin().getZ() <=75)
	{
		return true;
	}
	//else the ray does not intersect the floor
	else 
	{
		return false;
	}

}

//does the ray intersect the wall?
bool wallTest(vector3 wallpoint)
{
	
	if((wallpoint.getX()>=-25) && (wallpoint.getX() <= 25) && (wallpoint.getY() >= 0) && (wallpoint.getY() <= 50))
	{
		
		return true;
	}
	else 
	{
		return false;
	}

}
//does the ray intersect the floor?
bool floorTest(vector3 floorpoint)
{
	
	if((floorpoint.getX()>=-75) && (floorpoint.getX() <= 75) && (floorpoint.getZ() >= -75)
	&& (floorpoint.getZ() <= 75))
		return true;
	else
		return false;

}
//the render function using the R R T algorithm
void render2()
{
	
	vector3 newColor(0.0, 0.0, 0.0);
	vector3 currentPixel(0.0, 0.0, 0.0);
	ray currentRay(viewer, currentPixel);
	ray *pntrRay = NULL;
	pntrRay = &currentRay;
		
	for (int i = -500; i <imageHeight; i++)
	//can use the below to increase amount of rays
	//for (double i = -500.0; i < imageHeight; i += 0.25)
	{
		for (int j = -500; j < imageWidth; j++)
		////can use the below to increase amount of rays
		//for (double j = -500.00; j < imageWidth; j += 0.25)
		{
			
			pntrRay->setRayDirection(i,j,imageDepth);
			newColor = rrTrace(pntrRay, 0);
			glColor3f(newColor.x, newColor.y,  newColor.z);
				
			glBegin(GL_POLYGON);

				glVertex3f(i, j, imageDepth);

				glVertex3f(i+1, j, imageDepth);

				glVertex3f(i+1, j+1, imageDepth);

				glVertex3f(i, j+1, imageDepth);

			glEnd();
		
		}
	}
	
}


// recursive ray trace algorithm
vector3 rrTrace(ray *r, int d)
{
	vector3 newColor(0.0, 0.0, 0.0);// the color we will return
	vector3 reflect(0.0,0.0,0.0);// the reflected vector
	vector3 noColor(0.0,0.0,0.0);// the no color contribution value
	vector3 newintersect(0.0, 0.0, 0.0);// the intersection point found
	vector3 shadowTestPoint(0.0,0.0,0.0);
		
	ray childRay(newintersect, lightPosition);//the child ray
	
	static ray *rPntr;
	static vector3 *point;
			
	if (d > dmax)
	{
		return newColor;
	}
	//determine if there is a point of intersect
	point = (testintersect(r));
	
	if (!point)//no point found
	{
	
		if(d == 0)//first call and no intersection so we just want the background
			return  background;
		if(d > 0)//last call of recursion and no intersection so we don't need to return any color
			return noColor;
	}
	else//we found a point
	{
		newintersect = *point;
		shadowTestPoint = newintersect;
		

		newColor = aggColorCont(newintersect);
		if((point) && (newintersect.isReflective()))//a point on the floor
		{		
			reflect = newintersect.subtract(viewer).reflect(floorNormal);//reflected ray
			reflect = reflect.add(newintersect);
			childRay.setRayOriginVector(newintersect);
			childRay.setRayDirectionVector(reflect);
			r = &childRay;

			
			if (inShadow(shadowTestPoint))
			{
				
				newColor = shadow;
			}

			newColor = newColor.add(rrTrace(r, d+1));//recursive call
		}
		if ((point) && !(newintersect.isReflective()))//a point on the wall
		{
			return lightRed;
		
		}
	}
		
	return newColor;
}
//return the color of the intersect point
vector3 aggColorCont(vector3 point)
{
	
	return localColor(point, grey, floorNormal);

}
//test the ray cast for possible intersections
vector3 *testintersect(ray *CurrentRay)
{
		
	float floorDistance = 0.0;
	float wallDistance = 0.0;

	vector3 floorpoint(0.0,0.0,0.0);
	vector3 wallpoint(0.0, 0.0, 0.0);
	static vector3 *vecwPntr;
	static vector3 *vecfPntr;

	floorpoint = floorDef.intersect(CurrentRay->getRayDirection(), CurrentRay->getRayOrigin());
	wallpoint = wall.intersect(CurrentRay->getRayDirection(), CurrentRay->getRayOrigin());
		
	vecwPntr = &wallpoint;
	vecfPntr = &floorpoint;
	
	//is the ray coming of a relective object?
	if(CurrentRay->getRayOriginReflection())
	{
		
		//is this ray hitting the wall?
		if(wallTest(wallpoint))
		{
			vecwPntr->setReflective(false);
			return vecwPntr;
		}
		else//then it will hit the light source
		{
			return NULL;
		}

	}

	else// then the ray must be coming off the floor or from the viewer
	{
		// the ray has hit nothing
		if(!wallTest(wallpoint) && !floorTest(floorpoint))
		{
		
			return NULL;
		}
		// the ray hit the wall
		else if(wallTest(wallpoint))
		{
			vecwPntr->setReflective(false);
			return vecwPntr;
		}
		// the ray hit the fllor
		else if(floorTest(floorpoint))
		{
			vecfPntr->setReflective(true);
			return vecfPntr;
		}
		// the ray has hit nothing
		else
		{
			return NULL;
		}
	}
	
}

bool inShadow(vector3 point)
{
	vector3 wallTestPoint(0.0, 0.0, 0.0);
	wallTestPoint = wall.intersect(point, lightPosition);
		
	if ( point.isReflective() && wallTest(wallTestPoint) )//if the ray is coming of the floor and hitting
	//the light source then it is in shadow
	{
				
		return true;
	}
	else
		return false;
}

void initialize()
{

	// set background color
	glClearColor(0.5, 0.7, 0.5, 0.0);
	
}



// calculate local color

// local color is intensity * base color

vector3 localColor(vector3 intersect, vector3 baseColor, vector3 normal) {

	// calculate unit vector

	vector3 origin = lightPosition.subtract(intersect);

	vector3 unitVec = origin.normalize();
	// calculate dot product

	float dotProd = unitVec.dot(normal);
	
	// calculate intensity

	float ambientContr = ambient_coef;

	float diffuseContr = diffuse_coef * dotProd;

	float intensity = ambientContr + diffuseContr;

	if (intensity > 1.0) intensity = 1.0;

	float r = intensity * baseColor.x;

	float g = intensity * baseColor.y;

	float b = intensity * baseColor.z;
	
	return vector3(r,g,b);

}


// render prev. method not using recursion
/*
void render() {

	// render the floor

	for (int i=-75; i < 75; i++) {

		for (int j=-75; j < 75; j++) {

			vector3 intersect = vector3(i,0,j);

			vector3 color = localColor(intersect, grey, floorNormal);	// local color of the floor
			
			// reflection color of floor

			vector3 reflectColor(0.0, 0.0, 0.0);

			vector3 mixedColor(0.0, 0.0, 0.0);
			
			vector3 reflect = intersect.subtract(viewer).reflect(floorNormal);

			vector3 sm = wall.intersect(intersect, intersect.add(reflect));
			
			// test for inclusion - hardcoded

			if ( (sm.x >= -25.0) && (sm.x <= 25.0) && (sm.y >= 0.0) && (sm.y <= 50.0) ) {    // test for inclusion

				vector3 reflectColor = localColor(sm, lightRed, wallNormal);

				mixedColor = color.scalar(local_coef).add(reflectColor.scalar(reflect_coef));

			}

			else {

				mixedColor = color;		// outside of the reflection, use local color only
			
			}



			glColor3f(mixedColor.x, mixedColor.y, mixedColor.z);



			// use the small rectangles method

			glBegin(GL_POLYGON);

				glVertex3i(i, 0, j);

				glVertex3i(i+1, 0, j);

				glVertex3i(i+1, 0, j+1);

				glVertex3i(i, 0, j+1);

			glEnd();

		}

	}

	// render the wall - non-reflective surface

	for (int m=-25; m<25; m++) {

		for(int n=0; n<50; n++) {

			vector3 color = localColor(vector3(m,n,0), lightRed, wallNormal);

			glColor3f(color.x, color.y, color.z);

			glRecti(m, n, m+1, n+1);

		}

	}

}
*/
// display registry

void display(void) {

	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	gluLookAt(viewer.x, viewer.y, (viewer.z), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	//render();
	render2();
	
	glutSwapBuffers();

}



// reshape registry

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);

	glMatrixMode(GL_MODELVIEW);

}



// main program

void main(int argc, char **argv)

{

	glutInit( &argc, argv );

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;

	glutInitWindowSize(500, 500);

  	glutInitWindowPosition(100, 100);

	int windowHandle = glutCreateWindow("Athabasca University - TME 4-2");

	glutSetWindow(windowHandle);
	
	glutDisplayFunc( display );
	
	glutReshapeFunc( reshape );
		
	initialize();
	
	printf("end...: \n");

    glutMainLoop();

	
}