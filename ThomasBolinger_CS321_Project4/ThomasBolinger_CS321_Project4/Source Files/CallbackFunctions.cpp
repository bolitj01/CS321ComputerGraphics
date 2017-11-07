#include "../Header Files/CallbackFunctions.h"

//All glut callback functions for key, mouse, and display

//Display all the vertex data
void display(void) {

	//Set background to white
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);

	//Save current transformations
	GLfloat transformationMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, transformationMatrix);

	//Clear Model view matrix and set project, viewport, and camera
	glLoadIdentity();

	if (fourViewportsOn) {
		//Draw four viewports with different camera views
		for (int i = 0; i < 4; i++) {
			perspectiveOn = false;
			//Orthographic front view bottom left
			if (i == 0) {
				glViewport(0, 0, screenWidth / 2, screenHeight / 2);
				frontCamera();
			}
			//Orthographic side view bottom right
			else if (i == 1) {
				glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight / 2);
				sideCamera();
			}
			//Orthographic top view top left
			else if (i == 2) {
				glViewport(0, screenHeight/ 2, screenWidth / 2, screenHeight / 2);
				topCamera();
			}
			//Perspective view top right
			else if (i == 3) {
				glViewport(screenWidth / 2, screenHeight / 2, screenWidth / 2, screenHeight / 2);
				initializeCamera();
				eyeX = eyeZ;
				eyeY = eyeZ;
				perspectiveOn = true;
			}

			updateViewingVolume(0, false, false, false);

			setProjection();

			setCamera();

			glMultMatrixf(transformationMatrix);

			drawObject();

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
	}
	else {
		updateViewingVolume(0, false, false, false);

		setProjection();

		setCamera();

		setViewport();

		glMultMatrixf(transformationMatrix);

		drawObject();

		//Draw viewport border
		glColor3f(255, 0, 0);

		//Ignore object transformations
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(worldLeft, worldRight, worldBottom, worldTop, worldNear, worldFar);

		glBegin(GL_LINE_LOOP);
		glVertex3f(worldLeft + (worldWidth / 1000), worldBottom + (worldHeight / 1000), 0);
		glVertex3f(worldRight - (worldWidth / 1000), worldBottom + (worldHeight / 1000), 0);
		glVertex3f(worldRight - (worldWidth / 1000), worldTop - (worldHeight / 1000), 0);
		glVertex3f(worldLeft + (worldWidth / 1000), worldTop - (worldHeight / 1000), 0);
		glEnd();

		glPopMatrix();

		glColor3f(0, 0, 0);
	}

	//Restore previous transformation matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(transformationMatrix);
	
	glFlush(); //Force display immediately
	glutSwapBuffers(); //Double buffering
}

//Update viewing volume through scaling
void updateViewingVolume(float scaleFactor, bool updateX, bool updateY, bool updateZ){
	if (updateX) {
		worldLeft -= worldWidth * scaleFactor;
		worldRight += worldWidth * scaleFactor;
	}
	if (updateY) {
		worldBottom -= worldHeight * scaleFactor;
		worldTop += worldHeight * scaleFactor;
	}
	if (updateZ) {
		worldNear -= worldDepth * scaleFactor;
		worldFar += worldDepth * scaleFactor;
	}

	worldWidth = worldRight - worldLeft;
	worldHeight = worldTop - worldBottom;
	worldDepth = worldFar - worldNear;
}

//Update camera through scaling
void updateCamera(float scaleFactor, bool updateX, bool updateY, bool updateZ) {
	if (updateX) {
		eyeX += eyeX * scaleFactor;
	}
	if (updateY) {
		eyeY += eyeY * scaleFactor;
	}
	if (updateZ) {
		eyeZ += eyeZ * scaleFactor;
	}
}

void frontCamera() {
	initializeCamera();
}

//Move camera to side
void sideCamera() {
	initializeCamera();
	eyeX = eyeZ;
	eyeZ = 0;
}

//Move camera to top
void topCamera() {
	initializeCamera();

	eyeY = eyeZ;
	eyeZ = 0;
	upX = 0;
	upY = 0;
	upZ = -1.0;
}

