#include "UtilityFunctions.h"

//Normalizes the vector
void normalizeVector(float* vector) {
	double magnitude = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);

	for (int i = 0; i < 3; i++) {
		vector[i] = vector[i] / magnitude;
	}
}

//Calculates the cross product of two vectors, storing the result in the first vector
float* vectorCrossProduct(float* vector1, float* vector2) {
	float* result = (float*)calloc(3, sizeof(float));

	result[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
	result[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
	result[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];

	return result;
}

//Update the camera's up vector using normalization and cross product
void updateCameraUpVector() {
	float* lookVector = (float*)calloc(3, sizeof(float));
	for (int i = 0; i < 3; i++) {
		lookVector[i] = cameraAtVertex[i] - cameraLocation[i];
	}

	normalizeVector(lookVector);

	printf("%f %f %f\n", lookVector[0], lookVector[1], lookVector[2]);

	float up[3] = { 0, 1, 0 };
	float* rightVector = vectorCrossProduct(lookVector, up);
	
	printf("%f %f %f\n", rightVector[0], rightVector[1], rightVector[2]);

	

	float* result = vectorCrossProduct(rightVector, lookVector);

	printf("%f %f %f\n\n", result[0], result[1], result[2]);

	for (int i = 0; i < 3; i++) {
		cameraUpVector[i] = result[i];
	}

	delete lookVector;
	delete rightVector;
	delete result;
	
}

//Calculate a new target position within a curved boundary between ball and goal
void calculateNewTargetPosition() {
	float randomZ = rand() % 300 + 200;
	float curveLocation = (randomZ - 200) / 300 * pi;
	float xyBound = sin(curveLocation);
	float randomY = rand() % 100 * xyBound + 3;
	float randomX = rand() % 100 * xyBound - 50;

	targetLocation[0] = randomX;
	targetLocation[1] = randomY;
	targetLocation[2] = randomZ;
}

//Convert screen coordinates to world coordinates
void screenToWorldCoordinates(int screenX, int screenY, float* worldX, float* worldY) {
	float screenPercentage = (float)screenX / (float)screenWidth;
	*worldX = -(screenPercentage * (worldRight * 2) - worldRight);
	screenPercentage = (float)screenY / (float)screenHeight;
	*worldY = -(screenPercentage * (worldTop * 2) - worldTop);
}