#include "DrawModels.h"

//Counts number of vector and face lines in the file
void countLines() {

	char lineHeader[128];
	numOfLines = 0;
	numOfV = 0;
	int res = fscanf(fp, "%s", lineHeader);
	while (res != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			numOfV++;
			numOfLines++;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			numOfVN++;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			if (currObj == 0) {
				numOfFB++;
			}
			else if (currObj == 1) {
				numOfFG++;
			}
			else if (currObj == 2) {
				numOfFS++;
			}
		}
		res = fscanf(fp, "%s", lineHeader);
	}
}
//Creates a dynamically allotted array (arrayPtr) and stores data from the input file
void createGoalData() {
	rewind(fp);
	int countv = 0;
	int countvn = 0;
	int countf = 0;
	int test;
	char lineHeader[128];
	verticeArrGoal = (double *)calloc(numOfV * 3, sizeof(double));
	normVecArrGoal = (double *)calloc(numOfVN * 3, sizeof(double));
	faceArrGoal = (int *)calloc(numOfFG * 6, sizeof(int));
	// read the first word of the line
	int res = fscanf(fp, "%s", lineHeader);
	while (res != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			fscanf(fp, "%lf %lf %lf\n", &verticeArrGoal[countv], &verticeArrGoal[countv + 1], &verticeArrGoal[countv + 2]);
			countv += 3;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf(fp, "%lf %lf %lf\n", &normVecArrGoal[countvn], &normVecArrGoal[countvn + 1], &normVecArrGoal[countvn + 2]);
			countvn += 3;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			fscanf(fp, "%d//%d %d//%d %d//%d", &faceArrGoal[countf], &faceArrGoal[countf + 1], &faceArrGoal[countf + 2], &faceArrGoal[countf + 3], &faceArrGoal[countf + 4], &faceArrGoal[countf + 5]);
			/*fscanf(fp, " %d %d %d ", &faceArr[countf], &faceArr[countf + 1], &faceArr[countf + 2]);
			countf += 3;*/
			countf += 6;
		}
		res = fscanf(fp, "%s", lineHeader);
	}
}

void createBallData() {
	rewind(fp);
	int countv = 0;
	int countvn = 0;
	int countf = 0;
	int test;
	char lineHeader[128];
	verticeArrBall = (double *)calloc(numOfV * 3, sizeof(double));
	normVecArrBall = (double *)calloc(numOfVN * 3, sizeof(double));
	faceArrBall = (int *)calloc(numOfFB * 3, sizeof(int));
	// read the first word of the line
	int res = fscanf(fp, "%s", lineHeader);
	while (res != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			fscanf(fp, "%lf %lf %lf\n", &verticeArrBall[countv], &verticeArrBall[countv + 1], &verticeArrBall[countv + 2]);
			countv += 3;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf(fp, "%lf %lf %lf\n", &normVecArrBall[countvn], &normVecArrBall[countvn + 1], &normVecArrBall[countvn + 2]);
			countvn += 3;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			fscanf(fp, " %d %d %d ", &faceArrBall[countf], &faceArrBall[countf + 1], &faceArrBall[countf + 2]);
			countf += 3;
		}
		res = fscanf(fp, "%s", lineHeader);
	}
}

void createArrayS() {
	rewind(fp);
	int countv = 0;
	int countvn = 0;
	int countf = 0;
	int test;
	char lineHeader[128];
	verticeArrStadium = (double *)calloc(numOfV * 3, sizeof(double));
	normVecArrStadium = (double *)calloc(numOfVN * 3, sizeof(double));
	faceArrStadium = (int *)calloc(numOfFS * 9, sizeof(int));
	// read the first word of the line
	int res = fscanf(fp, "%s", lineHeader);
	while (res != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			fscanf(fp, "%lf %lf %lf\n", &verticeArrStadium[countv], &verticeArrStadium[countv + 1], &verticeArrStadium[countv + 2]);
			countv += 3;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf(fp, "%lf %lf %lf\n", &normVecArrStadium[countvn], &normVecArrStadium[countvn + 1], &normVecArrStadium[countvn + 2]);
			countvn += 3;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			fscanf(fp, "%d/%d/d %d/%d/%d %d/%d/%d", &faceArrStadium[countf], &faceArrStadium[countf + 1], &faceArrStadium[countf + 2], &faceArrStadium[countf + 3], &faceArrStadium[countf + 4], &faceArrGoal[countf + 5], &faceArrStadium[countf + 6], &faceArrStadium[countf + 7], &faceArrGoal[countf + 8]);
			/*fscanf(fp, " %d %d %d ", &faceArr[countf], &faceArr[countf + 1], &faceArr[countf + 2]);
			countf += 3;*/
			countf += 9;
		}
		res = fscanf(fp, "%s", lineHeader);
	}
}

