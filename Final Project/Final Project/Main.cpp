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
int numOfLines; //Number of lines in the input file
int numOfData; //Number of data in file
int numOfV; //Number of vertices in file
int numOfVN;//Number of normal vectors in the file
int numOfFG;//Number of faces in goal file
int numOfFB;//Number of faces in ball file
int numOfFS;//Number of faces in stadium file
int * arrayPtr; //Pointer to dynamically allotted array
double *vertice = (double *)calloc(4, sizeof(double));//Holds current x, y, z, and w values to be drawn
int xRot = 0;//Holds number of degrees to rotate around x axis
int yRot = 0;//Holds number of degrees to rotate around y axis
int zRot = 15;//Holds number of degrees to rotate around z axis
int xMove = 0;//Holds amount to move along x axis
int yMove = 0;//Holds amount to move along y axis
int zMove = 0;//Holds amount to move along z axis
double scaleAmount = 3.0;//Holds amount to scale by
double previousMouseX, previousMouseY;//Holds the original x and y values when mouse is depressed
int mode = 0;//Defines mode for mouse motion. Holds 0 for drag and drop mode and 1 for rotate mode
double *verticeArrGoal;
double *normVecArrGoal;
int *faceArrGoal;
double *verticeArrBall;
double *normVecArrBall;
int *faceArrBall;
double *verticeArrStadium;
double *normVecArrStadium;
int *faceArrStadium;
int currObj = 0; //Object file being read, 0 = ball, 1 = goal
float worldLeft, worldRight, worldBottom,
worldTop, worldNear, worldFar;

void setup() {
	//Reads data for models into arrays 
	fp = fopen("soccerball.obj", "r");
	countLines();
	createBallData();
	currObj = 1;

	fp = fopen("soccergoal.obj", "r");
	countLines();
	createGoalData();
	currObj = 2;

	/*fp = fopen("stadium.obj", "r");
	countLines();
	createArrayS();*/
}

void main(int argc, char** argv)
{
	setup();
	initWindow(argc, argv);

	initializeViewingVolume();

	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseCameraRotation);
	glutKeyboardFunc(keyPress);
	glutMainLoop();

}