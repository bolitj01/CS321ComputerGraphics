#ifndef DRAW_MODELS_H
#define DRAW_MODELS_H
#include "GlobalVariables.h"

//Counts number of vector and face lines in the file
void countLines();
void createGoalData();
void createBallData();
void createLampData();
void createTargetData();
void createStadiumData();
void drawFileG();
void drawFileB();
void drawFileL();
void drawFileS();
void drawTarget();
float* getObjectParameters(int vertexCount, float* vertices);

#endif