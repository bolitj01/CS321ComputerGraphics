#include "DrawModels.h"
#include "TextureMapping.h"

//Counts number of vector and face lines in the file
void countLines() {
	char lineHeader[128];
	numOfLines = 0;
	numOfV = 0;
	numOfVN = 0;
	numOfVT = 0;
	numOfMat = 0;
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
		else if (strcmp(lineHeader, "g") == 0) {
			numOfMat++;
		}
		else if (strcmp(lineHeader, "u") == 0) {
			numOfS++;
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
			else if (currObj == 3) {
				numOfFL++;
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
	//initializeTextures("soccerMap3.ppm");
	/*rewind(fp);
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
	}*/
	rewind(fp);
	int countv = 0;
	int countvn = 0;
	int countvt = 0;
	int countf = 0;
	int counts = 0;
	char lineHeader[128];
	verticeArrBall = (float *)calloc(numOfV * 3, sizeof(float));
	normVecArrBall = (float *)calloc(numOfVN * 3, sizeof(float));
	textVecArrBall = (float *)calloc(numOfVT * 2, sizeof(float));
	faceArrBall = (int *)calloc(numOfFB * 12, sizeof(int));
	sArrBall = (int *)calloc(numOfMat, sizeof(int));
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
			fscanf(fp, "%f %f\n", &textVecArrBall[countvt], &textVecArrBall[countvt + 1]);
			countvt += 2;

		}
		else if (strcmp(lineHeader, "u") == 0) {
			sArrBall[counts] = countf;
			counts++;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			fscanf(fp, " %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d ", &faceArrBall[countf], &faceArrBall[countf + 1], &faceArrBall[countf + 2], &faceArrBall[countf + 3], &faceArrBall[countf + 4], &faceArrBall[countf + 5], &faceArrBall[countf + 6], &faceArrBall[countf + 7], &faceArrBall[countf + 8], &faceArrBall[countf + 9], &faceArrBall[countf + 10], &faceArrBall[countf + 11]);
			countf += 12;
		}
		res = fscanf(fp, "%s", lineHeader);
	}
}

void createLampData() {
	rewind(fp);
	int countv = 0;
	int countvn = 0;
	int countvt = 0;
	int countf = 0;
	int countm = 0;
	int test;
	char lineHeader[128];
	verticeArrLamp = (float *)calloc(numOfV * 3, sizeof(float));
	normVecArrLamp = (float *)calloc(numOfVN * 3, sizeof(float));
	textVecArrLamp = (float *)calloc(numOfVT * 2, sizeof(float));
	faceArrLamp = (int *)calloc(numOfFS * 12, sizeof(int));
	int res = fscanf(fp, "%s", lineHeader);
	while (res != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			fscanf(fp, "%f %f %f\n", &verticeArrLamp[countv], &verticeArrLamp[countv + 1], &verticeArrLamp[countv + 2]);
			countv += 3;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf(fp, "%f %f %f\n", &normVecArrLamp[countvn], &normVecArrLamp[countvn + 1], &normVecArrLamp[countvn + 2]);
			countvn += 3;
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			fscanf(fp, "%f %f\n", &textVecArrLamp[countvt], &textVecArrLamp[countvt + 1]);
			countvt += 2;

		}
		else if (strcmp(lineHeader, "f") == 0) {
			fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &faceArrLamp[countf], &faceArrLamp[countf + 1], &faceArrLamp[countf + 2], &faceArrLamp[countf + 3], &faceArrLamp[countf + 4], &faceArrLamp[countf + 5], &faceArrLamp[countf + 6], &faceArrLamp[countf + 7], &faceArrLamp[countf + 8], &faceArrLamp[countf + 9], &faceArrLamp[countf + 10], &faceArrLamp[countf + 11]);
			countf += 12;
		}
		res = fscanf(fp, "%s", lineHeader);
	}
}

