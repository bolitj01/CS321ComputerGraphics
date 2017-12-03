#ifndef DRAW_MODELS_H
#define DRAW_MODELS_H
#include "GlobalVariables.h"

//Counts number of vector and face lines in the file
void countLines();
void createGoalData();
void createBallData();
void createTargetData();
void createArrayS();
void drawFileG();
void drawFileB();
void drawFileS();
void drawTarget();
double* getObjectParameters(int vertexCount, double* vertices);

#endif