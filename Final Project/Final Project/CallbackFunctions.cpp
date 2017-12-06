#include "CallbackFunctions.h"

//Display the scene in its current state
void display(void) {

	//Clear screen
	glClearColor(0.5, 0.5, 0.7, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set lighting

	//Global lighting
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMaterial);

	//Outside direction light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, outsideDiffuseLight);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, outsideCutoff);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, outsideExponent);

	//Outside specular light
	glLightfv(GL_LIGHT4, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT5, GL_EMISSION, emissiveLight);
	
	
	//Lamp 1
	glLoadIdentity();
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lamp1DiffuseLight);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, lampCutoff);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, lampExponent);

	//Lamp 2
	glLoadIdentity();
	glLightfv(GL_LIGHT3, GL_DIFFUSE, lamp2DiffuseLight);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, lampCutoff);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, lampExponent);

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

	//Rotate camera
	glRotatef(yCameraRot - ballKickTurnAngle, 0, 1, 0);
	glRotatef(xCameraRot, 1, 0, 0);

	//Scale for bullet
	glScalef(worldScaleToBullet, worldScaleToBullet, worldScaleToBullet);

	//Draw kick line and HUD
	glColor3f(0, 0, 1);
	glLineWidth(5);

	if (!ballKicked) {
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(kickLineStartX, kickLineStartY, cameraLocation[2]);
		if (kickLineEndY > 0) {
			glVertex3f(kickLineEndX, kickLineEndY * 4, cameraLocation[2]);
		}
		else {
			glVertex3f(kickLineEndX, kickLineEndY, cameraLocation[2]);
		}
		
		glEnd();

		//float textPositionX = cameraLocation[2] * 1.1 * screenWidth / screenHeight;
		//float textPositionY = cameraLocation[2] * 1.6;

		////Print kick up angle
		//glRasterPos2f(1, 1);
		//char kickUpAngleText[18] = { "Kick up angle:   " };
		//snprintf(kickUpAngleText + 15, 3, "%d", (int)ballKickUpAngle);
		//for (int i = 0; i < 18; i++) {
		//	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, kickUpAngleText[i]);
		//}

		////Print kick turn angle
		//glRasterPos2f(3, 1);
		//char kickTurnAngleText[22] = { "Kick turn angle:     " };
		//snprintf(kickTurnAngleText + 17, 4, "%d", (int)ballKickTurnAngle);
		//for (int i = 0; i < 22; i++) {
		//	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, kickTurnAngleText[i]);
		//}
		//glPopMatrix();

		//Draw kick angle
		glPushMatrix();
		glRotatef(-ballKickUpAngle, 1, 0, 0);
		glRotatef(ballKickTurnAngle, 0, 1, 0);
		glTranslatef(0, ballRadius, 0);
		glColor3f(0, 0, 1);
		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 30);
		glEnd();
		glPopMatrix();
	}

	glLightfv(GL_LIGHT1, GL_POSITION, outsideLightPosition);
	glLightfv(GL_LIGHT4, GL_POSITION, outsideLightPosition);
	glLightfv(GL_LIGHT2, GL_POSITION, lamp1LightPosition);
	glLightfv(GL_LIGHT3, GL_POSITION, lamp2LightPosition);

	
	
	//Draw goal
	glPushMatrix();
	glTranslatef(80, 0, goalZLocation);
	glRotatef(yGoalRot, 0, 1, 0);
	glScalef(goalScale, goalScale, goalScale);
	glTranslatef(-goalBottomCenter[0], -goalBottomCenter[1], -goalBottomCenter[2]);
	drawFileG();
	glPopMatrix();

	/*//Draw goal mesh
	glPushMatrix();
	glColor3f(255, 0, 0);
	glTranslatef(0, 0, goalZLocation);
	glTranslatef(-goalBottomCenter[0], -goalBottomCenter[1], -goalBottomCenter[2]);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		glVertex3f(goalMesh[i][0], goalMesh[i][1], goalMesh[i][2]);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		glVertex3f(goalMesh[i + 2][0], goalMesh[i + 2][1], goalMesh[i + 2][2]);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		glVertex3f(goalMesh[i + 4][0], goalMesh[i + 4][1], goalMesh[i + 4][2]);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(goalMesh[1][0], goalMesh[1][1], goalMesh[1][2]);
	glVertex3f(goalMesh[2][0], goalMesh[2][1], goalMesh[2][2]);
	glVertex3f(goalMesh[5][0], goalMesh[5][1], goalMesh[5][2]);
	glVertex3f(goalMesh[6][0], goalMesh[6][1], goalMesh[6][2]);
	glEnd();
	glPopMatrix();*/
	
	//Draw stadium
	if (drawStadium) {
		glPushMatrix();
		glTranslated(0, -9, -14);
		glRotated(90, 0, 1, 0);
		glScaled(400, 200, 200);
		glTranslatef(-stadiumBottomCenter[0], -stadiumBottomCenter[1], -stadiumBottomCenter[2]);
		drawFileS();
		glPopMatrix();
	}

	//Draw four lamps
	glPushMatrix();
	glTranslated(375, 0, 200);
	glScaled(10, 10, 10);
	drawFileL();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-375, 0, 200);
	glScaled(10, 10, 10);
	drawFileL();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(370, 0, 800);
	glScaled(10, 10, 10);
	drawFileL();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-370, 0, 800);
	glScaled(10, 10, 10);
	drawFileL();
	glPopMatrix();

	emissiveMaterial[0] = .1;
	emissiveMaterial[1] = .1;
	emissiveMaterial[2] = .1;

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissiveMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularMaterial);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	//For loading physics world transformations of ball and target
	float transformation[16];

	//Draw target
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	targetTransformation.getOpenGLMatrix(transformation);
	glMultMatrixf(transformation);
	glRotatef(targetRotation, 0, 1, 0);
	glScalef(targetScale, targetScale, targetScale / 3);
	glColor3f(1, 0, 0);
	drawTarget();
	glPopMatrix();

	//Draw ball
	glPushMatrix();
	ballTransformation.getOpenGLMatrix(transformation);
	glMultMatrixf(transformation);
	glRotatef(ballRotationY, 0, 1, 0);
	glRotatef(ballKickTurnAngle, 0, 1, 0);
	glTranslatef(-ballBottomCenter[0], -ballBottomCenter[1], -ballBottomCenter[2]);
	drawFileB();
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}

