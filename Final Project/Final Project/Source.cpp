#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include <math.h>
#include <../Final Project/Final Project/Final Project/DrawModels.h>
#include <../Final Project/Final Project/Final Project/Interaction.h>
#include <../Final Project/Final Project/Final Project/GlobalVariables.h>
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
	glFrustum(-200, 200, -200, 200, 200, 1000);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 800, 0, 0, 0, 0, 1, 0);
	glRotatef(xRot, 1.0, 0.0, 0.0);
	glRotatef(yRot, 0.0, 1.0, 0.0);
	glRotatef(zRot, 0.0, 0.0, 1.0);
	glScalef(scaleAmount, scaleAmount, scaleAmount);
	glTranslatef(xMove, yMove, zMove);
	drawFileB();
	drawFileG();
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
