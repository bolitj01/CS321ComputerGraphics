#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include "DrawModels.h"
#include "GlobalVariables.h"
#include "Interaction.h"

FILE *fp;
char fileName[50]; //Holds the  file name
int numOfLines; //Number of lines in the input file
int numOfData; //Number of data in file
int numOfV; //Number of vertices in file
int numOfVN;//Number of normal vectors in the file
int numOfFG;//Number of faces in goal file
int numOfFB;//Number of faces in ball file
int numOfFS;//Number of faces in stadium file
int * arrayPtr; //Pointer to dynamically allotted array
double *vertice = (double *)calloc(4, sizeof(double));//Holds current x, y, z, and w values to be drawn
double *verticeNorm = (double *)calloc(4, sizeof(double));//Holds current x, y, z, and w values to be drawn
int xRot = 0;//Holds number of degrees to rotate around x axis
int yRot = 0;//Holds number of degrees to rotate around y axis
int zRot = 15;//Holds number of degrees to rotate around z axis
int xMove = 0;//Holds amount to move along x axis
int yMove = 0;//Holds amount to move along y axis
int zMove = 0;//Holds amount to move along z axis
double scaleAmount = 3.0;//Holds amount to scale by
double origX, origY;//Holds the original x and y values when mouse is depressed
int mode = 0;//Defines mode for mouse motion. Holds 0 for drag and drop mode and 1 for rotate mode
double *verticeArrG;
double *normVecArrG;
int *faceArrG;
double *verticeArrB;
double *normVecArrB;
int *faceArrB;
double *verticeArrS;
double *normVecArrS;
int *faceArrS;
int currObj = 0; //Object file being read, 0 = ball, 1 = goal

void initWindow(int &argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Problem #1");
}

void display(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-400, 400, -400, 400, -400, 400);
	glFrustum(-350, 350, -400, 400, 400, 2000);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-400, 000, 000, 0, 0, 0, 0, 1, 0);
	glRotatef(xRot, 1.0, 0.0, 0.0);
	glRotatef(yRot, 0.0, 1.0, 0.0);
	glRotatef(zRot, 0.0, 0.0, 1.0);
	glScalef(scaleAmount, scaleAmount, scaleAmount);
	glTranslatef(xMove, yMove, zMove);

	drawFileB();
	glPushMatrix();
	//glTranslatef(300, 0, 200);
	drawFileG();
	glPopMatrix();
	//drawFileS()

	glFlush();
}

void setup() {
	//Reads data for models into arrays 
	fp = fopen("soccerball.obj", "r");
	countLines();
	createArrayB();
	currObj = 1;
	
	fp = fopen("soccergoal.obj", "r");
	countLines();
	createArrayG();
	currObj = 2;

/*	fp = fopen("stadium.obj", "r");
	countLines();
	createArrayS();*/
}

void main(int argc, char** argv)
{
		setup();
		initWindow(argc, argv);
		glutDisplayFunc(display);
		glutMouseFunc(mouse);
		glutMotionFunc(mouseMotion);
		glutKeyboardFunc(keyPress);
		glutMainLoop();

}
