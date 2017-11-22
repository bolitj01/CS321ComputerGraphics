#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#define _CRT_SECURE_NO_WARNINGS
#include <freeglut.h>
#include <Windows.h>
#include <stdio.h>
#include <btBulletDynamicsCommon.h>

extern FILE *fp;
extern char fileName[50]; //Holds the  file name

extern float worldLeft, worldRight, worldBottom,
worldTop, worldNear, worldFar; //Coordinates of the viewing volume

btDiscreteDynamicsWorld* dynamicsWorld;
btRigidBody* ballRigidBody;
btTransform ballTransformation;

extern int numOfLines; //Number of lines in the input file
extern int numOfData; //Number of data in file
extern int numOfV; //Number of vertices in file
extern int numOfVN; //Number of normal vectors in the file
extern int numOfFG; //Number of faces in goal file
extern int numOfFB; //Number of faces in ball file
extern int numOfFS; //Number of faces in stadium file

extern int* arrayPtr; //Pointer to dynamically allotted array
extern double *vertex; //Holds current x, y, z, and w values to be drawn

extern float yGoalRot; //Holds number of degrees to rotate around y axis

extern float cameraZLocation;
extern float xCameraRot; //Degrees to rotate camera on x axis
extern float yCameraRot; //Degrees to rotate camera on y axis
extern float* cameraLocation; //Vector for camera location
extern float* cameraAtVertex; //At vector for camera's direction of looking
extern float* cameraUpVector; //Up vector for camera orthogonal to look vector

extern double previousMouseX, previousMouseY; //Holds the original x and y values when mouse is depressed

//Data for goal object
extern double *verticeArrGoal;
extern double *normVecArrGoal;
extern int *faceArrGoal;
extern double goalZLocation;
extern double* goalBottomCenter;

//Data for ball object
extern double *verticeArrBall;
extern double *normVecArrBall;
extern int *faceArrBall;
extern double* ballBottomCenter;
extern float ballRadius;

//Data for stadium object
extern double *verticeArrStadium;
extern double *normVecArrStadium;
extern int *faceArrStadium;

extern int currObj; //Object file being read, 0 = ball, 1 = goal




#endif