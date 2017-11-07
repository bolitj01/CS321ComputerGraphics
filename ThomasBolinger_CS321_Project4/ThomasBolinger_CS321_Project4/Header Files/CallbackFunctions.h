#ifndef CALLBACK_FUNCTIONS
#define CALLBACK_FUNCTIONS

#include "Initialization.h"
//#include "MatrixFunctions.h"
#include "VertexFunctions.h"
#include "GlobalVariables.h"

void display();
void updateViewingVolume(float scaleFactor, bool updateX, bool updateY, bool updateZ);
void setProjection();
void setCamera();
void frontCamera();
void sideCamera();
void topCamera();
void setViewport();
void drawObject();
void keyboardControls(unsigned char key, int x, int y);
void click(int button, int state, int x, int y);
void mouseDrag(int x, int y);
void mouseRotate(int x, int y);

#endif // !CALLBACK_FUNCTIONS

