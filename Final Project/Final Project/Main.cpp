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


FILE *fp;
char fileName[50]; //Holds the file name

float worldLeft, worldRight, worldBottom,
worldTop, worldNear, worldFar;

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

double *verticeArrBall;
double *normVecArrBall;
int *faceArrBall;
double* ballBottomCenter;
float ballRadius;

double *verticeArrStadium;
double *normVecArrStadium;
int *faceArrStadium;

int currObj = 0; //Object file being read, 0 = ball, 1 = goal

void setup() {
	//Reads data for models into arrays 
	fp = fopen("soccerball.obj", "r");
	countLines();
	createBallData();
	ballBottomCenter = getObjectBottomCenter(numOfV, verticeArrBall);
	currObj = 1;

	fp = fopen("soccergoal.obj", "r");
	countLines();
	createGoalData();
	goalBottomCenter = getObjectBottomCenter(numOfV, verticeArrGoal);
	currObj = 2;

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
	initializeBallGoal();
}

void main(int argc, char** argv)
{
	setup();

	initWindow(argc, argv);

	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseCameraRotation);
	glutKeyboardFunc(keyPress);
	glutMainLoop();


	//Free allocated memory

}