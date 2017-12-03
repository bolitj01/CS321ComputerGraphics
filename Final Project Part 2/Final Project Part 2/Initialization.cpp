#include "Initialization.h"

//All the functions for intializing openGL or data

void initWindow(int &argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Problem #1");
}

void initializeViewingVolume() {
	worldLeft = -350;
	worldRight = 350;
	worldBottom = -400;
	worldTop = 400;
	worldNear = 400;
	worldFar = 4000;
}

void setupLight() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHT0);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}