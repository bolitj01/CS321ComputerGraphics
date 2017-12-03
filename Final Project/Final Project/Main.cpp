#include "DrawModels.h"
#include "GlobalVariables.h"
#include "CallbackFunctions.h"
#include "Initialization.h"

/*
Thomas Bolinger
Kimberley Grobien
Soccer game final project for CS321 Intro to Computer Graphics
Fall 2017
*/

float screenWidth, screenHeight;

FILE *fp;
char fileName[50]; //Holds the file name

float worldLeft, worldRight, worldBottom,
worldTop, worldNear, worldFar;

btDiscreteDynamicsWorld* dynamicsWorld;
btRigidBody* ballRigidBody;
btRigidBody* targetRigidBody;
btTransform ballTransformation;
btTransform targetTransformation;
float worldScaleToBullet;
btVector3 goalMesh[8];

int numOfLines; //Number of lines in the input file
int numOfData; //Number of data in file
int numOfV; //Number of vertices in file
int numOfVN;//Number of normal vectors in the file
int numOfFG;//Number of faces in goal file
int numOfFB;//Number of faces in ball file
int numOfFS;//Number of faces in stadium file
int* arrayPtr; //Pointer to dynamically allotted array
double* vertex; //Holds current x, y, z, and w values to be drawn

float yGoalRot = -90; //Holds number of degrees to rotate around y axis

float xCameraRot = 0; //Degrees to rotate camera around y axis
float yCameraRot = 0; //Degrees to rotate camera around x axis
float* cameraLocation;
float* cameraAtVertex;
float* cameraUpVector;

double previousMouseX, previousMouseY;//Holds the original x and y values when mouse is depressed

double *verticeArrGoal;
double *normVecArrGoal;
int *faceArrGoal;
double goalZLocation;
double* goalBottomCenter;
float goalWidth;
float goalHeight;
float goalDepth;
float goalScale;

double *verticeArrBall;
double *normVecArrBall;
int *faceArrBall;
double* ballBottomCenter;
float ballRadius;
float ballStartingHeightOffGround;
btVector3 ballVelocity;
float ballKickUpAngle;
float ballKickTurnAngle;
float ballRotation;

double *verticeArrStadium;
double *normVecArrStadium;
int *faceArrStadium;

float **verticeArrTarget;
float **normVecArrTarget;
float targetScale;
btVector3 targetLocation;
int targetRotation = 0;

int currObj = 0; //Object file being read, 0 = ball, 1 = goal

float kickLineStartX, kickLineStartY, kickLineEndX, kickLineEndY;
float kickStrengthY, kickStrengthX;
bool ballKicked = false;

float pi = atan(1.0) * 4;

void setup() {
	//Reads data for models into arrays 
	fp = fopen("soccerball.obj", "r");
	countLines();
	createBallData();
	ballBottomCenter = getObjectParameters(numOfV, verticeArrBall);
	currObj = 1;

	fp = fopen("soccergoal.obj", "r");
	countLines();
	createGoalData();
	goalBottomCenter = getObjectParameters(numOfV, verticeArrGoal);
	currObj = 2;

	createTargetData();

	/*fp = fopen("stadium.obj", "r");
	countLines();
	createArrayS();*/

	//Allocate memory
	vertex = (double *)calloc(4, sizeof(double));

	cameraLocation = (float*)calloc(3, sizeof(float));
	cameraAtVertex = (float*)calloc(3, sizeof(float));
	cameraUpVector = (float*)calloc(3, sizeof(float));

	initializeViewingVolume();
	initializeCamera();
	initializePhysicsWorld();
}

void main(int argc, char** argv)
{
	setup();

	initWindow(argc, argv);

	glutDisplayFunc(display);
	glutIdleFunc(idleWorldStep);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseCameraRotation);
	glutKeyboardFunc(keyPress);
	glutSpecialFunc(specialKeyPress);
	glutMainLoop();


	//Free allocated memory

}