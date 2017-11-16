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
		vertice[0] = verticeArrGoal[(vertexNum * 3) - 3];
		vertice[1] = verticeArrGoal[(vertexNum * 3) - 2];
		vertice[2] = verticeArrGoal[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
		vertexNum = faceArrGoal[i * 6 + 2];//Second vertex
		vertice[0] = verticeArrGoal[(vertexNum * 3) - 3];
		vertice[1] = verticeArrGoal[(vertexNum * 3) - 2];
		vertice[2] = verticeArrGoal[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
		vertexNum = faceArrGoal[i * 6 + 4];//Third vertex
		vertice[0] = verticeArrGoal[(vertexNum * 3) - 3];
		vertice[1] = verticeArrGoal[(vertexNum * 3) - 2];
		vertice[2] = verticeArrGoal[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
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
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3] - 500;
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1] - 200;
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
		vertexNum = faceArrBall[i * 3 + 1];//Second vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3] - 500;
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1] - 200;
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
		vertexNum = faceArrBall[i * 3 + 2];//Third vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3] - 500;
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1] - 200;
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
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
		vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
		vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
		vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
		vertexNum = faceArrStadium[i * 9 + 3];//Second vertex
		vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
		vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
		vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
		vertexNum = faceArrStadium[i * 9 + 6];//Third vertex
		vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
		vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
		vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
	}
	glEnd();
}