void drawFileG() {
	int i = 0;
	int vertexNum = 0;
	glBegin(GL_TRIANGLES);
	for (i = 0; i < numOfFG; i++) {
		glColor3f(.4, .4, .3);
		vertexNum = faceArrGoal[i * 6];//First vertex
		vertex[0] = verticeArrGoal[(vertexNum * 3) - 3];
		vertex[1] = verticeArrGoal[(vertexNum * 3) - 2];
		vertex[2] = verticeArrGoal[(vertexNum * 3) - 1];
		vertex[3] = 1;
		glVertex3f(vertex[0], vertex[1], vertex[2]);
		vertexNum = faceArrGoal[i * 6 + 2];//Second vertex
		vertex[0] = verticeArrGoal[(vertexNum * 3) - 3];
		vertex[1] = verticeArrGoal[(vertexNum * 3) - 2];
		vertex[2] = verticeArrGoal[(vertexNum * 3) - 1];
		vertex[3] = 1;
		glVertex3f(vertex[0], vertex[1], vertex[2]);
		vertexNum = faceArrGoal[i * 6 + 4];//Third vertex
		vertex[0] = verticeArrGoal[(vertexNum * 3) - 3];
		vertex[1] = verticeArrGoal[(vertexNum * 3) - 2];
		vertex[2] = verticeArrGoal[(vertexNum * 3) - 1];
		vertex[3] = 1;
		glVertex3f(vertex[0], vertex[1], vertex[2]);
	}
	glEnd();
}

void drawFileB() {
	int i = 0;
	int vertexNum = 0;
	glBegin(GL_TRIANGLES);
	for (i = 0; i < numOfFB; i++) {
		glColor3f(0.0, 0.0, 0.0);
		vertexNum = faceArrBall[i * 3];//First vertex
		vertex[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertex[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertex[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertex[3] = 1;
		glVertex3f(vertex[0], vertex[1], vertex[2]);
		vertexNum = faceArrBall[i * 3 + 1];//Second vertex
		vertex[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertex[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertex[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertex[3] = 1;
		glVertex3f(vertex[0], vertex[1], vertex[2]);
		vertexNum = faceArrBall[i * 3 + 2];//Third vertex
		vertex[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertex[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertex[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertex[3] = 1;
		glVertex3f(vertex[0], vertex[1], vertex[2]);
	}
	glEnd();

}

void drawFileS() {
	int i = 0;
	int vertexNum = 0;
	glBegin(GL_TRIANGLES);
	for (i = 0; i < numOfFS; i++) {
		glColor3f(.4, .4, .3);
		vertexNum = faceArrStadium[i * 9];//First vertex
		vertex[0] = verticeArrStadium[(vertexNum * 3) - 3];
		vertex[1] = verticeArrStadium[(vertexNum * 3) - 2];
		vertex[2] = verticeArrStadium[(vertexNum * 3) - 1];
		vertex[3] = 1;
		glVertex3f(vertex[0], vertex[1], vertex[2]);
		vertexNum = faceArrStadium[i * 9 + 3];//Second vertex
		vertex[0] = verticeArrStadium[(vertexNum * 3) - 3];
		vertex[1] = verticeArrStadium[(vertexNum * 3) - 2];
		vertex[2] = verticeArrStadium[(vertexNum * 3) - 1];
		vertex[3] = 1;
		glVertex3f(vertex[0], vertex[1], vertex[2]);
		vertexNum = faceArrStadium[i * 9 + 6];//Third vertex
		vertex[0] = verticeArrStadium[(vertexNum * 3) - 3];
		vertex[1] = verticeArrStadium[(vertexNum * 3) - 2];
		vertex[2] = verticeArrStadium[(vertexNum * 3) - 1];
		vertex[3] = 1;
		glVertex3f(vertex[0], vertex[1], vertex[2]);
	}
	glEnd();
}

//Calculate object's bottom center
double* getObjectParameters(int vertexCount, double* vertices) {

	double* bottomCenter = (double*)calloc(3, sizeof(double));

	float highX = 0, lowX = 0, lowY = 0, highY = 0, highZ = 0, lowZ = 0;

	//Find highs and lows of each dimension
	for (int i = 0; i < vertexCount; i++) {
		if (vertices[i * 3] > highX) {
			highX = vertices[i * 3];
		}
		else if (vertices[i * 3] < lowX) {
			lowX = vertices[i * 3];
		}
		
		if (vertices[i * 3 + 1] < lowY) {
			lowY = vertices[i * 3 + 1];
		}
		else if (vertices[i * 3 + 1] > highY) {
			highY = vertices[i * 3 + 1];
		}

		if (vertices[i * 3 + 2] > highZ) {
			highZ = vertices[i * 3 + 2];
		}
		else if (vertices[i * 3 + 2] < lowZ) {
			lowZ = vertices[i * 3 + 2];
		}
	}

	bottomCenter[0] = (highX + lowX) / 2;
	bottomCenter[1] = lowY;
	bottomCenter[2] = (highZ + lowZ) / 2;

	//Get radius if object is the ball
	if (currObj == 0) {
		ballRadius = (highX - lowX) / 2;
	}
	//Get width, height, and depth if object is the goal
	if (currObj == 1) {
		goalWidth = highX - lowX;
		goalHeight = highY - lowY;
		goalDepth = highZ - lowZ;
	}

	return bottomCenter;
}