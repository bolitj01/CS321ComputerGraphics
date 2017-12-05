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
int numOfVN; //Number of normal vectors in the file
int numOfVT;//Number of texture vectors in the file
int numOfFG; //Number of faces in goal file
int numOfFB; //Number of faces in ball file
int numOfFL;//Number of faces in lamp file
int numOfFS; //Number of faces in stadium file
int numOfMat; //Number of materials
int numOfS;

int* arrayPtr; //Pointer to dynamically allotted array
float* vertice; //Holds current x, y, z, and w values to be drawn
float *verticeNorm;//Holds current x, y, z, and w normal values to be drawn

float yGoalRot; //Holds number of degrees to rotate around y axis

float xCameraRot = 0; //Degrees to rotate camera around y axis
float yCameraRot = 0; //Degrees to rotate camera around x axis
float* cameraLocation;
float* cameraAtVertex;
float* cameraUpVector;

float previousMouseX, previousMouseY;//Holds the original x and y values when mouse is depressed

//Goal data and parameters
float *verticeArrGoal;
float *normVecArrGoal;
int *faceArrGoal;
float goalZLocation;
float* goalBottomCenter;
float goalWidth;
float goalHeight;
float goalDepth;
float goalScale;

//Ball data and parameters
float *verticeArrBall;
float *normVecArrBall;
float *textVecArrBall;
int *faceArrBall;
int *sArrBall;

float* ballBottomCenter;
float ballRadius;
float ballStartingHeightOffGround;
btVector3 ballVelocity;
float ballKickUpAngle;
float ballKickTurnAngle;
float ballRotationY;
float ballRotationX;

//Data and parameters for lamp object
float *verticeArrLamp;
float *normVecArrLamp;
float *textVecArrLamp;
int *faceArrLamp;

//Stadium data and parameters
float *verticeArrStadium;
float *normVecArrStadium;
float *textVecArrStadium;
char *matArrStadium;
int *faceArrStadium;
float* stadiumBottomCenter;
bool drawStadium = true;

//Target data and parameters
float **verticeArrTarget;
float **normVecArrTarget;
float targetScale;
btVector3 targetLocation;
int targetRotation;

//Lighting
GLfloat ambientLight[4];
GLfloat diffuseLight[4];
GLfloat emissiveLight[4];
GLfloat specularLight[4];
GLfloat ambientMaterial[4];
GLfloat diffuseMaterial[4];
GLfloat emissiveMaterial[4];
GLfloat specularMaterial[4];
GLfloat shininess;
//Outside positonal diffuse light
GLfloat outsideDiffuseLight[4];
GLfloat outsideLightPosition[4];
GLfloat outsideSpotDirection[3];
GLfloat outsideCutoff;
GLint outsideExponent;
//Field Light 1
GLfloat lamp1DiffuseLight[4];
GLfloat lamp1LightPosition[4];
GLfloat lamp1SpotDirection[3];
bool lamp1Enabled;
//Field Light 2
GLfloat lamp2DiffuseLight[4];
GLfloat lamp2LightPosition[4];
GLfloat lamp2SpotDirection[3];
bool lamp2Enabled;

GLfloat lampExponent;
GLfloat lampCutoff;

//Texture Mapping
int ImgWidth, ImgHeight;
typedef GLubyte Pixel[3];
Pixel *Image;
char *materialType;
GLuint texName[5];

bool displayTextures = true;

int currObj = 0; //Object file being read, 0 = ball, 1 = goal, 2 = stadium

float kickLineStartX, kickLineStartY, kickLineEndX, kickLineEndY;
float kickStrengthY, kickStrengthX;
bool ballKicked = false;

float pi = atan(1.0) * 4;

void setup() {
	//Reads data for models into arrays 

	printf("Reading ball\n");
	currObj = 0;
	fp = fopen("testcolorball.obj", "r");
	countLines();
	createBallData();
	ballBottomCenter = getObjectParameters(numOfV, verticeArrBall);
	
	printf("Reading goal\n");
	currObj = 1;
	fp = fopen("soccergoal.obj", "r");
	countLines();
	createGoalData();
	goalBottomCenter = getObjectParameters(numOfV, verticeArrGoal);

	/*printf("Reading stadium\n");
	currObj = 2;
	fp = fopen("stadium2.obj", "r");
	countLines();
	createStadiumData();
	stadiumBottomCenter = getObjectParameters(numOfV, verticeArrStadium);

	currObj = 3;
	printf("Reading lamp\n");
	fp = fopen("lamp2.obj", "r");
	countLines();
	createLampData();*/

	createTargetData();

	//Allocate memory
	vertice = (float *)calloc(4, sizeof(float));
	verticeNorm = (float *)calloc(4, sizeof(float));

	cameraLocation = (float*)calloc(3, sizeof(float));
	cameraAtVertex = (float*)calloc(3, sizeof(float));
	cameraUpVector = (float*)calloc(3, sizeof(float));

	initializeViewingVolume();
	initializeCamera();
	initializePhysicsWorld();
	initializeLight();
	//bindTextures();
}

void main(int argc, char** argv)
{
	initWindow(argc, argv);

	setup();

	glutDisplayFunc(display);
	glutIdleFunc(idleWorldStep);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseCameraRotation);
	glutKeyboardFunc(keyPress);
	glutSpecialFunc(specialKeyPress);
	glutMainLoop();


	//Free allocated memory

}