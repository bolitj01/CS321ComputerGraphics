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
	gluPerspective(45, screenWidth / screenHeight, worldNear, worldFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Set camera
	//updateCameraUpVector();
	gluLookAt(cameraLocation[0], cameraLocation[1], cameraLocation[2],
		cameraAtVertex[0], cameraAtVertex[1], cameraAtVertex[2],
		cameraUpVector[0], cameraUpVector[1], cameraUpVector[2]);

	//Draw kick line and HUD
	glPushMatrix();
	glColor3f(0, 0, 255);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3f(kickLineStartX, kickLineStartY, 0);
	glVertex3f(kickLineEndX, kickLineEndY, 0);
	glEnd();

	//Print kick up angle
	glRasterPos2f(-4, -5); //Make dynamic
	char kickAngleText[18] = { "Kick up angle:   " };
	snprintf(kickAngleText + 13, 3, "%d", (int)ballKickUpAngle);
	for (int i = 0; i < 18; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, kickAngleText[i]);
	}
	glPopMatrix();

	//Rotate camera
	glRotatef(yCameraRot - ballKickTurnAngle, 0, 1, 0);
	glRotatef(xCameraRot, 1, 0, 0);

	//Scale for bullet
	glScalef(worldScaleToBullet, worldScaleToBullet, worldScaleToBullet);

	//Draw goal
	glPushMatrix();
	glTranslatef(0, 0, goalZLocation);
	glRotatef(yGoalRot, 0, 1, 0);
	glScalef(goalScale, goalScale, goalScale);
	glTranslatef(-goalBottomCenter[0], -goalBottomCenter[1], -goalBottomCenter[2]);
	drawFileG();
	glPopMatrix();

	////Draw goal mesh
	//glPushMatrix();
	//glColor3f(255, 0, 0);
	//glTranslatef(0, 0, goalZLocation);
	////glTranslatef(-goalBottomCenter[0], -goalBottomCenter[1], -goalBottomCenter[2]);
	//glBegin(GL_LINE_LOOP);
	//for (int i = 0; i < 4; i++) {
	//	glVertex3f(goalMesh[i][0], goalMesh[i][1], goalMesh[i][2]);
	//}
	//glEnd();
	//glBegin(GL_LINE_LOOP);
	//for (int i = 0; i < 4; i++) {
	//	glVertex3f(goalMesh[i + 2][0], goalMesh[i + 2][1], goalMesh[i + 2][2]);
	//}
	//glEnd();
	//glBegin(GL_LINE_LOOP);
	//for (int i = 0; i < 4; i++) {
	//	glVertex3f(goalMesh[i + 4][0], goalMesh[i + 4][1], goalMesh[i + 4][2]);
	//}
	//glEnd();
	//glBegin(GL_LINE_LOOP);
	//glVertex3f(goalMesh[1][0], goalMesh[1][1], goalMesh[1][2]);
	//glVertex3f(goalMesh[2][0], goalMesh[2][1], goalMesh[2][2]);
	//glVertex3f(goalMesh[5][0], goalMesh[5][1], goalMesh[5][2]);
	//glVertex3f(goalMesh[6][0], goalMesh[6][1], goalMesh[6][2]);
	//glEnd();
	//glPopMatrix();
	

	//Draw ball
	glPushMatrix();
	float transformation[16];
	ballTransformation.getOpenGLMatrix(transformation);
	glMultMatrixf(transformation);
	glRotatef(ballRotation, 0, 1, 0);
	glRotatef(ballKickTurnAngle, 0, 1, 0);
	drawFileB();
	glPopMatrix();
	
	//drawFileS();

	glutSwapBuffers();
	glFlush();
}

//Step the dynamics world when application is idle
void idleWorldStep() {
	dynamicsWorld->stepSimulation(1 / 20.0f, 20);
	
	if (ballKicked) {
		btVector3 velocity = ballRigidBody->getLinearVelocity();

		if (velocity[2] > 10) {
			ballRotation += kickStrengthX * 15;
			velocity[0] -= kickStrengthX;
		}
			
		

		ballRigidBody->setLinearVelocity(velocity);
	}

	ballRigidBody->getMotionState()->getWorldTransform(ballTransformation);

	glutPostRedisplay();
}

