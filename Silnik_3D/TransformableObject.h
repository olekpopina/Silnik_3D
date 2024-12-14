#ifndef TRANSFORMABLEOBJECT_H
#define TRANSFORMABLEOBJECT_H
#include "Triangle.h"
#include "Cube.h"
#include <GL/freeglut.h>

class TransformableObject  {
	
public:
	static void scaleUp_Cube(float& scale);
	static void scaleDown_Cube(float& scale);
	static void scaleUp_Triangle(float& scale);
	static void scaleDown_Triangle(float& scale);
};



#endif