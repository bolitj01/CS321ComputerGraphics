#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <math.h>
#include "GlobalVariables.h"

void normalizeVector(float* vector);
float* vectorCrossProduct(float* vector1, float* vector2);
void updateCameraUpVector();

#endif // !UTILITYFUNCTIONS_H

