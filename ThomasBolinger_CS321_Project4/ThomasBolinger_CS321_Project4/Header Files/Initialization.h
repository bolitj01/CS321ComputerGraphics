//Header file for OpenGL and GLUT intialization functions
#ifndef GLINITIALIZATION_H
#define GLINITIALIZATION_H

#include <gl/freeglut.h>
#include "GlobalVariables.h"
#include "CallbackFunctions.h"

//Glut initialization functions and other initialization functions to set up environment. 
//Function descriptions are in the .cpp file
void init_window(int argc, char** argv);
void other_init();

void initializeObject();
void initializeViewingVolume();
void initializeViewport();
void initializeCamera();

#endif // !GLINITIALIZATION_H