void createTargetData() {
	targetScale = 9;

	verticeArrTarget = (float**)calloc(9, sizeof(float*));
	for (int i = 0; i < 9; i++) {
		verticeArrTarget[i] = (float*)calloc(3, sizeof(float));
	}
	normVecArrTarget = (float**)calloc(9, sizeof(float*));
	for (int i = 0; i < 9; i++) {
		normVecArrTarget[i] = (float*)calloc(3, sizeof(float));
	}

	//Top right back
	verticeArrTarget[0][0] = 1;
	verticeArrTarget[0][1] = 1;
	verticeArrTarget[0][2] = 1;
	//Top right front
	verticeArrTarget[1][0] = 1;
	verticeArrTarget[1][1] = 1;
	verticeArrTarget[1][2] = -1;
	//Top left front
	verticeArrTarget[2][0] = -1;
	verticeArrTarget[2][1] = 1;
	verticeArrTarget[2][2] = -1;
	//Top left back
	verticeArrTarget[3][0] = -1;
	verticeArrTarget[3][1] = 1;
	verticeArrTarget[3][2] = 1;

	//Bottom left back
	verticeArrTarget[4][0] = -1;
	verticeArrTarget[4][1] = -1;
	verticeArrTarget[4][2] = 1;
	//Bottom left front
	verticeArrTarget[5][0] = -1;
	verticeArrTarget[5][1] = -1;
	verticeArrTarget[5][2] = -1;
	//Bottom right front
	verticeArrTarget[6][0] = 1;
	verticeArrTarget[6][1] = -1;
	verticeArrTarget[6][2] = -1;
	//Bottom right back
	verticeArrTarget[7][0] = 1;
	verticeArrTarget[7][1] = -1;
	verticeArrTarget[7][2] = 1;

	//Bottom triangle bottom
	verticeArrTarget[8][0] = 0;
	verticeArrTarget[8][1] = -2;
	verticeArrTarget[8][2] = 0;

	//Up normal
	normVecArrTarget[0][0] = 0;
	normVecArrTarget[0][1] = 1;
	normVecArrTarget[0][2] = 0;
	//Left normal
	normVecArrTarget[1][0] = -1;
	normVecArrTarget[1][1] = 0;
	normVecArrTarget[1][2] = 0;
	//Right normal
	normVecArrTarget[2][0] = 1;
	normVecArrTarget[2][1] = 0;
	normVecArrTarget[2][2] = 0;
	//Front normal
	normVecArrTarget[3][0] = 0;
	normVecArrTarget[3][1] = 0;
	normVecArrTarget[3][2] = -1;
	//Back normal
	normVecArrTarget[4][0] = 0;
	normVecArrTarget[4][1] = 0;
	normVecArrTarget[4][2] = 1;

	//Down left normal
	normVecArrTarget[5][0] = -1;
	normVecArrTarget[5][1] = -1;
	normVecArrTarget[5][2] = 0;
	//Down right normal
	normVecArrTarget[6][0] = 1;
	normVecArrTarget[6][1] = -1;
	normVecArrTarget[6][2] = 0;
	//Down back normal
	normVecArrTarget[7][0] = 0;
	normVecArrTarget[7][1] = -1;
	normVecArrTarget[7][2] = 1;
	//Down front normal
	normVecArrTarget[8][0] = 0;
	normVecArrTarget[8][1] = -1;
	normVecArrTarget[8][2] = -1;
}

