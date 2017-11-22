#ifndef CALLBACKFUNCTIONS_H
#define CALLBACKFUNCTIONS_H
#include "GlobalVariables.h"
#include "UtilityFunctions.h"
#include "DrawModels.h"
#include "Initialization.h"

//All functions associated with openGL callback functions. Function descriptions are in .cpp file
void display(void);
void mouseClick(int button, int state, int x, int y);
void mouseCameraRotation(int x, int y);
void keyPress(unsigned char key, int x, int y);


#endif