//Set projection type
void setProjection() {
	glMatrixMode(GL_PROJECTION);
	if (perspectiveOn) {
		//gluPerspective(45, 1, 1, worldDepth * 4);
		glFrustum(worldLeft, worldRight, worldBottom, worldTop, worldDepth * 2.0/3, worldDepth * 1000);
	}
	else {
		glOrtho(worldLeft, worldRight, worldBottom, worldTop, worldNear, worldFar * 10);
	}
	glMatrixMode(GL_MODELVIEW);
}

//Set viewport
void setViewport() {
	glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
}

//Set camera position and orientation
void setCamera() {
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(eyeX, eyeY, eyeZ, atX, atY, atZ, upX, upY, upZ);
}

//Apply geometric transformation and draw the object
void drawObject() {

	int index = 0;

	for (int i = 0; i < vertexGroups; i++) {
		glBegin(GL_LINE_STRIP);

		for (int j = 0; j < verticesPerGroup[i]; j++) {
			glVertex3fv(vertices[index]);
			index++;
		}

		glEnd();
	}
}

//Callback for ascii key presses
void keyboardControls(unsigned char key, int x, int y) {
	getObjectHeightWidthDepthCenter();

	float previous;

	switch (key) {

	//Move viewport up 10% of screen height with object panning effect
	case 'u':
		//Check screen boundaries
		if ((viewportY + viewportHeight / 10) <= (screenHeight - viewportHeight)) {
			viewportY = viewportY + viewportHeight / 10;
			//Move viewing volume up as well
			worldBottom += worldHeight / 10;
			worldTop += worldHeight / 10;
		}
		else {
			previous = viewportY;
			viewportY = screenHeight - viewportHeight;
			worldBottom += (viewportY - previous) / viewportHeight * worldHeight;
			worldTop += (viewportY - previous) / viewportHeight * worldHeight;
		}
		updateViewingVolume(0, false, false, false);
		display();
		break;

	//Move the viewport down 10% of screen height with panning effect
	case 'd':
		//Check screen boundaries
		if ((viewportY - viewportHeight / 10) >= 0) {
			viewportY = viewportY - viewportHeight / 10;
			//Move viewing volume down as well
			worldBottom -= worldHeight / 10;
			worldTop -= worldHeight / 10;
		}
		else {
			previous = viewportY;
			viewportY = 0;
			worldBottom -= (previous / viewportHeight) * worldHeight;
			worldTop -= (previous / viewportHeight) * worldHeight;
		}
		updateViewingVolume(0, false, false, false);
		display();
		break;

	case 'l':
		//Check screen boundaries
		if ((viewportX - viewportWidth / 10) >= 0) {
			viewportX = viewportX - viewportWidth / 10;
			//Move viewing volume with viewport
			worldLeft -= worldWidth / 10;
			worldRight -= worldWidth / 10;
		}
		else {
			previous = viewportX;
			viewportX = 0;
			worldLeft -= (previous / viewportWidth) * worldWidth;
			worldRight -= (previous / viewportWidth) * worldWidth;
		}
		updateViewingVolume(0, false, false, false);
		display();
		break;

	case 'r':
		//Check screen boundaries
		if ((viewportX + viewportWidth / 10) <= (screenWidth - viewportWidth)) {
			viewportX = viewportX + viewportWidth / 10;
			//Move viewing volume with viewport
			worldLeft += worldWidth / 10;
			worldRight += worldWidth / 10;
		}
		else {
			previous = viewportX;
			viewportX = screenWidth - viewportWidth;
			worldLeft += (viewportX - previous) / viewportWidth * worldWidth;
			worldRight += (viewportX - previous) / viewportWidth * worldWidth;
		}
		updateViewingVolume(0, false, false, false);
		display();
		break;

	//Increase the size of viewport by 10%
	case 'E':
		if (!fourViewportsOn) {
			if (viewportWidth * 1.1 <= screenWidth && viewportHeight * 1.1 <= screenHeight) {
				//Scale and translate viewport width
				previous = viewportWidth;
				viewportWidth = viewportWidth * 1.1;
				viewportX = viewportX - (viewportWidth - previous) / 2;

				//Scale and translate viewport height
				previous = viewportHeight;
				viewportHeight = viewportHeight * 1.1;
				viewportY = viewportY - (viewportHeight - previous) / 2;

				//Scale viewing port in opposite direction
				updateViewingVolume(1.0 / 10 / 2, true, true, false);
			}
			else {
				previous = viewportWidth;
				viewportWidth = screenWidth;
				viewportX = viewportX - (viewportWidth - previous) / 2;

				previous = viewportHeight;
				viewportHeight = screenHeight;
				viewportY = viewportY - (viewportHeight - previous) / 2;

				updateViewingVolume((1 - previous / viewportHeight) / 2, true, true, false);
			}
			display();
		}
		break;

	//Decrease size of viewport by 10%
	case 'e':
		if (!fourViewportsOn) {
			if (viewportWidth * .9 >= 10 && viewportHeight * .9 >= 10) {
				//Scale and translate viewport width
				previous = viewportWidth;
				viewportWidth = viewportWidth * .9;
				viewportX = viewportX - (viewportWidth - previous) / 2;

				//Scale and translate viewport height
				previous = viewportHeight;
				viewportHeight = viewportHeight * .9;
				viewportY = viewportY - (viewportHeight - previous) / 2;

				//Scale viewing port in opposite direction
				updateViewingVolume(-1.0 / 10 / 2, true, true, false);
			}
			else {
				previous = viewportWidth;
				viewportWidth = 10 * viewportWidth / viewportHeight;
				viewportX = viewportX - (viewportWidth - previous) / 2;

				previous = viewportHeight;
				viewportHeight = 10;
				viewportY = viewportY - (viewportHeight - previous) / 2;

				updateViewingVolume(-(1 - previous / viewportHeight) / 2, true, true, false);
			}
			display();
		}
		break;

	//Toggle perspective projection
	case 'P':
	case 'p':
		fourViewportsOn = false;
		perspectiveOn = true;
		display();
		break;

	//Move camera to front view
	case 'O':
	case 'o':
		perspectiveOn = false;
		fourViewportsOn = false;

		frontCamera();
		display();
		break;

	//Move camera to side view
	case 'S':
	case 's':
		perspectiveOn = false;
		fourViewportsOn = false;

		sideCamera();
		display();
		break;

	//Move camera to top view
	case 'T':
	case 't':
		perspectiveOn = false;
		fourViewportsOn = false;

		topCamera();
		display();
		break;

	//Split into four viewports from different angles
	case 'V':
	case 'v':
		perspectiveOn = false;
		fourViewportsOn = true;

		initializeViewingVolume();
		initializeCamera();
		display();
		break;

	//Move camera foward 10% of center of projection
	case 'F':
	case 'f':
		updateCamera(1.0 / 20, true, true, true);
		display();
		break;

	//Move camera back 10% of center of projection
	case 'N':
	case 'n':
		if ((eyeX == 0 || eyeX * .95 > worldDepth * 2.0 / 3) && (eyeY == 0 || eyeY * .95 > worldDepth * 2.0 / 3)
			&& (eyeZ == 0 || eyeZ * .95 > worldDepth * 2.0 / 3)) {
			updateCamera(-1.0 / 20, true, true, true);
			display();
		}
		break;

	//Move object up 10% of the object's height
	case 'U':
		glTranslatef(0, objectHeight / 10, 0);
		display();
		break;
	
	//Move object down 10% of object's height
	case 'D':
		glTranslatef(0, -objectHeight / 10, 0);
		display();
		break;
		
	//Move object left 10% of object's width
	case 'L':
		glTranslatef(-objectWidth / 10, 0, 0);
		display();
		break;
	
	//Move object right 10% of object's width
	case 'R':
		glTranslatef(objectWidth / 10, 0, 0);
		display();
		break;

	//Increase the size of the object by 10%
	case '=':
	case '+':
		//Translate to origin, scale, put back
		glTranslatef(objectCenter[0], objectCenter[1], objectCenter[2]);
		glScalef(1.1, 1.1, 1.1);
		glTranslatef(-objectCenter[0], -objectCenter[1], -objectCenter[2]);
		updateViewingVolume(1.0 / 20, false, false, true);
		display();
		break;

	//Decrease the size of the object by 10%
	case '-':
	case '_':
		//Translate to origin, scale, put back
		glTranslatef(objectCenter[0], objectCenter[1], objectCenter[2]);
		glScalef(.9, .9, .9);
		glTranslatef(-objectCenter[0], -objectCenter[1], -objectCenter[2]);
		updateViewingVolume(-1.0 / 20, false, false, true);
		display();
		break;

	//Rotate object around x-axis by +15 degrees
	case 'X':
		//Rotate object along x axis
		glTranslatef(objectCenter[0], objectCenter[1], objectCenter[2]);
		glRotatef(15, 1, 0, 0);
		glTranslatef(-objectCenter[0], -objectCenter[1], -objectCenter[2]);
		display();
		break;

	//Rotate object around x-axis by -15 degrees
	case 'x':
		//Transform object
		glTranslatef(objectCenter[0], objectCenter[1], objectCenter[2]);
		glRotatef(-15, 1, 0, 0);
		glTranslatef(-objectCenter[0], -objectCenter[1], -objectCenter[2]);
		display();
		break;

	//Rotate object around y axis by +15 degrees
	case 'Y':
		//Transform object
		glTranslatef(objectCenter[0], objectCenter[1], objectCenter[2]);
		glRotatef(15, 0, 1, 0);
		glTranslatef(-objectCenter[0], -objectCenter[1], -objectCenter[2]);
		display();
		break;

	//Rotate object around y axis by -15 degrees
	case 'y':
		//Transform object
		glTranslatef(objectCenter[0], objectCenter[1], objectCenter[2]);
		glRotatef(-15, 0, 1, 0);
		glTranslatef(-objectCenter[0], -objectCenter[1], -objectCenter[2]);
		display();
		break;

	//Rotate object around the z axis by +15 degrees
	case 'Z':
		//Transform object
		glTranslatef(objectCenter[0], objectCenter[1], objectCenter[2]);
		glRotatef(15, 0, 0, 1);
		glTranslatef(-objectCenter[0], -objectCenter[1], -objectCenter[2]);
		display();
		break;

	//Rotate object around the z axis by -15 degrees
	case 'z':
		//Transform object
		glTranslatef(objectCenter[0], objectCenter[1], objectCenter[2]);
		glRotatef(-15, 0, 0, 1);
		glTranslatef(-objectCenter[0], -objectCenter[1], -objectCenter[2]);
		display();
		break;

	//Reset object to initial state
	case 'i':
	case 'I':
		initializeObject();
		display();
		break;

	//Quit application
	case 'q':
	case 'Q':
		exit(0);
		break;
	}
}

