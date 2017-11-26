#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "GlobalVariables.h"

//Functions associated with initilization of the environment or data

void initWindow(int &argc, char **argv);

void initializePhysicsWorld();

void initializeViewingVolume();
void initializeCamera();



#endif // !INITIALIZATION_H

