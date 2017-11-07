#ifndef MATRIX_H
#define MATRIX_H
#define PI acos(-1)
#include "VertexFunctions.h"
#include "FileFunctions.h"
#include "CallbackFunctions.h"
#include "GlobalVariables.h"

/*
All functions associated with matrices and geometric transformations
as well as definitions for matrix4 objects and the globalModelMatrix
*/

typedef GLfloat matrix4[4][4];

extern matrix4 globalModelMatrix;

void loadIdentity();

void multiplyMatrix(matrix4 matrix);
void multiplyVertex(vertex3 vertex);
void printMatrix(matrix4 matrix);
void printVertex(vertex3 vertex);

void scale(float x, float y, float z);
void translate(float x, float y, float z);
void rotate(float degrees, float x, float y, float z);
void rotateX(float degrees);
void rotateY(float degrees);
void rotateZ(float degrees);

void geometricTransformation();

#endif