//Step the dynamics world when application is idle
void idleWorldStep() {
	dynamicsWorld->stepSimulation(1 / 20.0f, 20);
	
	if (ballKicked) {
		btVector3 velocity = ballRigidBody->getLinearVelocity();

		if (velocity[2] > 10) {
			ballRotationY -= kickStrengthX * 30;
			velocity[0] -= kickStrengthX * 1.3;
		}

		ballRigidBody->setLinearVelocity(velocity);
	}

	ballRigidBody->getMotionState()->getWorldTransform(ballTransformation);
	targetRigidBody->getMotionState()->getWorldTransform(targetTransformation);

	targetRotation = (targetRotation + 1) % 360;

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
		if (!ballKicked) {
			screenToWorldCoordinates(x, y, &kickLineStartX, &kickLineStartY);
			kickLineEndX = kickLineStartX;
			kickLineEndY = kickLineStartY;
			glutMotionFunc(mouseDrawKickLine);
		}
	}
	//Kick ball
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (!ballKicked) {
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
	}
	//Right click for camera rotation
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glutMotionFunc(mouseCameraRotation);
	}
	//Scroll up move camera forward
	else if (button == 3) {
		if (cameraLocation[2] < -17) {
			cameraLocation[2] += 1;
		}
	
	}
	//Scroll down move camera backward
	else if (button == 4) {
		cameraLocation[2] -= 1;
	}
	else {
		glutMotionFunc(NULL);
	}
}