void createStadiumData() {
	rewind(fp);
	int countv = 0;
	int countvn = 0;
	int countvt = 0;
	int countf = 0;
	int countm = 0;
	int test;
	char lineHeader[128];
	verticeArrStadium = (float *)calloc(numOfV * 3, sizeof(float));
	normVecArrStadium = (float *)calloc(numOfVN * 3, sizeof(float));
	textVecArrStadium = (float *)calloc(numOfVT * 2, sizeof(float));
	matArrStadium = (char *)calloc(numOfMat, sizeof(char));
	faceArrStadium = (int *)calloc(numOfFS * 9 + 18, sizeof(int));//15 is number of tags
																  // read the first word of the line
	int res = fscanf(fp, "%s", lineHeader);
	while (res != EOF) {
		if (strcmp(lineHeader, "g") == 0) {
			fgets(lineHeader, 128, fp);
			fgets(lineHeader, 128, fp);
			materialType = strchr(lineHeader, ' ');
			materialType++;
			matArrStadium[countm] = materialType[0];
			countm++;
			faceArrStadium[countf] = -999;//Special char, signals new section
			countf++; //Division between face sections
		}
		else if (strcmp(lineHeader, "v") == 0) {
			fscanf(fp, "%f %f %f\n", &verticeArrStadium[countv], &verticeArrStadium[countv + 1], &verticeArrStadium[countv + 2]);
			countv += 3;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf(fp, "%f %f %f\n", &normVecArrStadium[countvn], &normVecArrStadium[countvn + 1], &normVecArrStadium[countvn + 2]);
			countvn += 3;
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			fscanf(fp, "%f %f 0\n", &textVecArrStadium[countvt], &textVecArrStadium[countvt + 1]);
			countvt += 2;

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
	glDisable(GL_TEXTURE_2D);
	int i = 0;
	int vertexNum = 0;
	int vertexNormNum = 0;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < numOfFG; i++) {
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
	glEnable(GL_TEXTURE_2D);
}

void drawFileB() {
	glDisable(GL_TEXTURE_2D);
	int i = 0;
	int vertexNum = 0;
	int vertexNormNum = 0;
	int vertexTexNum = 0;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	for (i = 0; i < 1919; i++) {//Black

		vertexNormNum = faceArrBall[i * 12 + 2];
		verticeNorm[0] = normVecArrBall[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrBall[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrBall[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexTexNum = faceArrBall[i * 12 + 1];
		vertexNum = faceArrBall[i * 12];//First vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrBall[(vertexTexNum * 2) - 2], textVecArrBall[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrBall[i * 12 + 5];
		verticeNorm[0] = normVecArrBall[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrBall[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrBall[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexTexNum = faceArrBall[i * 12 + 4];
		vertexNum = faceArrBall[i * 12 + 3];//Second vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrBall[(vertexTexNum * 2) - 2], textVecArrBall[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrBall[i * 12 + 8];
		verticeNorm[0] = normVecArrBall[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrBall[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrBall[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexTexNum = faceArrBall[i * 12 + 7];
		vertexNum = faceArrBall[i * 12 + 6];//Third vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrBall[(vertexTexNum * 2) - 2], textVecArrBall[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrBall[i * 12 + 11];
		verticeNorm[0] = normVecArrBall[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrBall[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrBall[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexTexNum = faceArrBall[i * 12 + 10];
		vertexNum = faceArrBall[i * 12 + 9];//Fourth vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrBall[(vertexTexNum * 2) - 2], textVecArrBall[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);
	}
	glColor3f(0.0, 0.0, 0.0);
	for (; i < numOfFB; i++) {//White
							  //printf("NUM OF TIMES: %d\n", i);
		glColor3f(0.0, 0.0, 0.0);
		vertexNormNum = faceArrBall[i * 12 + 2];
		verticeNorm[0] = normVecArrBall[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrBall[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrBall[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexTexNum = faceArrBall[i * 12 + 1];
		vertexNum = faceArrBall[i * 12];//First vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrBall[(vertexTexNum * 2) - 2], textVecArrBall[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrBall[i * 12 + 5];
		verticeNorm[0] = normVecArrBall[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrBall[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrBall[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexTexNum = faceArrBall[i * 12 + 4];
		vertexNum = faceArrBall[i * 12 + 3];//Second vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrBall[(vertexTexNum * 2) - 2], textVecArrBall[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrBall[i * 12 + 8];
		verticeNorm[0] = normVecArrBall[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrBall[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrBall[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexTexNum = faceArrBall[i * 12 + 7];
		vertexNum = faceArrBall[i * 12 + 6];//Third vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrBall[(vertexTexNum * 2) - 2], textVecArrBall[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrBall[i * 12 + 11];
		verticeNorm[0] = normVecArrBall[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrBall[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrBall[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexTexNum = faceArrBall[i * 12 + 10];
		vertexNum = faceArrBall[i * 12 + 9];//Fourth vertex
		vertice[0] = verticeArrBall[(vertexNum * 3) - 3];
		vertice[1] = verticeArrBall[(vertexNum * 3) - 2];
		vertice[2] = verticeArrBall[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrBall[(vertexTexNum * 2) - 2], textVecArrBall[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);
	}


	glEnd();
	glEnable(GL_TEXTURE_2D);
}

void drawFileL() {
	glBindTexture(GL_TEXTURE_2D, texName[3]);
	glEnable(GL_TEXTURE_2D);
	int i = 0;
	int vertexNum = 0;
	int vertexNormNum = 0;
	int vertexTexNum = 0;
	glBegin(GL_QUADS);
	for (i = 0; i < numOfFL; i++) {
		glColor3f(1.0, 1.0, 1.0);
		vertexNormNum = faceArrLamp[i * 12 + 2];
		verticeNorm[0] = normVecArrLamp[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrLamp[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrLamp[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexTexNum = faceArrLamp[i * 12 + 1];
		vertexNum = faceArrLamp[i * 12];//First vertex
		vertice[0] = verticeArrLamp[(vertexNum * 3) - 3];
		vertice[1] = verticeArrLamp[(vertexNum * 3) - 2];
		vertice[2] = verticeArrLamp[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrLamp[(vertexTexNum * 2) - 2], textVecArrLamp[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrLamp[i * 12 + 5];
		verticeNorm[0] = normVecArrLamp[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrLamp[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrLamp[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexTexNum = faceArrLamp[i * 12 + 4];
		vertexNum = faceArrLamp[i * 12 + 3];//Second vertex
		vertice[0] = verticeArrLamp[(vertexNum * 3) - 3];
		vertice[1] = verticeArrLamp[(vertexNum * 3) - 2];
		vertice[2] = verticeArrLamp[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrLamp[(vertexTexNum * 2) - 2], textVecArrLamp[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrLamp[i * 12 + 8];
		verticeNorm[0] = normVecArrLamp[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrLamp[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrLamp[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexTexNum = faceArrLamp[i * 12 + 7];
		vertexNum = faceArrLamp[i * 12 + 6];//Third vertex
		vertice[0] = verticeArrLamp[(vertexNum * 3) - 3];
		vertice[1] = verticeArrLamp[(vertexNum * 3) - 2];
		vertice[2] = verticeArrLamp[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrLamp[(vertexTexNum * 2) - 2], textVecArrLamp[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);

		vertexNormNum = faceArrLamp[i * 12 + 11];
		verticeNorm[0] = normVecArrLamp[(vertexNormNum * 3) - 3];
		verticeNorm[1] = normVecArrLamp[(vertexNormNum * 3) - 2];
		verticeNorm[2] = normVecArrLamp[(vertexNormNum * 3) - 1];
		verticeNorm[3] = 1;
		glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
		vertexTexNum = faceArrLamp[i * 12 + 10];
		vertexNum = faceArrLamp[i * 12 + 9];//Fourth vertex
		vertice[0] = verticeArrLamp[(vertexNum * 3) - 3];
		vertice[1] = verticeArrLamp[(vertexNum * 3) - 2];
		vertice[2] = verticeArrLamp[(vertexNum * 3) - 1];
		vertice[3] = 1;
		glTexCoord2f(textVecArrLamp[(vertexTexNum * 2) - 2], textVecArrLamp[(vertexTexNum * 2) - 1]);
		glVertex3f(vertice[0], vertice[1], vertice[2]);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawFileS() {
	int i = 0;
	int stabilize = 0;
	int vertexNum = 0;
	int vertexNormNum = 0;
	int vertexTexNum = 0;

	if (displayTextures) {
		glEnable(GL_TEXTURE_2D);
	}
	else {
		glDisable(GL_TEXTURE_2D);
	}

	//THIS VERSION DOESN'T CHANGE TEXTURES
	/*glBindTexture(GL_TEXTURE_2D, texName[1]);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < numOfFS; i++) {//Grass
	if (faceArrStadium[i * 9 + stabilize] == -999) {
	stabilize++;
	glEnd();//New section
	glBegin(GL_TRIANGLES);
	}
	if (stabilize == 6) {
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	}
	if (stabilize == 7) {
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	}
	if (stabilize == 10) {
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	}
	if (stabilize == 11){
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	}
	if (stabilize == 15){
	//DO NOTHING
	}
	else if ((stabilize == 2) || (stabilize == 4) || (stabilize == 7) || (stabilize == 9) || (stabilize == 11) || (stabilize == 12) || (stabilize == 14) || (stabilize == 16)) {
	glColor3f(1.0, 1.0, 1.0);
	vertexTexNum = faceArrStadium[i * 9 + stabilize + 1];
	glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
	vertexNum = faceArrStadium[i * 9 + stabilize];//First vertex
	vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
	vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
	vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
	vertice[3] = 1;
	glVertex3f(vertice[0], vertice[1], vertice[2]);
	vertexTexNum = faceArrStadium[i * 9 + stabilize + 3];
	glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
	vertexNum = faceArrStadium[i * 9 + stabilize + 2];//Second vertex
	vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
	vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
	vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
	vertice[3] = 1;
	glVertex3f(vertice[0], vertice[1], vertice[2]);
	vertexTexNum = faceArrStadium[i * 9 + stabilize + 5];
	glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
	vertexNum = faceArrStadium[i * 9 + stabilize + 4];//Third vertex
	vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
	vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
	vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
	vertice[3] = 1;
	glVertex3f(vertice[0], vertice[1], vertice[2]);
	}
	else {
	glColor3f(1.0, 1.0, 1.0);
	vertexNormNum = faceArrStadium[i * 9 + stabilize + 2];
	verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
	verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
	verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
	verticeNorm[3] = 1;
	glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
	vertexTexNum = faceArrStadium[i * 9 + stabilize + 1];
	glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
	vertexNum = faceArrStadium[i * 9 + stabilize];//First vertex
	vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
	vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
	vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
	vertice[3] = 1;
	glVertex3f(vertice[0], vertice[1], vertice[2]);
	vertexNormNum = faceArrStadium[i * 9 + stabilize + 5];
	verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
	verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
	verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
	verticeNorm[3] = 1;
	glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
	vertexTexNum = faceArrStadium[i * 9 + stabilize + 4];
	glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
	vertexNum = faceArrStadium[i * 9 + stabilize + 3];//Second vertex
	vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
	vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
	vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
	vertice[3] = 1;
	glVertex3f(vertice[0], vertice[1], vertice[2]);
	vertexNormNum = faceArrStadium[i * 9 + stabilize + 8];
	verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
	verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
	verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
	verticeNorm[3] = 1;
	glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
	vertexTexNum = faceArrStadium[i * 9 + stabilize + 7];
	glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
	vertexNum = faceArrStadium[i * 9 + stabilize + 6];//Third vertex
	vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
	vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
	vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
	vertice[3] = 1;
	glVertex3f(vertice[0], vertice[1], vertice[2]);
	}
	}
	glEnd();*/


	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glBegin(GL_TRIANGLES);
	i = 0;
	while (stabilize < 5) {//Brown Accent Pieces
		if (faceArrStadium[i * 9 + stabilize] == -999) {
			stabilize++;
			glEnd();//New section
			glBegin(GL_TRIANGLES);
		}
		if (stabilize == 1) {
			//glBindTexture(GL_TEXTURE_2D, texName[2]);
		}
		if (stabilize == 15) {
			//Do nothing
		}
		else if ((stabilize == 2) || (stabilize == 4) || (stabilize == 7) || (stabilize == 9) || (stabilize == 11) || (stabilize == 12) || (stabilize == 14) || (stabilize == 16)) {
			glColor3f(1.0, 1.0, 1.0);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 1];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize];//First vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexTexNum = faceArrStadium[i * 9 + stabilize + 3];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 2];//Second vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexTexNum = faceArrStadium[i * 9 + stabilize + 5];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 4];//Third vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);
		}
		else {
			glColor3f(1.0, 1.0, 1.0);
			vertexNormNum = faceArrStadium[i * 9 + stabilize + 2];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 1];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize];//First vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexNormNum = faceArrStadium[i * 9 + stabilize + 5];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 4];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 3];//Second vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexNormNum = faceArrStadium[i * 9 + stabilize + 8];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 7];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 6];//Third vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);
		}
		i++;
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_TRIANGLES);
	while (stabilize < 6) {//Stand seats
		if (faceArrStadium[i * 9 + stabilize] == -999) {
			stabilize++;
			glEnd();//New section
			glBegin(GL_TRIANGLES);
		}
		if (stabilize == 1) {
			//glBindTexture(GL_TEXTURE_2D, texName[2]);
		}
		if (stabilize == 15) {
			//Do nothing
		}
		else if ((stabilize == 2) || (stabilize == 4) || (stabilize == 7) || (stabilize == 9) || (stabilize == 11) || (stabilize == 12) || (stabilize == 14) || (stabilize == 16)) {
			glColor3f(1.0, 1.0, 1.0);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 1];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize];//First vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexTexNum = faceArrStadium[i * 9 + stabilize + 3];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 2];//Second vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexTexNum = faceArrStadium[i * 9 + stabilize + 5];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 4];//Third vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);
		}
		else {
			glColor3f(1.0, 1.0, 1.0);
			vertexNormNum = faceArrStadium[i * 9 + stabilize + 2];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 1];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize];//First vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexNormNum = faceArrStadium[i * 9 + stabilize + 5];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 4];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 3];//Second vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexNormNum = faceArrStadium[i * 9 + stabilize + 8];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 7];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 6];//Third vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);
		}
		i++;
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glBegin(GL_TRIANGLES);
	while (stabilize < 10) {//Stand seats
		if (faceArrStadium[i * 9 + stabilize] == -999) {
			stabilize++;
			glEnd();//New section
			glBegin(GL_TRIANGLES);
		}
		if (stabilize == 1) {
			//glBindTexture(GL_TEXTURE_2D, texName[2]);
		}
		if (stabilize == 15) {
			//Do nothing
		}
		else if ((stabilize == 2) || (stabilize == 4) || (stabilize == 7) || (stabilize == 9) || (stabilize == 11) || (stabilize == 12) || (stabilize == 14) || (stabilize == 16)) {
			glColor3f(1.0, 1.0, 1.0);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 1];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize];//First vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexTexNum = faceArrStadium[i * 9 + stabilize + 3];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 2];//Second vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexTexNum = faceArrStadium[i * 9 + stabilize + 5];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 4];//Third vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);
		}
		else {
			glColor3f(1.0, 1.0, 1.0);
			vertexNormNum = faceArrStadium[i * 9 + stabilize + 2];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 1];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize];//First vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexNormNum = faceArrStadium[i * 9 + stabilize + 5];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 4];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 3];//Second vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexNormNum = faceArrStadium[i * 9 + stabilize + 8];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 7];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 6];//Third vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);
		}
		i++;
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_TRIANGLES);
	while (stabilize < 11) {//Stand seats
		if (faceArrStadium[i * 9 + stabilize] == -999) {
			stabilize++;
			glEnd();//New section
			glBegin(GL_TRIANGLES);
		}
		if (stabilize == 1) {
			//glBindTexture(GL_TEXTURE_2D, texName[2]);
		}
		if (stabilize == 15) {
			//Do nothing
		}
		else if ((stabilize == 2) || (stabilize == 4) || (stabilize == 7) || (stabilize == 9) || (stabilize == 11) || (stabilize == 12) || (stabilize == 14) || (stabilize == 16)) {
			glColor3f(1.0, 1.0, 1.0);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 1];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize];//First vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexTexNum = faceArrStadium[i * 9 + stabilize + 3];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 2];//Second vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexTexNum = faceArrStadium[i * 9 + stabilize + 5];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 4];//Third vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);
		}
		else {
			glColor3f(1.0, 1.0, 1.0);
			vertexNormNum = faceArrStadium[i * 9 + stabilize + 2];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 1];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize];//First vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexNormNum = faceArrStadium[i * 9 + stabilize + 5];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 4];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 3];//Second vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexNormNum = faceArrStadium[i * 9 + stabilize + 8];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 7];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 6];//Third vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);
		}
		i++;
	}
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glBegin(GL_TRIANGLES);
	while (stabilize < 15) {//Field
		if (faceArrStadium[i * 9 + stabilize] == -999) {
			stabilize++;
			glEnd();//New section
			glBegin(GL_TRIANGLES);
		}
		/*if (stabilize == 1) {
		//glBindTexture(GL_TEXTURE_2D, texName[2]);
		}*/
		/*if (stabilize == 15) {
		printf("NTREVOU");
		//Do nothing
		}*/
		else if ((stabilize == 2) || (stabilize == 4) || (stabilize == 7) || (stabilize == 9) || (stabilize == 11) || (stabilize == 12) || (stabilize == 14) || (stabilize == 16)) {
			glColor3f(1.0, 1.0, 1.0);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 1];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize];//First vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexTexNum = faceArrStadium[i * 9 + stabilize + 3];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 2];//Second vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexTexNum = faceArrStadium[i * 9 + stabilize + 5];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 4];//Third vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);
		}
		else {
			glColor3f(1.0, 1.0, 1.0);
			vertexNormNum = faceArrStadium[i * 9 + stabilize + 2];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 1];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize];//First vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexNormNum = faceArrStadium[i * 9 + stabilize + 5];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 4];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 3];//Second vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);

			vertexNormNum = faceArrStadium[i * 9 + stabilize + 8];
			verticeNorm[0] = normVecArrStadium[(vertexNormNum * 3) - 3];
			verticeNorm[1] = normVecArrStadium[(vertexNormNum * 3) - 2];
			verticeNorm[2] = normVecArrStadium[(vertexNormNum * 3) - 1];
			verticeNorm[3] = 1;
			glNormal3f(verticeNorm[0], verticeNorm[1], verticeNorm[2]);
			vertexTexNum = faceArrStadium[i * 9 + stabilize + 7];
			glTexCoord2f(textVecArrStadium[(vertexTexNum * 2) - 2], textVecArrStadium[(vertexTexNum * 2) - 1]);
			vertexNum = faceArrStadium[i * 9 + stabilize + 6];//Third vertex
			vertice[0] = verticeArrStadium[(vertexNum * 3) - 3];
			vertice[1] = verticeArrStadium[(vertexNum * 3) - 2];
			vertice[2] = verticeArrStadium[(vertexNum * 3) - 1];
			vertice[3] = 1;
			glVertex3f(vertice[0], vertice[1], vertice[2]);
		}
		i++;
	}
	glEnd();
}

void drawTarget() {
	glBegin(GL_TRIANGLES);
	
	//Cube top
	glNormal3fv(normVecArrTarget[0]);
	glVertex3fv(verticeArrTarget[0]);
	glNormal3fv(normVecArrTarget[0]);
	glVertex3fv(verticeArrTarget[1]);
	glNormal3fv(normVecArrTarget[0]);
	glVertex3fv(verticeArrTarget[2]);

	glNormal3fv(normVecArrTarget[0]);
	glVertex3fv(verticeArrTarget[2]);
	glNormal3fv(normVecArrTarget[0]);
	glVertex3fv(verticeArrTarget[3]);
	glNormal3fv(normVecArrTarget[0]);
	glVertex3fv(verticeArrTarget[0]);

	//Cube left
	glNormal3fv(normVecArrTarget[1]);
	glVertex3fv(verticeArrTarget[2]);
	glNormal3fv(normVecArrTarget[1]);
	glVertex3fv(verticeArrTarget[3]);
	glNormal3fv(normVecArrTarget[1]);
	glVertex3fv(verticeArrTarget[4]);

	glNormal3fv(normVecArrTarget[1]);
	glVertex3fv(verticeArrTarget[4]);
	glNormal3fv(normVecArrTarget[1]);
	glVertex3fv(verticeArrTarget[5]);
	glNormal3fv(normVecArrTarget[1]);
	glVertex3fv(verticeArrTarget[2]);

	//Cube right
	glNormal3fv(normVecArrTarget[2]);
	glVertex3fv(verticeArrTarget[0]);
	glNormal3fv(normVecArrTarget[2]);
	glVertex3fv(verticeArrTarget[1]);
	glNormal3fv(normVecArrTarget[2]);
	glVertex3fv(verticeArrTarget[7]);

	glNormal3fv(normVecArrTarget[2]);
	glVertex3fv(verticeArrTarget[1]);
	glNormal3fv(normVecArrTarget[2]);
	glVertex3fv(verticeArrTarget[7]);
	glNormal3fv(normVecArrTarget[2]);
	glVertex3fv(verticeArrTarget[6]);

	//Cube front
	glNormal3fv(normVecArrTarget[3]);
	glVertex3fv(verticeArrTarget[1]);
	glNormal3fv(normVecArrTarget[3]);
	glVertex3fv(verticeArrTarget[2]);
	glNormal3fv(normVecArrTarget[3]);
	glVertex3fv(verticeArrTarget[5]);

	glNormal3fv(normVecArrTarget[3]);
	glVertex3fv(verticeArrTarget[5]);
	glNormal3fv(normVecArrTarget[3]);
	glVertex3fv(verticeArrTarget[6]);
	glNormal3fv(normVecArrTarget[3]);
	glVertex3fv(verticeArrTarget[1]);

	//Cube back
	glNormal3fv(normVecArrTarget[4]);
	glVertex3fv(verticeArrTarget[0]);
	glNormal3fv(normVecArrTarget[4]);
	glVertex3fv(verticeArrTarget[3]);
	glNormal3fv(normVecArrTarget[4]);
	glVertex3fv(verticeArrTarget[4]);

	glNormal3fv(normVecArrTarget[4]);
	glVertex3fv(verticeArrTarget[4]);
	glNormal3fv(normVecArrTarget[4]);
	glVertex3fv(verticeArrTarget[7]);
	glNormal3fv(normVecArrTarget[4]);
	glVertex3fv(verticeArrTarget[0]);

	//Triangle left
	glNormal3fv(normVecArrTarget[5]);
	glVertex3fv(verticeArrTarget[4]);
	glNormal3fv(normVecArrTarget[5]);
	glVertex3fv(verticeArrTarget[5]);
	glNormal3fv(normVecArrTarget[5]);
	glVertex3fv(verticeArrTarget[8]);
	//Triangle right
	glNormal3fv(normVecArrTarget[6]);
	glVertex3fv(verticeArrTarget[6]);
	glNormal3fv(normVecArrTarget[6]);
	glVertex3fv(verticeArrTarget[7]);
	glNormal3fv(normVecArrTarget[6]);
	glVertex3fv(verticeArrTarget[8]);
	//Triangle front
	glNormal3fv(normVecArrTarget[7]);
	glVertex3fv(verticeArrTarget[5]);
	glNormal3fv(normVecArrTarget[7]);
	glVertex3fv(verticeArrTarget[6]);
	glNormal3fv(normVecArrTarget[7]);
	glVertex3fv(verticeArrTarget[8]);
	//Triangle back
	glNormal3fv(normVecArrTarget[8]);
	glVertex3fv(verticeArrTarget[4]);
	glNormal3fv(normVecArrTarget[8]);
	glVertex3fv(verticeArrTarget[7]);
	glNormal3fv(normVecArrTarget[8]);
	glVertex3fv(verticeArrTarget[8]);

	glEnd();
}

//Calculate object's bottom center
float* getObjectParameters(int vertexCount, float* vertices) {

	float* bottomCenter = (float*)calloc(3, sizeof(float));

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