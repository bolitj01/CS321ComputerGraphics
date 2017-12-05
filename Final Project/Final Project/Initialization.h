#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "GlobalVariables.h"
#include "UtilityFunctions.h"

//Functions associated with initilization of the environment or data

void initWindow(int &argc, char **argv);

void initializePhysicsWorld();
void initializeViewingVolume();
void initializeCamera();
void initializeLight();



#endif // !INITIALIZATION_H