//Mouse movement to drag object
void mouseDrag(int x, int y) {
	//Calculate mouse movement
	float worldX, worldY, changeX, changeY;
	screenToWorldCoordinates(x, y, &worldX, &worldY);
	changeX = worldX - previousMouseX;
	changeY = worldY - previousMouseY;

	//Transform object
	glTranslatef(changeX, changeY, 0);
	display();
	previousMouseX = worldX;
	previousMouseY = worldY;
}

//Mouse movement to rotate object
void mouseRotate(int x, int y) {
	//Calculate mouse movement
	float worldX, worldY, changeX, changeY;
	screenToWorldCoordinates(x, y, &worldX, &worldY);
	changeX = worldX - previousMouseX;
	changeY = worldY - previousMouseY;

	//Transform object
	glTranslatef(objectCenter[0], objectCenter[1], objectCenter[2]);
	//rotateX(-changeY / 8);
	glRotatef(-changeY / 8, 1, 0, 0);
	//rotateY(changeX / 8);
	glRotatef(-changeX / 8, 0, 1, 0);
	glTranslatef(-objectCenter[0], -objectCenter[1], -objectCenter[2]);
	display();
	previousMouseX = worldX;
	previousMouseY = worldY;
}

//Mouse click and mouse wheel functions
void click(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		screenToWorldCoordinates(x, y, &previousMouseX, &previousMouseY);
		if (button == GLUT_LEFT_BUTTON) {
			glutMotionFunc(mouseDrag);
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			glutMotionFunc(mouseRotate);
		}
		//Scroll up
		else if (button == 3) {
			//Scale object
			glTranslatef(objectCenter[0], objectCenter[1], objectCenter[2]);
			glScalef(1.05, 1.05, 1.05);
			glTranslatef(-objectCenter[0], -objectCenter[1], -objectCenter[2]);
			display();
		}
		//Scroll down
		else if (button == 4) {
			//Scale object
			glTranslatef(objectCenter[0], objectCenter[1], objectCenter[2]);
			glScalef(.95, .95, .95);
			glTranslatef(-objectCenter[0], -objectCenter[1], -objectCenter[2]);
			display();
		}
	}

	else {
		glutMotionFunc(NULL);
	}

}