void calculateBallVelocity() {
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
	int mod = glutGetModifiers();

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
	//Toggle light 1
	else if (key == '1') {
		if (!lamp1Enabled) {
			glEnable(GL_LIGHT2);
			lamp1Enabled = true;
		}
		else {
			glDisable(GL_LIGHT2);
			lamp1Enabled = false;
		}
	}
	//Toggle light 2
	else if (key == '2') {
		if (!lamp2Enabled) {
			glEnable(GL_LIGHT3);
			lamp2Enabled = true;
		}
		else {
			glDisable(GL_LIGHT3);
			lamp2Enabled = false;
		}
	}
	//Toggle stadium drawing
	else if (mod == GLUT_ACTIVE_ALT) {
		if (key == 's') {
			if (drawStadium) {
				drawStadium = false;
			}
			else {
				drawStadium = true;
			}
		}
		else if (key == 't') {
			if (displayTextures) {
				displayTextures = false;
			}
			else {
				displayTextures = true;
			}
		}
	}
	//Increase/decrease diffuse light
	else if (key == 'D') {
		if (diffuseLight[1] < 1) {
			diffuseLight[0] += .1;
			diffuseLight[1] += .1;
			diffuseLight[2] += .1;

			outsideDiffuseLight[0] += .1;
			outsideDiffuseLight[1] += .1;
			outsideDiffuseLight[2] += .1;
		}
	}
	else if (key == 'd') {
		if (diffuseLight[1] >= .1) {
			diffuseLight[0] -= .1;
			diffuseLight[1] -= .1;
			diffuseLight[2] -= .1;

			outsideDiffuseLight[0] -= .1;
			outsideDiffuseLight[1] -= .1;
			outsideDiffuseLight[2] -= .1;
		}
	}
	//Increase/decrease ambient light
	else if (key == 'A') {
		if (ambientLight[0] < 1) {
			ambientLight[0] += .1;
			ambientLight[1] += .1;
			ambientLight[2] += .1;
		}
	}
	else if (key == 'a') {
		if (ambientLight[0] >= 0) {
			ambientLight[0] -= .1;
			ambientLight[1] -= .1;
			ambientLight[2] -= .1;
		}
	}
	//Increase/decrease emissive light values
	else if (key == 'E') {
		if (emissiveLight[0] < 1) {
			emissiveLight[0] += .1;
			emissiveLight[1] += .1;
			emissiveLight[2] += .1;
		}
	}
	else if (key == 'e') {
		if (emissiveLight[0] > 0) {
			emissiveLight[0] -= .1;
			emissiveLight[1] -= .1;
			emissiveLight[2] -= .1;
		}
	}
	//Increase/decrease specular light values
	else if (key == 'S') {
		if (specularLight[0] < 1) {
			specularLight[0] += .1;
			specularLight[1] += .1;
			specularLight[2] += .1;
		}
	}
	else if (key == 's') {
		if (specularLight[0] > 0) {
			specularLight[0] -= .1;
			specularLight[1] -= .1;
			specularLight[2] -= .1;
		}
	}
	//Increase/decrease lamp light values
	else if (key == 'L') {
		lamp1DiffuseLight[0] += .1;
		lamp1DiffuseLight[1] += .1;
		lamp1DiffuseLight[2] += .1;
		lamp2DiffuseLight[0] += .1;
		lamp2DiffuseLight[1] += .1;
		lamp2DiffuseLight[2] += .1;
	}
	else if (key == 'l') {
		lamp1DiffuseLight[0] -= .1;
		lamp1DiffuseLight[1] -= .1;
		lamp1DiffuseLight[2] -= .1;
		lamp2DiffuseLight[0] -= .1;
		lamp2DiffuseLight[1] -= .1;
		lamp2DiffuseLight[2] -= .1;
	}
	//Increase/decrease lamp light exponents
	else if (key == 'E') {
		lampExponent += 1;
	}
	else if (key == 'e') {
		lampExponent -= 1;
	}
	//Increase/decrease cutoff angle of lamp lights
	else if (key == 'C') {
		if (lampCutoff < 180) {
			lampCutoff += 5;
		}
	}
	else if (key == 'c') {
		if (lampCutoff > 0) {
			lampCutoff -= 5;

		}	
	}
	//Enable or disable wireframe mode
	else if (key == 'W') {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (key == 'w') {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	//Initialize camera to where the ball is facing
	else if (key == 'I' || key == 'i') {
		initializeCamera();
	}
	//Exit program
	else if (key == 'Q' || key == 'q') {
		exit(0);
	}
	//Move the target to a new position
	else if (key == 'n' || key == 'N') {
		calculateNewTargetPosition();
		targetRigidBody->getWorldTransform().setIdentity();
		targetRigidBody->getWorldTransform().setOrigin(targetLocation);
		targetRigidBody->clearForces();
		targetRigidBody->setAngularVelocity(btVector3(0, 0, 0));
		targetRigidBody->setLinearVelocity(btVector3(0, 0, 0));
	}
	else if (key == 'r' || key == 'R') {
		ballRigidBody->getWorldTransform().setIdentity();
		ballRigidBody->getWorldTransform().setOrigin(btVector3(0, ballStartingHeightOffGround + ballRadius, 0));
		ballRigidBody->clearForces();
		ballRigidBody->setAngularVelocity(btVector3(0, 0, 0));
		ballRigidBody->setLinearVelocity(btVector3(0, 0, 0));
		ballKicked = false;
	}
	else if (key == ' ') {
		calculateNewTargetPosition();
		targetRigidBody->getWorldTransform().setIdentity();
		targetRigidBody->getWorldTransform().setOrigin(targetLocation);
		targetRigidBody->clearForces();
		targetRigidBody->setAngularVelocity(btVector3(0, 0, 0));
		targetRigidBody->setLinearVelocity(btVector3(0, 0, 0));

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

