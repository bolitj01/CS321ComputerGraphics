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
#include <../Final Project/Final Project/Final Project/GlobalVariables.h>
#include <../Final Project/Final Project/Final Project/DrawModels.h>
#include <../Final Project/Final Project/Final Project/Interaction.h>


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
