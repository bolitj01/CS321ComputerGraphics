 #include "../Header Files/VertexFunctions.h"
#include <stdio.h>

//Thomas Bolinger
//CS321 Project 2B
//All the functions associated with vertices.

//Set all the Z axis values to 0 for 2D display of 3D data (Orthographic projection)
void removeZAxis() {
	for (int i = 0; i < vertexCount; i++) {
		vertices[i][2] = 0;
	}
}

//Move vertexData so worldCoordinates are all positive or 0
void normalizeVertices() {
	for (int i = 0; i < vertexCount; i++) {
		vertices[i][0] += -worldLeft;
		vertices[i][1] += -worldBottom;
		vertices[i][2] += -worldNear;
	}
	
	//Update world coordinate boundaries
	worldRight += -worldLeft;
	worldLeft += -worldLeft;
	worldTop += -worldBottom;
	worldBottom += -worldBottom;
	worldFar += -worldNear;
	worldNear += -worldNear;
}


//Reset vertices to the values of the original vertices and specified direction
void resetVertices(vertex3* vertices, vertex3* originVertices, int* vertexDirections, int vertexDirection, int vertexCount) {
	for (int i = 0; i < vertexCount; i++) {
		vertices[i][0] = originVertices[i][0];
		vertices[i][1] = originVertices[i][1];
		vertexDirections[i] = vertexDirection;
	}
}

//Find height and width of object represented by vertices
void getObjectHeightWidthDepthCenter() {
	//Find high and low values of each dimension
	float highX = -worldWidth * 100;
	float lowX = worldWidth * 100;
	float highY = -worldHeight * 100;
	float lowY = worldHeight * 100;
	float highZ = -worldDepth * 100;
	float lowZ = worldDepth * 100;
	for (int i = 0; i < vertexCount; i++) {
		float x = vertices[i][0];
		float y = vertices[i][1];
		float z = vertices[i][2];

		if (x > highX) {
			highX = x;
		}
		else if (x < lowX) {
			lowX = x;
		}

		if (y > highY) {
			highY = y;
		}
		else if (y < lowY) {
			lowY = y;
		}

		if (z > highZ) {
			highZ = z;
		}
		else if (z < lowZ) {
			lowZ = z;
		}
	}

	//Object dimensions are the difference of the high and low values
	objectHeight = highY - lowY;
	objectWidth = highX - lowX;
	objectDepth = highZ - lowZ;

	//Update center point of object
	objectCenter[0] = highX - (objectWidth / 2);
	objectCenter[1] = highY - (objectHeight / 2);
	objectCenter[2] = highZ - (objectDepth / 2);
	for (int i = 0; i < 3; i++) {
		if (abs((long)objectCenter[i]) < .01) {
			objectCenter[i] = 0;
		}
	}
}

//Convert screen coordinates to world coordinates
void screenToWorldCoordinates(int screenX, int screenY, float* worldX, float* worldY) {
	float screenPercentage = (float)screenX / (float)screenWidth;
	*worldX = screenPercentage * (worldWidth * 2) - worldWidth;
	screenPercentage = (float)screenY / (float)screenHeight;
	*worldY = -(screenPercentage * (worldHeight * 2) - worldHeight);
}