#include "Initialization.h"

//All the functions for intializing openGL or data

void initWindow(int &argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Soccer Simulator");
}

//Set up the dynamics world based on bullet physics
void initializePhysicsWorld() {
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));
}

void initializeViewingVolume() {
	worldLeft = -15;
	worldRight = 15;
	worldBottom = -15;
	worldTop = 15;
	worldNear = 15;
	worldFar = 10000;
}

void initializeCamera() {
	cameraLocation[0] = 0;
	cameraLocation[1] = ballRadius;
	cameraLocation[2] = -150;

	cameraAtVertex[0] = 0;
	cameraAtVertex[1] = ballRadius;
	cameraAtVertex[2] = 0;

	cameraUpVector[0] = 0;
	cameraUpVector[1] = 1;
	cameraUpVector[2] = 0;

	xCameraRot = -5;
	yCameraRot = 0;
}

void initializeBallGoal() {
	goalZLocation = 1500;
}

