#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#define _CRT_SECURE_NO_WARNINGS
#include <freeglut.h>
#include <Windows.h>
#include <stdio.h>

extern FILE *fp;
extern char fileName[50]; //Holds the  file name

extern float worldLeft, worldRight, worldBottom,
worldTop, worldNear, worldFar; //Coordinates of the viewing volume

extern int numOfLines; //Number of lines in the input file
extern int numOfData; //Number of data in file
extern int numOfV; //Number of vertices in file
extern int numOfVN;//Number of normal vectors in the file
extern int numOfFG;//Number of faces in goal file
extern int numOfFB;//Number of faces in ball file
extern int numOfFS;//Number of faces in stadium file

extern int * arrayPtr; //Pointer to dynamically allotted array
extern double *vertice;//Holds current x, y, z, and w values to be drawn

extern int xRot;//Holds number of degrees to rotate around x axis
extern int yRot;//Holds number of degrees to rotate around y axis
extern int zRot;//Holds number of degrees to rotate around z axis

extern int xMove;//Holds amount to move along x axis
extern int yMove;//Holds amount to move along y axis
extern int zMove;//Holds amount to move along z axis

extern double scaleAmount; //Holds amount to scale by

extern double previousMouseX, previousMouseY; //Holds the original x and y values when mouse is depressed
extern int mode; //Defines mode for mouse motion. Holds 0 for drag and drop mode and 1 for rotate mode

				 //Data for goal object
extern double *verticeArrGoal;
extern double *normVecArrGoal;
extern int *faceArrGoal;

//Data for ball object
extern double *verticeArrBall;
extern double *normVecArrBall;
extern int *faceArrBall;

//Data for stadium object
extern double *verticeArrStadium;
extern double *normVecArrStadium;
extern int *faceArrStadium;

extern int currObj; //Object file being read, 0 = ball, 1 = goal




#endif