//Gets position of mouse when left button is depressed
void mouseClick(int button, int state, int x, int y)
{
	previousMouseX = x;
	previousMouseY = y;
	//Left click to start dragging ball kick line
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		screenToWorldCoordinates(x, y, &kickLineStartX, &kickLineStartY);
		kickLineEndX = kickLineStartX;
		kickLineEndY = kickLineStartY;
		glutMotionFunc(mouseDrawKickLine);
	}
	//Kick ball
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		//Set ball velocities based on drawn kick line
		kickStrengthY = (kickLineEndY - kickLineStartY) * 120;
		kickStrengthX = (kickLineEndX - kickLineStartX) / 8;
		calculateBallVelocity();
		ballKicked = true;
		kickLineStartX = 0;
		kickLineStartY = 0;
		kickLineEndX = 0;
		kickLineEndY = 0;

		
	}
	//Right click for camera rotation
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glutMotionFunc(mouseCameraRotation);
	}
	else {
		glutMotionFunc(NULL);
	}
}

void calculateBallVelocity() {
	float pi = atan(1.0) * 4;
	float ballTurnFactorZ = cos(ballKickTurnAngle * pi / 180);
	float ballTurnFactorX = sin(ballKickTurnAngle * pi / 180);
	float ballUpFactorZ = cos(ballKickUpAngle * pi / 180);
	float ballUpFactorY = sin(ballKickUpAngle * pi / 180);

	ballVelocity[0] = kickStrengthY * ballTurnFactorX;
	ballVelocity[1] = kickStrengthY * ballUpFactorY / 3;
	ballVelocity[2] = kickStrengthY * ballTurnFactorZ * ballUpFactorZ;

	//Set ball velocity in dynamics world
	ballRigidBody->setLinearVelocity(ballVelocity);
}

//Use mouse to draw a line 
void mouseDrawKickLine(int x, int y) {
	screenToWorldCoordinates(x, y, &kickLineEndX, &kickLineEndY);
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
	else if (key == 'k' || key == 'K') {
		ballRigidBody->getWorldTransform().setIdentity();
		ballRigidBody->getWorldTransform().setOrigin(btVector3(0, ballRadius, 0));
		ballRigidBody->clearForces();
		ballRigidBody->setAngularVelocity(btVector3(0, 0, 0));
		ballRigidBody->setLinearVelocity(btVector3(0, 0, 0));
		ballRigidBody->applyTorque(btVector3(0, 10, 0));
		ballRigidBody->setLinearVelocity(btVector3(0, 0, 200));
	}
	else if (key == 'r' || key == 'R') {
		ballRigidBody->getWorldTransform().setIdentity();
		ballRigidBody->getWorldTransform().setOrigin(btVector3(0, ballStartingHeightOffGround + ballRadius, 0));
		ballRigidBody->clearForces();
		ballRigidBody->setAngularVelocity(btVector3(0, 0, 0));
		ballRigidBody->setLinearVelocity(btVector3(0, 0, 0));
		ballKicked = false;
	}
	glutPostRedisplay();
}

//Handle key presses of special keys such as arrows
void specialKeyPress(int key, int x, int y) {
	switch (key) {
		//Increase ball kick up angle
		case GLUT_KEY_UP:
			if (ballKickUpAngle < 70) {
				ballKickUpAngle += 5;
			}
			break;
		//Decrease ball kick up angle
		case GLUT_KEY_DOWN:
			if (ballKickUpAngle > 0) {
				ballKickUpAngle -= 5;
			}
			break;
		//Increase ball kick turn angle
		case GLUT_KEY_LEFT:
			if (ballKickTurnAngle < 45) {
				ballKickTurnAngle += 1;
			}
			break;
		case GLUT_KEY_RIGHT:
			if (ballKickTurnAngle > -45) {
				ballKickTurnAngle -= 1;
			}
			break;
	}
}

