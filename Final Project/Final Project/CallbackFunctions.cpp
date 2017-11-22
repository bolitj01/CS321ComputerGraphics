#include "CallbackFunctions.h"

//Display the scene in its current state
void display(void) {

	//Clear screen
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//Set projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(worldLeft, worldRight, worldBottom, worldTop, worldNear, worldFar);
	gluPerspective(50, 1, worldNear, worldFar);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//Set camera
	//updateCameraUpVector();
	gluLookAt(cameraLocation[0], cameraLocation[1], cameraLocation[2], 
			  cameraAtVertex[0], cameraAtVertex[1], cameraAtVertex[2], 
			  cameraUpVector[0], cameraUpVector[1], cameraUpVector[2]);

	//Rotate camera
	glRotatef(yCameraRot, 0, 1, 0);
	glRotatef(xCameraRot, 1, 0, 0);

	//Draw goal
	glPushMatrix();
	glTranslatef(0, 0, goalZLocation);
	glRotatef(yGoalRot, 0, 1, 0);
	glTranslatef(-goalBottomCenter[0], -goalBottomCenter[1], -goalBottomCenter[2]);
	drawFileG();
	glPopMatrix();
	

	//Draw ball
	glPushMatrix();
	glTranslatef(-ballBottomCenter[0], -ballBottomCenter[1] + ballRadius, -ballBottomCenter[2]);
	drawFileB();
	glPopMatrix();
	
	//drawFileS();

	glutSwapBuffers();
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
	float changeY = (previousMouseY - y) / 5;
	if (xCameraRot + changeY < 0 && xCameraRot + changeY > -90) {
		xCameraRot += changeY;
	}
	yCameraRot -= (previousMouseX - x) / 5;
	previousMouseX = x;
	previousMouseY = y;
	glutPostRedisplay();
}

//Controls actions for various key presses
void keyPress(unsigned char key, int x, int y)
{
	//Rotate camera 15 degrees around y axis
	if (key == 'Y') {
		yCameraRot += 15;
	}
	else if (key == 'y') {
		yCameraRot -= 15;
	}
	//Rotate camera 15 degrees around x axis
	if (key == 'X') {
		xCameraRot += 15;
	}
	else if (key == 'x') {
		xCameraRot -= 15;
	}
	else if (key == 'I' || key == 'i') {
		//Resets image
		initializeCamera();
	}
	else if (key == 'Q' || key == 'q') {
		//Exits program
		exit(0);
	}
	glutPostRedisplay();
}

