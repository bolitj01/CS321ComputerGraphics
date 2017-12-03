#include "Initialization.h"

//All the functions for intializing openGL or data

void initWindow(int &argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	//Get full screen size
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	screenWidth = desktop.right;
	screenHeight = desktop.bottom;
	//Create full screen window
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Soccer Simulator");
}

//Set up the dynamics world based on bullet physics
void initializePhysicsWorld() {
	//set up world
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));

	//Create ground
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

	groundRigidBody->setRestitution(.7);
	groundRigidBody->setFriction(.6);
	groundRigidBody->setRollingFriction(.6);
	groundRigidBody->setDamping(.5, 0);

	dynamicsWorld->addRigidBody(groundRigidBody);

	float x = (goalWidth * .2 + goalBottomCenter[0]);
	float z = (goalDepth * .72 + goalBottomCenter[2]);
	float y = goalHeight / 3;
	float goalThickness = goalWidth / 50;
	float backPadding = 100;

	//Create goal mesh

	//Bottom left front
	goalMesh[0] = btVector3(-x, 0, -z);
	//Bottom left back
	goalMesh[1] = btVector3(-x, 0, z);
	//Top left back
	goalMesh[2] = btVector3(-x, y, z);
	//Top left front
	goalMesh[3] = btVector3(-x, y, -z);
	//Top right front
	goalMesh[4] = btVector3(x, y, -z);
	//Top right back
	goalMesh[5] = btVector3(x, y, z);
	//Bottom right back
	goalMesh[6] = btVector3(x, 0, z);
	//Bottom right front
	goalMesh[7] = btVector3(x, 0, -z);

	btCollisionShape* goalSideWall = new btBoxShape(btVector3(goalThickness, y, goalDepth));
	btCollisionShape* goalTopWall = new btBoxShape(btVector3(x * 2, goalThickness, goalDepth));
	btCollisionShape* goalBackWall = new btBoxShape(btVector3(x * 2, y, goalThickness));

	btConvexHullShape* goalLeftHull = new btConvexHullShape();
	goalLeftHull->addPoint(goalMesh[0]);
	goalLeftHull->addPoint(goalMesh[1]);
	goalLeftHull->addPoint(goalMesh[2]);
	goalLeftHull->addPoint(goalMesh[3]);

	btConvexHullShape* goalTopHull = new btConvexHullShape();
	goalTopHull->addPoint(goalMesh[2]);
	goalTopHull->addPoint(goalMesh[3]);
	goalTopHull->addPoint(goalMesh[4]);
	goalTopHull->addPoint(goalMesh[5]);

	btConvexHullShape* goalRightHull = new btConvexHullShape();
	goalRightHull->addPoint(goalMesh[4]);
	goalRightHull->addPoint(goalMesh[5]);
	goalRightHull->addPoint(goalMesh[6]);
	goalRightHull->addPoint(goalMesh[7]);

	btConvexHullShape* goalBackHull = new btConvexHullShape();
	goalBackHull->addPoint(goalMesh[1]);
	goalBackHull->addPoint(goalMesh[2]);
	goalBackHull->addPoint(goalMesh[5]);
	goalBackHull->addPoint(goalMesh[6]);

	goalLeftHull->recalcLocalAabb();
	goalRightHull->recalcLocalAabb();
	goalTopHull->recalcLocalAabb();
	goalBackHull->recalcLocalAabb();

	//Set collision margins
	float collisionMargin = 5;
	goalLeftHull->setMargin(collisionMargin);
	goalRightHull->setMargin(collisionMargin);
	goalTopHull->setMargin(collisionMargin);
	goalBackHull->setMargin(collisionMargin);

	//Create goal left side hull
	btDefaultMotionState* goalLeftMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, goalZLocation)));
	btRigidBody::btRigidBodyConstructionInfo
		goalLeftRigidBodyCI(0, goalLeftMotionState, goalLeftHull, btVector3(0, 0, 0));
	btRigidBody* goalLeftRigidBody = new btRigidBody(goalLeftRigidBodyCI);

	//Create goal top side hull
	btDefaultMotionState* goalTopMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, goalZLocation)));
	btRigidBody::btRigidBodyConstructionInfo
		goalTopRigidBodyCI(0, goalTopMotionState, goalTopHull, btVector3(0, 0, 0));
	btRigidBody* goalTopRigidBody = new btRigidBody(goalTopRigidBodyCI);

	//Create goal right side hull
	btDefaultMotionState* goalRightMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, goalZLocation)));
	btRigidBody::btRigidBodyConstructionInfo
		goalRightRigidBodyCI(0, goalRightMotionState, goalRightHull, btVector3(0, 0, 0));
	btRigidBody* goalRightRigidBody = new btRigidBody(goalRightRigidBodyCI);

	//Create goal back side hull
	btDefaultMotionState* goalBackMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, goalZLocation + goalDepth / 2)));
	btRigidBody::btRigidBodyConstructionInfo
		goalBackRigidBodyCI(0, goalBackMotionState, goalBackHull, btVector3(0, 0, 0));
	btRigidBody* goalBackRigidBody = new btRigidBody(goalBackRigidBodyCI);

	goalLeftRigidBody->setRestitution(.4);
	goalRightRigidBody->setRestitution(.4);
	goalTopRigidBody->setRestitution(.4);
	goalBackRigidBody->setRestitution(0);


	//Add goal parts to dynamics world
	
	dynamicsWorld->addRigidBody(goalLeftRigidBody);
	dynamicsWorld->addRigidBody(goalRightRigidBody);
	dynamicsWorld->addRigidBody(goalTopRigidBody);
	dynamicsWorld->addRigidBody(goalBackRigidBody);

	//Create target hull
	btConvexHullShape* targetHull = new btConvexHullShape();
	for (int i = 0; i < 9; i++) {
		targetHull->addPoint(btVector3(verticeArrTarget[i][0], verticeArrTarget[i][1], verticeArrTarget[i][2]));
	}

	targetHull->setMargin(collisionMargin);
	targetHull->setLocalScaling(btVector3(targetScale, targetScale, targetScale / 3));
	calculateNewTargetPosition();

	btDefaultMotionState* targetMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), targetLocation));
	btScalar targetMass = .001;
	btVector3 targetInertia(0, 0, 0);
	targetHull->calculateLocalInertia(targetMass, targetInertia);
	btRigidBody::btRigidBodyConstructionInfo targetRigidBodyCI(targetMass, targetMotionState, targetHull, targetInertia);
	targetRigidBody = new btRigidBody(targetRigidBodyCI);

	//Need to change target forces in real time
	targetRigidBody->setActivationState(DISABLE_DEACTIVATION);

	dynamicsWorld->addRigidBody(targetRigidBody);
	dynamicsWorld->updateSingleAabb(targetRigidBody); //Maybe need targetHull instead

	//Set zero gravity for target
	targetRigidBody->setGravity(btVector3(0, 0, 0));

	//Create ball 
	btCollisionShape* ballShape = new btSphereShape(1);
	ballShape->setMargin(collisionMargin);

	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, ballStartingHeightOffGround + ballRadius, 0)));
	btScalar ballMass = 4;
	btVector3 ballInertia(0, 0, 0);
	ballShape->calculateLocalInertia(ballMass, ballInertia);
	btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(ballMass, ballMotionState, ballShape, ballInertia);
	ballRigidBody = new btRigidBody(ballRigidBodyCI);

	//Set initial ball parameters
	ballKickUpAngle = 25;
	ballKickTurnAngle = 0;
	ballVelocity = btVector3(0, 0, 0);

	ballRigidBody->setLinearVelocity(ballVelocity);
	ballRigidBody->setRestitution(.9);
	ballRigidBody->setFriction(.4);
	ballRigidBody->setRollingFriction(.4);
	ballRigidBody->setDamping(0, 1);

	//Needed to change ball forces in real time and reset
	ballRigidBody->setActivationState(DISABLE_DEACTIVATION);

	dynamicsWorld->addRigidBody(ballRigidBody);
}
 
void initializeViewingVolume() {
	//Set scale of world to be within reasonable bullet units
	worldScaleToBullet = 1 / ballRadius;

	worldLeft = -15 * worldScaleToBullet;
	worldRight = 15 * worldScaleToBullet;
	worldBottom = -15 * worldScaleToBullet;
	worldTop = 15 * worldScaleToBullet;
	worldNear = 15 * worldScaleToBullet;
	worldFar = 10000;

	goalZLocation = 1500;
	goalScale = 4.0 / 10;
	ballStartingHeightOffGround = .5;
}

void initializeCamera() {
	cameraLocation[0] = 0;
	cameraLocation[1] = 1;
	cameraLocation[2] = -17;

	cameraAtVertex[0] = 0;
	cameraAtVertex[1] = 1;
	cameraAtVertex[2] = 0;

	cameraUpVector[0] = 0;
	cameraUpVector[1] = 1;
	cameraUpVector[2] = 0;

	xCameraRot = -6;
	yCameraRot = 0;
}
