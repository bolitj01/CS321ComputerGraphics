#include "DrawModels.h"

//Counts number of vector and face lines in the file
void countLines() {
	char lineHeader[128];
	numOfLines = 0;
	numOfV = 0;
	numOfVN = 0;
	numOfVT = 0;
	int res = fscanf(fp, "%s", lineHeader);
	while (res != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			numOfV++;
			numOfLines++;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			numOfVN++;
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			numOfVT++;
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
	verticeArrGoal = (float *)calloc(numOfV * 3, sizeof(float));
	normVecArrGoal = (float *)calloc(numOfVN * 3, sizeof(float));
	faceArrGoal = (int *)calloc(numOfFG * 6, sizeof(int));
	// read the first word of the line
	int res = fscanf(fp, "%s", lineHeader);
	while (res != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			fscanf(fp, "%f %f %f\n", &verticeArrGoal[countv], &verticeArrGoal[countv + 1], &verticeArrGoal[countv + 2]);
			countv += 3;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf(fp, "%f %f %f\n", &normVecArrGoal[countvn], &normVecArrGoal[countvn + 1], &normVecArrGoal[countvn + 2]);
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
	int countvt = 0;
	int countf = 0;
	int test;
	char lineHeader[128];
	verticeArrBall = (float *)calloc(numOfV * 3, sizeof(float));
	normVecArrBall = (float *)calloc(numOfVN * 3, sizeof(float));
	textVecArrBall = (float *)calloc(numOfVT * 2, sizeof(float));
	faceArrBall = (int *)calloc(numOfFB * 8, sizeof(int));
	// read the first word of the line
	int res = fscanf(fp, "%s", lineHeader);
	while (res != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			fscanf(fp, "%f %f %f\n", &verticeArrBall[countv], &verticeArrBall[countv + 1], &verticeArrBall[countv + 2]);
			countv += 3;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf(fp, "%f %f %f\n", &normVecArrBall[countvn], &normVecArrBall[countvn + 1], &normVecArrBall[countvn + 2]);
			countvn += 3;
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			fscanf(fp, "%f %f 0\n", &textVecArrBall[countvt], &textVecArrBall[countvt + 1]);
			countvt += 2;
			
		}
		else if (strcmp(lineHeader, "f") == 0) {
			fscanf(fp, " %d/%d %d/%d %d/%d %d/%d ", &faceArrBall[countf], &faceArrBall[countf + 1], &faceArrBall[countf + 2], &faceArrBall[countf + 3], &faceArrBall[countf + 4], &faceArrBall[countf + 5], &faceArrBall[countf + 6], &faceArrBall[countf + 7]);
			countf += 8;
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
	verticeArrStadium = (float *)calloc(numOfV * 3, sizeof(float));
	normVecArrStadium = (float *)calloc(numOfVN * 3, sizeof(float));
	faceArrStadium = (int *)calloc(numOfFS * 9, sizeof(int));
	// read the first word of the line
	int res = fscanf(fp, "%s", lineHeader);
	while (res != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			fscanf(fp, "%f %f %f\n", &verticeArrStadium[countv], &verticeArrStadium[countv + 1], &verticeArrStadium[countv + 2]);
			countv += 3;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf(fp, "%f %f %f\n", &normVecArrStadium[countvn], &normVecArrStadium[countvn + 1], &normVecArrStadium[countvn + 2]);
			countvn += 3;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			/*fscanf(fp, "%d//%d %d//%d %d//%d", &faceArrStadium[countf], &faceArrStadium[countf + 1], &faceArrStadium[countf + 2], &faceArrStadium[countf + 3], &faceArrStadium[countf + 4], &faceArrStadium[countf + 5]);
			countf += 6;*/
			fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &faceArrStadium[countf], &faceArrStadium[countf + 1], &faceArrStadium[countf + 2], &faceArrStadium[countf + 3], &faceArrStadium[countf + 4], &faceArrStadium[countf + 5], &faceArrStadium[countf + 6], &faceArrStadium[countf + 7], &faceArrStadium[countf + 8]);
			countf += 9;
		}
		res = fscanf(fp, "%s", lineHeader);
	}
}

void drawFileG() {
	int i = 0;
	int vertexNum = 0;
	int vertexNormNum = 0;
	glBegin(GL_TRIANGLES);
	for (i = 0; i < numOfFG; i++) {
		glColor3f(1.0, 1.0, 1.0);
		vertexNormNum = faceArrGoal[i * 6 + 1];
		verticeNorm[0] = normVecArrGoal[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrGoal[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrGoal[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexNum = faceArrGoal[i * 6];//First vertex
		vertice[0] = verticeArrGoal[(vertexNum * 3) - 3] + 400;
		vertice[1] = verticeArrGoal[(vertexNum * 3) - 2];
		vertice[2] = verticeArrGoal[(vertexNum * 3) - 1] + 200;
		vertice[3] = 1;

		vertexNormNum = faceArrGoal[i * 6 + 3];
		verticeNorm[0] = normVecArrGoal[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrGoal[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrGoal[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);
		vertexNum = faceArrGoal[i * 6 + 2];//Second vertex
		vertice[0] = verticeArrGoal[(vertexNum * 3) - 3] + 400;
		vertice[1] = verticeArrGoal[(vertexNum * 3) - 2];
		vertice[2] = verticeArrGoal[(vertexNum * 3) - 1] + 200;
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrGoal[i * 6 + 5];
		verticeNorm[0] = normVecArrGoal[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrGoal[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrGoal[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexNum = faceArrGoal[i * 6 + 4];//Third vertex
		vertice[0] = verticeArrGoal[(vertexNum * 3) - 3] + 400;
		vertice[1] = verticeArrGoal[(vertexNum * 3) - 2];
		vertice[2] = verticeArrGoal[(vertexNum * 3) - 1] + 200;
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
	}
	glEnd();
}

void drawFileB() {
	int i = 0;
	int vertexNum = 0;
	int vertexNormNum = 0;
	int vertexTexNum = 0;
	glBegin(GL_QUADS);
	for (i = 0; i < numOfFB; i++) {
		glColor3f(1.0, 1.0, 1.0);
		/*vertexNormNum = faceArrBall[i * 8 + 1];
		verticeNorm[0] = normVecArrBall[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrBall[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrBall[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);*/
		vertexTexNum = faceArrBall[i * 8 + 1];
		vertexNum = faceArrBall[i * 8];//First vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrBall[(vertexTexNum * 2) - 2], textVecArrBall[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		/*vertexNormNum = faceArrBall[i * 8 + 3];
		verticeNorm[0] = normVecArrBall[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrBall[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrBall[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);*/
		vertexTexNum = faceArrBall[i * 8 + 3];
		vertexNum = faceArrBall[i * 8 + 2];//Second vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrBall[(vertexTexNum * 2) - 2], textVecArrBall[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		/*vertexNormNum = faceArrBall[i * 8 + 5];
		verticeNorm[0] = normVecArrBall[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrBall[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrBall[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);*/
		vertexTexNum = faceArrBall[i * 8 + 5];
		vertexNum = faceArrBall[i * 8 + 4];//Third vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrBall[(vertexTexNum * 2) - 2], textVecArrBall[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		/*vertexNormNum = faceArrBall[i * 8 + 7];
		verticeNorm[0] = normVecArrBall[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrBall[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrBall[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);*/
		vertexTexNum = faceArrBall[i * 8 + 7];
		vertexNum = faceArrBall[i * 8 + 6];//Fourth vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrBall[(vertexTexNum * 2) - 2], textVecArrBall[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);
	}
	glEnd();

}

void drawFileS() {
	int i = 0;
	int vertexNum = 0;
	int vertexNormNum = 0;
	/*glBegin(GL_TRIANGLES);
	for (i = 0; i < numOfFS; i++) {
		glColor3f(1.0, 1.0, 1.0);
		vertexNormNum = faceArrStadium[i * 6 + 1];
		verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexNum = faceArrStadium[i * 6];//First vertex
		vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
		vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
		vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrStadium[i * 6 + 3];
		verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexNum = faceArrStadium[i * 6 + 2];//Second vertex
		vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
		vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
		vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrStadium[i * 6 + 5];
		verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexNum = faceArrStadium[i * 6 + 4];//Third vertex
		vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
		vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
		vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
	}
	glEnd();*/
	glBegin(GL_TRIANGLES);
	for (i = 0; i < numOfFS; i++) {
		glColor3f(1.0, 1.0, 1.0);
		vertexNormNum = faceArrStadium[i * 9 + 1];
		verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexNum = faceArrStadium[i * 9];//First vertex
		vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
		vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
		vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrStadium[i * 9 + 4];
		verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexNum = faceArrStadium[i * 9 + 3];//Second vertex
		vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
		vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
		vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrStadium[i * 9 + 7];
		verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexNum = faceArrStadium[i * 9 + 6];//Third vertex
		vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
		vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
		vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
	}
	glEnd();
}