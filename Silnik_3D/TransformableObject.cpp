#include "TransformableObject.h"


void TransformableObject::scaleUp_Cube(float& scale) {
	scale *= 1.1f;
}
void TransformableObject::scaleDown_Cube(float& scale) {
	scale *= 0.9f;
}

void TransformableObject::scaleUp_Triangle(float& scale) {
  scale *= 1.1f;
}

void TransformableObject::scaleDown_Triangle(float& scale) {
	scale *= 0.9f;
}

