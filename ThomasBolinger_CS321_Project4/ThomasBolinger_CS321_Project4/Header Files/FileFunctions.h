#ifndef FILEFUNCTIONS_H
#define FILEFUNCTIONS_H

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>

#include "VertexFunctions.h"

//Functions utilizing data files. Function descriptions are in the .cpp file

char* promptForFile();
void openFile(char* fileName, FILE** fp);
void countVerticesInFile(FILE* fp, int* vertexCount, int* vertexGroups);
void readData(FILE* fp, int vertexCount, int vertexGroups, int** verticesPerGroup, vertex3** vertices);
void printDataReverseToFile(char* fileName, vertex3* vertices, int vertexCount);
void printVertices(int vertexGroups, int* verticesPerGroup, vertex3* vertices);


#endif