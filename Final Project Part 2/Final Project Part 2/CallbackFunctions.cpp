#include "CallbackFunctions.h"

//Display the scene in its current state
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(worldLeft, worldRight, worldBottom, worldTop, worldNear, worldFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-400, 0, 0, 0, 0, 0, 0, 1, 0);
	glRotatef(xRot, 1.0, 0.0, 0.0);
	glRotatef(yRot, 0.0, 1.0, 0.0);
	glRotatef(zRot, 0.0, 0.0, 1.0);
	glScalef(scaleAmount, scaleAmount, scaleAmount);
	glTranslatef(xMove, yMove, zMove);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseLight);
	glEnable(GL_LIGHT0);
	

	//drawFileG();

	//STADIUM
	glTranslatef(500, 0, 0);
	glPushMatrix();
	glScalef(50, 50, 50);
	glRotatef(30, 0, 0, 1);
	drawFileS();
	glPopMatrix();

	//BALL
	//drawFileB();

	//glEnable(GL_CULL_FACE);
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
	
    if ((key == 'L') || (key == 'l')) {
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
	else if (key == 'D') {
		if (diffuseLight[1] < 1) {
			diffuseLight[0] += .1;
			diffuseLight[1] += .1;
			diffuseLight[2] += .1;
		}
	}
	else if (key == 'd') {
		if (diffuseLight[1] >= .1) {
			diffuseLight[0] -= .1;
			diffuseLight[1] -= .1;
			diffuseLight[2] -= .1;
		}
	}
	else if (key == 'A') {
		if (ambientLight[0] < 1) {
			ambientLight[0] += .1;
			ambientLight[1] += .1;
			ambientLight[2] += .1;
		}
	}
	else if (key == 'a') {
		if (ambientLight[0] >= .1) {
			ambientLight[0] -= .1;
			ambientLight[1] -= .1;
			ambientLight[2] -= .1;
		}
	}
	glutPostRedisplay();
}

