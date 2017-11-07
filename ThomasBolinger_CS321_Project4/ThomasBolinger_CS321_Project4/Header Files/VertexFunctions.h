#ifndef VERTEX3_H
#define VERTEX3_H
#include <GL/freeglut.h>
#include <math.h>
#include "GlobalVariables.h"

//The data type and all the functions associated with vertices. Function descriptions are in the .cpp file
enum VertexDirection { VERTEX_DIRECTION_NORTH, VERTEX_DIRECTION_SOUTH, 
	VERTEX_DIRECTION_WEST, VERTEX_DIRECTION_EAST };
enum VertexGroupSpan { SPAN_HORIZONTAL, SPAN_VERTICAL };

void removeZAxis();
void normalizeVertices();
void resetVertices(vertex3* vertices, vertex3* originVertices, int* vertexDirections, int vertexDirection, int vertexCount);
void getObjectHeightWidthDepthCenter();
void screenToWorldCoordinates(int screenX, int screenY, float* worldX, float* worldY);
#endif // !VERTEX3_H

