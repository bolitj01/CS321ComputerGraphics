#ifndef INTERACTION_H
#define INTERACTION_H
#include <freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyPress(unsigned char key, int x, int y);


#endif