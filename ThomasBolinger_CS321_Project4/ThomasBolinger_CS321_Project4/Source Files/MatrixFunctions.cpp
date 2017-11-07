#include "../Header Files/MatrixFunctions.h"

//External global matrix for the model
matrix4 globalModelMatrix;

void loadIdentity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				globalModelMatrix[i][j] = 1;
			}
			else {
				globalModelMatrix[i][j] = 0;
			}
		}
	}
}

//Multiply globalModelMatrix by the given 4x4 matrix and store result in globalModelMatrix
//(typdef passes by reference so no pointer needed)
void multiplyMatrix(matrix4 matrix) {
	matrix4 result;
	/*printMatrix(matrix);
	printMatrix(globalModelMatrix);*/

	//Calculate each sum of products for each matrix cell
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			GLfloat sum = 0;

			//Perform multiplications and add to sum
			for (int x = 0; x < 4; x++) {
				float local = matrix[i][x];
				float global = globalModelMatrix[i][x];
				sum += globalModelMatrix[i][x] * matrix[x][j];
			}
			
			//Assign to result matrix
			result[i][j] = sum;
		}
	}
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			globalModelMatrix[i][j] = result[i][j];
		}
	}
	/*memcpy(globalModelMatrix, result, sizeof(float) * 16);*/
}


//Multiply globalModelMatrix by a given 4x1 vertex and store result in vertex
void multiplyVertex(vertex3 vertex) {
	vertex3 result;
	
	//printMatrix(globalModelMatrix);
	//printVertex(vertex);

	//Convert 3D vertex to homogenous 4D vertex for multiplication
	GLfloat vertex4[4];
	vertex4[0] = vertex[0];
	vertex4[1] = vertex[1];
	vertex4[2] = vertex[2];
	vertex4[3] = 1;
	//Calculate each vertex value
	for (int i = 0; i < 4; i++) {
		GLfloat sum = 0;
		for (int j = 0; j < 4; j++) {
			sum += globalModelMatrix[i][j] * vertex4[j];
		}
		if (i < 3) {
			result[i] = sum;
		}
	}
	memcpy(vertex, result, sizeof(float) * 3);
}

//Perform nonuniform scaling of globalModelMatrix
void scale(float x, float y, float z) {
	matrix4 scaleMatrix = { {x, 0, 0, 0,}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1} };
	multiplyMatrix(scaleMatrix);
}

//Perform nonuniform translation of globalModelMatrix
void translate(float x, float y, float z) {
	matrix4 translateMatrix = { {1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1} };
	multiplyMatrix(translateMatrix);
}

//Perform rotation of specified degrees around specified vector pointing from origin
void rotate(float degrees, float x, float y, float z) {
	double radians = degrees * PI / 180;
	double c = cos(radians);
	double s = sin(radians);
	matrix4 rotateMatrix = { {	x * x * (1 - c) + c,	y * x * (1 - c) + z * s,	x * y * (1 - c) - z * s,	0},
							 { x * z * (1 - c) + y * s,	y * y * (1 - c) + c,		y * z * (1 - c) + x * s,	0},
							 {	x * z * (1 - c) - y * s,	y * z * (1 - c) + x * s,	z * z * (1 - c) + c,		0},
							 {	0,							0,							0,							1} };
	multiplyMatrix(rotateMatrix);
}

//Rotate around x-axis
void rotateX(float degrees) {
	double radians = degrees * PI / 180;
	double c = cos(radians);
	double s = sin(radians);
	matrix4 rotateXMatrix = { {1, 0, 0, 0}, {0, c, -s, 0}, {0, s, c, 0}, {0, 0, 0, 1} };
	multiplyMatrix(rotateXMatrix);
}

//Rotate around the y-axis
void rotateY(float degrees) {
	double radians = degrees * PI / 180;
	double c = cos(radians);
	double s = sin(radians);
	matrix4 rotateYMatrix = { {c, 0, s, 0}, {0, 1, 0, 0}, {-s, 0, c, 0}, {0, 0, 0, 1} };
	multiplyMatrix(rotateYMatrix);
}

//Rotate around the z-axis
void rotateZ(float degrees) {
	double radians = degrees * PI / 180;
	double c = cos(radians);
	double s = sin(radians);
	matrix4 rotateZMatrix = { { c, -s, 0, 0 },{ s, c, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } };
	multiplyMatrix(rotateZMatrix);
}

//Apply geometric transformations to vertices by multiplying globalModelMatrix to all vertices
void geometricTransformation() {
	//Transform all object vertices
	for (int i = 0; i < vertexCount; i++) {
		multiplyVertex(vertices[i]);
	}
}



//Print 4v4 matrix to console
void printMatrix(matrix4 matrix) {
	printf("Matrix:\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("[%-5f]", matrix[i][j]);
		}
		printf("\n");
	}
}

//Print 4x1 vertex to console
void printVertex(vertex3 vertex) {
	printf("Vertex:\n");
	for (int i = 0; i < 3; i++) {
		printf("[%-5f]", vertex[i]);
		printf("\n");
	}
}