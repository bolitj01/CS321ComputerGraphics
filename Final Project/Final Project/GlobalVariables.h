#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#define _CRT_SECURE_NO_WARNINGS
#include <freeglut.h>
#include <Windows.h>
#include <stdio.h>
#include <btBulletDynamicsCommon.h>

extern float screenWidth, screenHeight;

extern FILE *fp;
extern char fileName[50]; //Holds the  file name

extern float worldLeft, worldRight, worldBottom,
worldTop, worldNear, worldFar; //Coordinates of the viewing volume

extern btDiscreteDynamicsWorld* dynamicsWorld;
extern btRigidBody* ballRigidBody;
extern btRigidBody* targetRigidBody;
extern btTransform ballTransformation;
extern btTransform targetTransformation;
extern float worldScaleToBullet;
extern btVector3 goalMesh[8];

extern int numOfLines; //Number of lines in the input file
extern int numOfData; //Number of data in file
extern int numOfV; //Number of vertices in file
extern int numOfVN; //Number of normal vectors in the file
extern int numOfVT;//Number of texture vectors in the file
extern int numOfFG; //Number of faces in goal file
extern int numOfFB; //Number of faces in ball file
extern int numOfFL;//Number of faces in lamp file
extern int numOfFS; //Number of faces in stadium file
extern int numOfMat; //Number of materials
extern int numOfS;

extern int* arrayPtr; //Pointer to dynamically allotted array
extern float *vertice;//Holds current x, y, z, and w values to be drawn
extern float *verticeNorm;//Holds current x, y, z, and w normal values to be drawn

extern float yGoalRot; //Holds number of degrees to rotate around y axis

extern float xCameraRot; //Degrees to rotate camera on x axis
extern float yCameraRot; //Degrees to rotate camera on y axis
extern float* cameraLocation; //Vector for camera location
extern float* cameraAtVertex; //At vector for camera's direction of looking
extern float* cameraUpVector; //Up vector for camera orthogonal to look vector

extern float previousMouseX, previousMouseY; //Holds the original x and y values when mouse is depressed

//Data for goal object
extern float *verticeArrGoal;
extern float *normVecArrGoal;
extern int *faceArrGoal;
extern float goalZLocation;
extern float* goalBottomCenter;
extern float goalWidth;
extern float goalHeight;
extern float goalDepth;
extern float goalScale;

//Data for ball object
extern float *verticeArrBall;
extern float *normVecArrBall;
extern float *textVecArrBall;
extern int *faceArrBall;
extern int *sArrBall;
extern float* ballBottomCenter;
extern float ballRadius;
extern float ballStartingHeightOffGround;
extern btVector3 ballVelocity;
extern float ballKickUpAngle;
extern float ballKickTurnAngle;
extern float ballRotationY;
extern float ballRotationX;

//Data for lamp object
extern float *verticeArrLamp;
extern float *normVecArrLamp;
extern float *textVecArrLamp;
extern int *faceArrLamp;

//Data for stadium object
extern float *verticeArrStadium;
extern float *normVecArrStadium;
extern float *textVecArrStadium;
extern char *matArrStadium;
extern int *faceArrStadium;
extern float* stadiumBottomCenter;
extern bool drawStadium;

//Data for target object
extern float **verticeArrTarget;
extern float **normVecArrTarget;
extern float targetScale;
extern btVector3 targetLocation;
extern int targetRotation;

//Lighting
extern GLfloat ambientLight[4];
extern GLfloat diffuseLight[4];
extern GLfloat emissiveLight[4];
extern GLfloat specularLight[4];
extern GLfloat ambientMaterial[4];
extern GLfloat diffuseMaterial[4];
//Field Light 1
extern GLfloat lamp1DiffuseLight[4];
extern GLfloat lamp1LightPosition[4];
extern GLfloat lamp1SpotDirection[3];
extern GLfloat lamp1Cutoff;
extern GLint lamp1Exponent;
extern bool light1Enabled;
//Field Light 2
extern GLfloat lamp2DiffuseLight[4];
extern GLfloat lamp2LightPosition[4];
extern GLfloat lamp2SpotDirection[3];
extern GLfloat lamp2Cutoff;
extern GLint lamp2Exponent;
extern bool light2Enabled;

//Texture Mapping
extern int ImgWidth, ImgHeight;
typedef GLubyte Pixel[3];
extern Pixel *Image;
extern char *materialType;
extern GLuint texName[5];

extern int currObj; //Object file being read, 0 = ball, 1 = goal

extern float kickLineStartX, kickLineStartY, kickLineEndX, kickLineEndY;
extern float kickStrengthY, kickStrengthX;
extern bool ballKicked;

extern float pi;




#endif