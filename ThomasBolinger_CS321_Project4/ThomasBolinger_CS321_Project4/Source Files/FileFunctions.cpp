#include "../Header Files/FileFunctions.h"
/*
	Thomas Bolinger
	CS321 Project 1
	All the functions utilizing the data files
*/



//Prompt for file name from standard input
char* promptForFile() {
	//Read user input file name
	printf("Please enter a file name: ");
	char* input = (char*)calloc(256, sizeof(char));
	fgets(input, 256, stdin);

	char* fileName = (char*)calloc(256, sizeof(char));
	strcpy_s(fileName, 256, "Data Files/");
	strcat_s(fileName, 256, input);

	char* nextToken = NULL;
	fileName = strtok_s(fileName, "\n", &nextToken);

	return fileName;
}

//Open file at beginning
void openFile(char* fileName, FILE** fp) {
	// Attempt to open file, exit program if unsuccessful 
	int err = fopen_s(fp, fileName, "r");
	if (err != 0) {
		fprintf(stderr, "File not found.");
		Sleep(2);
		exit(-1);
	}
}

//Count and return the number of vertices and groups of vertices(shapes) in the file for pre-reading memory allocation.
//Assumes file pointer is pointing to a text file at the beginning of the file.
void countVerticesInFile(FILE* fp, int* vertexCount, int* vertexGroups) {
	int lineLength = 256;
	char* line = (char*)calloc(lineLength, sizeof(char));
	bool passedVertices = false;

	//Loop through each line in the text file. If the line doesn't start with J or j,
	//increment vertex counter. Otherwise check if a vertex group has been passed.
	while (fgets(line, lineLength, fp) != NULL) {
		if (!(line[0] == 'J' || line[0] == 'j')) {
			(*vertexCount)++;
			passedVertices = true;
		}
		else if (passedVertices) {
			(*vertexGroups)++;
		}
	}

	//Account for last group of vertices (some files end in J, some do not)
	if (passedVertices) {
		(*vertexGroups)++;
	}

	if (line != NULL) {
		free(line);
	}
	if (fp != NULL) {
		fclose(fp);
	}
}

//Establish pointers for vertex groups and all vertices, read vertex data from file and place into
//pointer arrays
void readData(FILE* fp, int vertexCount, int vertexGroups, int** verticesPerGroup, vertex3** vertices) {
	int* verticesPerGroup1 = (int*)calloc(vertexGroups, sizeof(int));
	vertex3* vertices1 = (vertex3*)calloc(vertexCount, sizeof(vertex3));

	int vertexIndex = 0;
	int groupIndex = 0;
	int groupCount = 0; //Counter for vertices in current group

	int lineLength = 256;
	char* line = (char*)calloc(lineLength, sizeof(char));

	bool startedVertexGroup = false;

	char* nextToken = NULL;

	//Loop through each line in the text file, read vertices and track how many vertices are in each group
	while (fgets(line, lineLength, fp) != NULL) {
		if (!(line[0] == 'J' || line[0] == 'j')) {
			//Tokenize the line one number at a time by whitespace and store data into vertex
			char* token = strtok_s(line, " ", &nextToken);
			vertices1[vertexIndex][0] = atof(token); //Place x value into vertex
			token = strtok_s(NULL, " ", &nextToken);
			vertices1[vertexIndex][1] = atof(token); //Place y value into vertex
			token = strtok_s(NULL, " ", &nextToken);
			vertices1[vertexIndex][2] = atof(token); //Place z value into vertex
			vertexIndex++;

			groupCount++;
			startedVertexGroup = true;

		}
		else if (startedVertexGroup) {
			//Reached end of group, store group information and reset counter
			startedVertexGroup = false;
			verticesPerGroup1[groupIndex] = groupCount; //Put groupCount in the array
			groupIndex++;
			groupCount = 0;
		}

	}

	//Account for last group(some files end in J, some do not)
	if (startedVertexGroup) {
		verticesPerGroup1[groupIndex] = groupCount;
	}

	//Free memory
	if (line != NULL) {
		free(line);
	}
	if (fp != NULL) {
		fclose(fp);
	}

	//Assign data to outside pointers
	*verticesPerGroup = verticesPerGroup1;
	*vertices = vertices1;
}

//Print vertex data in reverse
void printDataReverseToFile(char* fileName, vertex3* vertices, int vertexCount) {

	//Append .out to fileName
	int fileNameLength = 0;
	while (fileName[fileNameLength] != '\0') {
		fileNameLength++;
	}
	fileName = (char*)realloc(fileName, sizeof(char) * fileNameLength + 4);
	strcat_s(fileName, fileNameLength + 4, ".out");

	//Open data file
	FILE* fp = NULL;
	int err = fopen_s(&fp, fileName, "w");
	if (err != 0) {
		printf("Could not open file: %s", fileName);
	}

	//Loop through vertices backwards and print each coordinate
	float averageX = 0, averageY = 0, averageZ = 0;
	for (int i = vertexCount - 1; i >= 0; i--) {
		float x = vertices[i][0];
		float y = vertices[i][1];
		float z = vertices[i][2];

		fprintf(fp, "%7.1f %7.1f %7.1f\n", x, y, z);

		averageX += x;
		averageY += y;
		averageZ += z;
	}

	//Print averages
	averageX = averageX / vertexCount;
	fprintf(fp, "Mean X-Coordinate = %7.1f\n", averageX);
	averageY = averageY / vertexCount;
	fprintf(fp, "Mean Y-Coordinate = %7.1f\n", averageY);
	averageZ = averageZ / vertexCount;
	fprintf(fp, "Mean Z-Coordinate = %7.1f\n", averageZ);

	//Free memory
	if (fp != NULL) {
		fclose(fp);
	}
}

//Only for testing vertex data by printing to console
void printVertices(int vertexGroups, int* verticesPerGroup, vertex3* vertices) {
	int index = 0;
	for (int x = 0; x < vertexGroups; x++) {
		int group = verticesPerGroup[x];
		fprintf(stdout, "Vertex group #%d: %d vertices\n", x, group);
		for (int y = 0; y < verticesPerGroup[x]; y++) {
			int p1 = vertices[index][0];
			int p2 = vertices[index][1];
			int p3 = vertices[index][2];
			printf("Vertex: %d %d %d\n", p1, p2, p3);
			index++;
		}
	}
}