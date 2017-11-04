#ifndef GL_INITIALIZATION
#define _CRT_SECURE_NO_WARNINGS
#include <freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>


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
		}
		res = fscanf(fp, "%s", lineHeader);
	}
}
//Creates a dynamically allotted array (arrayPtr) and stores data from the input file
void createArrayG() {
	rewind(fp);
	int countv = 0;
	int countvn = 0;
	int countf = 0;
	int test;
	char lineHeader[128];
	verticeArrG = (double *)calloc(numOfV * 3, sizeof(double));
	normVecArrG = (double *)calloc(numOfVN * 3, sizeof(double));
	faceArrG = (int *)calloc(numOfFG * 6, sizeof(int));
	// read the first word of the line
	int res = fscanf(fp, "%s", lineHeader);
	while (res != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			fscanf(fp, "%lf %lf %lf\n", &verticeArrG[countv], &verticeArrG[countv + 1], &verticeArrG[countv + 2]);
			countv += 3;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf(fp, "%lf %lf %lf\n", &normVecArrG[countvn], &normVecArrG[countvn + 1], &normVecArrG[countvn + 2]);
			countvn += 3;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			fscanf(fp, "%d//%d %d//%d %d//%d", &faceArrG[countf], &faceArrG[countf + 1], &faceArrG[countf + 2], &faceArrG[countf + 3], &faceArrG[countf + 4], &faceArrG[countf + 5]);
			/*fscanf(fp, " %d %d %d ", &faceArr[countf], &faceArr[countf + 1], &faceArr[countf + 2]);
			countf += 3;*/
			countf += 6;
		}
		res = fscanf(fp, "%s", lineHeader);
	}
}

void createArrayB() {
	rewind(fp);
	int countv = 0;
	int countvn = 0;
	int countf = 0;
	int test;
	char lineHeader[128];
	verticeArrB = (double *)calloc(numOfV * 3, sizeof(double));
	normVecArrB = (double *)calloc(numOfVN * 3, sizeof(double));
	faceArrB = (int *)calloc(numOfFB * 3, sizeof(int));
	// read the first word of the line
	int res = fscanf(fp, "%s", lineHeader);
	while (res != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			fscanf(fp, "%lf %lf %lf\n", &verticeArrB[countv], &verticeArrB[countv + 1], &verticeArrB[countv + 2]);
			countv += 3;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf(fp, "%lf %lf %lf\n", &normVecArrB[countvn], &normVecArrB[countvn + 1], &normVecArrB[countvn + 2]);
			countvn += 3;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			fscanf(fp, " %d %d %d ", &faceArrB[countf], &faceArrB[countf + 1], &faceArrB[countf + 2]);
			countf += 3;
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
		vertexNum = faceArrG[i * 6];//First vertex
		vertice[0] = verticeArrG[(vertexNum * 3) - 3];
		vertice[1] = verticeArrG[(vertexNum * 3) - 2];
		vertice[2] = verticeArrG[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
		vertexNum = faceArrG[i * 6 + 2];//Second vertex
		vertice[0] = verticeArrG[(vertexNum * 3) - 3];
		vertice[1] = verticeArrG[(vertexNum * 3) - 2];
		vertice[2] = verticeArrG[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
		vertexNum = faceArrG[i * 6 + 4];//Third vertex
		vertice[0] = verticeArrG[(vertexNum * 3) - 3];
		vertice[1] = verticeArrG[(vertexNum * 3) - 2];
		vertice[2] = verticeArrG[(vertexNum * 3) - 1];
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
		vertexNum = faceArrB[i * 3];//First vertex
		vertice[0] = verticeArrB[(vertexNum * 3) - 3] - 500;
		vertice[1] = verticeArrB[(vertexNum * 3) - 2];
		vertice[2] = verticeArrB[(vertexNum * 3) - 1] - 200;
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
		vertexNum = faceArrB[i * 3 + 1];//Second vertex
		vertice[0] = verticeArrB[(vertexNum * 3) - 3] - 500;
		vertice[1] = verticeArrB[(vertexNum * 3) - 2];
		vertice[2] = verticeArrB[(vertexNum * 3) - 1] - 200;
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
		vertexNum = faceArrB[i * 3 + 2];//Third vertex
		vertice[0] = verticeArrB[(vertexNum * 3) - 3] - 500;
		vertice[1] = verticeArrB[(vertexNum * 3) - 2];
		vertice[2] = verticeArrB[(vertexNum * 3) - 1] - 200;
		vertice[3] = 1;
		glVertex3f(vertice[0], vertice[1], vertice[2]);
	}
	glEnd();

}




#endif
