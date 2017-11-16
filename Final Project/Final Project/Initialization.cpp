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
	worldLeft = -200;
	worldRight = 200;
	worldBottom = -200;
	worldTop = 200;
	worldNear = 200;
	worldFar = 1000;
}

