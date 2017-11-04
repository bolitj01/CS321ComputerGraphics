#pragma once
#ifndef GL_INITIALIZATION
#define _CRT_SECURE_NO_WARNINGS
#include <freeglut.h>
#include <stdio.h>

FILE *fp;
char fileName[50]; //Holds the  file name
int numOfLines; //Number of lines in the input file
int numOfData; //Number of data in file
int numOfV; //Number of vertices in file
int numOfVN;//Number of normal vectors in the file
int numOfFG;//Number of faces in goal file
int numOfFB;//Number of faces in ball file
int * arrayPtr; //Pointer to dynamically allotted array
double *vertice = (double *)calloc(4, sizeof(double));//Holds current x, y, z, and w values to be drawn
int xRot = 15;//Holds number of degrees to rotate around x axis
int yRot = 135;//Holds number of degrees to rotate around y axis
int zRot = 0;//Holds number of degrees to rotate around z axis
int xMove = 0;//Holds amount to move along x axis
int yMove = 0;//Holds amount to move along y axis
int zMove = 0;//Holds amount to move along z axis
double scaleAmount = 1.0;//Holds amount to scale by
double origX, origY;//Holds the original x and y values when mouse is depressed
int mode = 0;//Defines mode for mouse motion. Holds 0 for drag and drop mode and 1 for rotate mode
double *verticeArrG;
double *normVecArrG;
int *faceArrG;
double *verticeArrB;
double *normVecArrB;
int *faceArrB;
int currObj = 0; //Object file being read, 0 = ball, 1 = goal




#endif
