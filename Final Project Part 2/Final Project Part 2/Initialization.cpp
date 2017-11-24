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
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseLight);
	glEnable(GL_LIGHT0);

	glLoadIdentity();
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection1);
	glLighti(GL_LIGHT1, GL_SPOT_EXPONENT, exponent);
	glEnable(GL_LIGHT1);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}