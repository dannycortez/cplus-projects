


#include "stdafx.h"

#include <math.h>

#include "vector3.h"



vector3 vector3 :: normalize() {

	float length = sqrt( (x * x) + (y * y) + (z * z) );

	if ( (length > -0.01) && (length < 0.01) )

		return vector3(0.0, 0.0, 0.0);

	else

		return vector3( (x / length), (y / length), (z / length) );	

}



vector3 vector3 :: add(vector3 v) {

	return vector3(x + v.x, y + v.y, z + v.z);

}



vector3 vector3 :: subtract(vector3 v) {

	return vector3(x - v.x, y - v.y, z - v.z);

}



vector3 vector3 :: scalar(float f) {

	return vector3(x * f, y * f, z * f);

}



float vector3 :: dot(vector3 v) {

	return ( (x * v.x) + (y * v.y) + (z * v.z) );

}



vector3 vector3 :: cross(vector3 v) {

	float x1 = (y * v.z) - (z * v.y);

	float y1 = (z * v.x) - (x * v.z);

	float z1 = (x * v.y) - (y * v.x);



	return vector3(x1, y1, z1);

}



vector3 vector3 :: reflect(vector3 norm) {

	// u = v - 2 * |Inc * Norm| * Norm

	vector3 n_inc    = normalize();

	float   term1    = 2 * n_inc.dot(norm);

	vector3 term2    = norm.scalar(term1);

	

	return vector3(n_inc.subtract(term2));

}



float vector3 :: distance(vector3 v) 
{

	float dx = v.x - x;

	float dy = v.y - y;

	float dz = v.z - z;

	return sqrt((dx * dx) + (dy * dy) + (dz * dz));

}

void vector3::getValues()

{

	printf("x %f y %f z %f \n", x,y,z);
	

}

float vector3::getX()
{
	
	//printf("get x %f \n", x);
	return x;
}

float vector3::getY()
{
	return y;
}

float vector3::getZ()
{
	return z;
}

void vector3::setX(float newx)
{
	//printf("xnew: %f setting x\n",newx);
	x = newx;
	//printf("x: %f setting x\n", x);
}

void vector3::setY(float newy)
{
	y = newy;
}
void vector3::setZ(float newz)
{
	z = newz;
}

bool vector3::isReflective()
{
	//printf("is reflect %d\n", reflective);
	return reflective;
}

void vector3::setReflective(bool r)
{
	reflective = r;
	//printf("set reflect %d\n", reflective);
}