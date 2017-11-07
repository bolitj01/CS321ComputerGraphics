#ifndef DRAW_MODELS_H
#define DRAW_MODELS_H
#include <freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>


//Counts number of vector and face lines in the file
void countLines();
void createArrayG();
void createArrayB();
void createArrayS();
void drawFileG();
void drawFileB();
void drawFileS();

#endif