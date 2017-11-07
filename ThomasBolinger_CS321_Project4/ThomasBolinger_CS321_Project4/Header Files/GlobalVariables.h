#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

//Define 3D vertex data type
typedef GLfloat vertex3[3];

//External globals initialized in Main.cpp
extern int vertexCount;
extern int vertexGroups;
extern vertex3* vertices;
extern int* verticesPerGroup;
extern int* vertexDirections;

extern int worldWidth, worldHeight, worldDepth;
extern int worldLeft, worldRight, worldBottom, worldTop, worldNear, worldFar;

extern int screenWidth, screenHeight;

extern float objectHeight, objectWidth, objectDepth;
extern vertex3 objectCenter;

extern float viewportWidth, viewportHeight;
extern float viewportX, viewportY;

extern float previousMouseX, previousMouseY;

extern bool perspectiveOn;
extern bool fourViewportsOn;

extern float eyeX, eyeY, eyeZ, atX, atY, atZ, upX, upY, upZ;

#endif