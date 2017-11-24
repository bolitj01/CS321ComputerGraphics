#include "DrawModels.h"
#include "GlobalVariables.h"
#include "CallbackFunctions.h"
#include "Initialization.h"
#include "TextureMapping.h"

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
int numOfVT;
int numOfFG;//Number of faces in goal file
int numOfFB;//Number of faces in ball file
int numOfFL;//Number of faces in lamp file
int numOfFS;//Number of faces in stadium file
int numOfMat;
int * arrayPtr; //Pointer to dynamically allotted array
float *vertice = (float *)calloc(4, sizeof(float));//Holds current x, y, z, and w values to be drawn
float *verticeNorm = (float *)calloc(4, sizeof(float));//Holds current x, y, z, and w normal values to be drawn
int xRot = 0;//Holds number of degrees to rotate around x axis
int yRot = 0;//Holds number of degrees to rotate around y axis
int zRot = 15;//Holds number of degrees to rotate around z axis
int xMove = 0;//Holds amount to move along x axis
int yMove = 0;//Holds amount to move along y axis
int zMove = 0;//Holds amount to move along z axis
float scaleAmount = 3.0;//Holds amount to scale by
float previousMouseX, previousMouseY;//Holds the original x and y values when mouse is depressed
int mode = 0;//Defines mode for mouse motion. Holds 0 for drag and drop mode and 1 for rotate mode
float *verticeArrGoal;
float *normVecArrGoal;
int *faceArrGoal;
float *verticeArrBall;
float *normVecArrBall;
float *textVecArrBall;
int *faceArrBall;
float *verticeArrLamp;
float *normVecArrLamp;
float *textVecArrLamp;
int *faceArrLamp;
float *verticeArrStadium;
float *normVecArrStadium;
float *textVecArrStadium;
char *matArrStadium;
int *faceArrStadium;
int currObj = 0; //Object file being read, 0 = ball, 1 = goal
float worldLeft, worldRight, worldBottom,
worldTop, worldNear, worldFar;
//Lighting
GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat emissiveLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
//Field Ligth 1
GLfloat diffuseLight1[] = { 1.0, .2, .6, 1.0 };
extern GLfloat lightPosition1[] = { 100, 0, 0, 1 };
extern GLfloat spotDirection1[] = {0, 0, 0};
//Texture Mapping
int ImgWidth, ImgHeight;
typedef GLubyte Pixel[3];
Pixel *Image;
char *materialType;
GLuint texName[5];

void setup() {
	//Reads data for models into arrays 
	fp = fopen("soccer ball2.obj", "r");
	countLines();
	createBallData();
	currObj = 1;

	fp = fopen("soccergoal.obj", "r");
	countLines();
	createGoalData();
	currObj = 2;

	fp = fopen("stadium2.obj", "r");
	countLines();
	createArrayS();
	currObj = 3;

	fp = fopen("lamp2.obj", "r");
	countLines();
	createLampData();
	printf("REACHED");
}

void main(int argc, char** argv)
{
	setup();
	initWindow(argc, argv);
	setupLight();
	bindTextures();
	//printf("HELLO");
	initializeViewingVolume();
	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseCameraRotation);
	glutKeyboardFunc(keyPress);
	glutMainLoop();

}