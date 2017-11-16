#include "CallbackFunctions.h"

//Display the scene in its current state
void display(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(worldLeft, worldRight, worldBottom, worldTop, worldNear, worldFar);
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

//Gets position of mouse when left button is depressed
void mouseClick(int button, int state, int x, int y)
{
	previousMouseX = x;
	previousMouseY = y;
	//Left click for ball shooting
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
	}
	//Right click for camera rotation
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glutMotionFunc(mouseCameraRotation);
	}
}

//Use mouse to rotate the camera around the ball
void mouseCameraRotation(int x, int y)
{
	//Calculate change in mouse position
	xRot -= (previousMouseY - y);
	yRot -= (previousMouseX - x);
	previousMouseX = x;
	previousMouseY = y;
	glutPostRedisplay();
}

//Controls actions for various key presses
void keyPress(unsigned char key, int x, int y)
{
	if ((key == 'U') || (key == 'u')) {
		//Move forward along Y axis
		yMove += 40;
	}
	else if ((key == 'D') || (key == 'd')) {
		//Move backward along Y axis
		yMove -= 40;
	}
	else if ((key == 'L') || (key == 'l')) {
		//Move backward along X axis
		xMove -= 40;
	}
	else if ((key == 'R') || (key == 'r')) {
		//Move forward along X axis
		xMove += 40;
	}
	else if ((key == 'F') || (key == 'f')) {
		//Move forward along Z axis
		zMove += 40;
	}
	else if ((key == 'N') || (key == 'n')) {
		//Move back along Z axis
		zMove -= 40;
	}
	else if (key == '+') {
		//Enlarge
		scaleAmount += .1;
	}
	else if (key == '-') {
		//Shrink
		scaleAmount -= .1;
	}
	else if (key == 'x') {
		//Rotate +15 degrees around x axis
		xRot += 15;
	}
	else if (key == 'X') {
		//Rotate -15 degrees around x axis
		xRot -= 15;
	}
	else if (key == 'y') {
		//Rotate +15 degrees around y axis
		yRot += 15;
	}
	else if (key == 'Y') {
		//Rotate -15 degrees around y axis
		yRot -= 15;
	}
	else if (key == 'z') {
		//Rotate +15 degrees around z axis
		zRot += 15;
	}
	else if (key == 'Z') {
		//Rotate -15 degrees around z axis
		zRot -= 15;
	}
	else if (key == 'I' || key == 'i') {
		//Resets image
		xRot = 0;
		yRot = 0;
		zRot = 15;
		scaleAmount = 3.0;
		xMove = 0;
		yMove = 0;
	}
	else if (key == 'Q' || key == 'q') {
		//Exits program
		exit(0);
	}
	else if (key == 'T' || key == 't') {
		//Toggles mode, 0 for drag and drop, 1 for rotate.
		if (mode == 0) {
			mode = 1;
		}
		else {
			mode = 0;
		}
	}
	glutPostRedisplay();
}

