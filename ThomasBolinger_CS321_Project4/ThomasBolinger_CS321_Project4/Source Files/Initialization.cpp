/*
	Thomas Bolinger
	CS321 Computer Graphics
	The main initialization functions for using OpenGL and GLUT
*/

#include "../Header Files/Initialization.h"

//Initialize state paremeters and create empty window
void init_window(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Project 3");
}

//Declare other state variables such as background color, foreground color, and orthographic projection
void other_init() {
	//Set background to white
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//Set foreground to black
	glColor3f(0, 0, 0);

	//Clear projection and model view matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

//Translate object's center to the origin and scale to reasonable size
void initializeObject() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	getObjectHeightWidthDepthCenter();

	//Translate the object to the origin and then scale it proportionally to 1/3 screen width 
	//Get difference of current object's percentage screen width to 1/3 screen width
	float desiredWidth = 4052 * 2 / 3;
	float scaleAmount = (desiredWidth - objectWidth) / objectWidth;

	//Scale by that amount
	glScalef(1 + scaleAmount, 1 + scaleAmount, 1 + scaleAmount);

	objectHeight = objectHeight * (1 + scaleAmount);
	objectWidth = objectWidth * (1 + scaleAmount);
	objectDepth = objectDepth * (1 + scaleAmount);

	glTranslatef(-objectCenter[0], -objectCenter[1], -objectCenter[2]);

	objectCenter[0] = 0;
	objectCenter[1] = 0;
	objectCenter[2] = 0;
}

void initializeViewingVolume() {
	//Initialize viewing volume
	worldLeft = -2026;
	worldRight = 2026;
	worldBottom = -2026;
	worldTop = 1000;
	worldNear = -4052;
	worldFar = 4052;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	updateViewingVolume(0, false, false, false);
}

void initializeViewport() {
	//Initialize viewport
	viewportWidth = 300;
	viewportHeight = 200;
	viewportX = (screenWidth - viewportWidth) / 2;
	viewportY = (screenHeight - viewportHeight) / 2;
}

//Initialize the camera location and orientation
void initializeCamera() {
	eyeX = 0;
	eyeY = 0;
	eyeZ = worldDepth;
	atX = 0;
	atY = 0;
	atZ = 0;
	upX = 0;
	upY = 1;
	upZ = 0;
}

