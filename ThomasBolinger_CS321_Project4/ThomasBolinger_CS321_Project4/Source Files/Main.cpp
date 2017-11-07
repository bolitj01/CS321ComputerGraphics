#include "../Header Files/FileFunctions.h"
#include "../Header Files/Initialization.h"
#include "../Header Files/VertexFunctions.h"
#include "../Header Files/MatrixFunctions.h"
#include "../Header Files/CallbackFunctions.h"
#include "../Header Files/GlobalVariables.h"
/*
	Thomas Bolinger
	CS321 Project 4
	Perform various geometric transformations on an object and on various viewports 
	using orthographic or perspective projection.
*/

///Global externals defined in GlobalVariables.h
int vertexCount; //number of total vertices
int vertexGroups; //number of groups of vertices
vertex3* vertices; //float array of individual coordinate values
int* vertexDirections; //int array storing the direction of each vertex
int* verticesPerGroup; //integer array storing how many vertices are in each group(shape)

int worldWidth; //width of world coordinates
int worldHeight; //height of world coordinates
int worldDepth; //depth of world coordinates

int worldLeft; //leftmost world coordinate
int worldRight; //rightmost world coordinate
int worldBottom; //bottommost world coordinate
int worldTop; //topmost world coordinate
int worldNear; //nearmost world coordinate
int worldFar; //farmost world coordinate

int screenWidth = 600; //width of viewing screen
int screenHeight = 400; //height of viewing screen

float objectHeight; //height of object(s)
float objectWidth; //width of object(s)
float objectDepth; //depth of object(s)
vertex3 objectCenter; //center vertex of object(s)

float viewportWidth = 300; //width of viewport
float viewportHeight = 200; //height of viewport
float viewportX = (screenWidth - viewportWidth) / 2; //screen X location of viewport
float viewportY = (screenHeight - viewportHeight) / 2; //screen Y location of viewport 

float previousMouseX; //previous mouse x coordinate
float previousMouseY; //previous mouse y coordinate

bool perspectiveOn = false; //For toggling perspective projection
bool fourViewportsOn = false; //For toggling 4 viewports

float eyeX, eyeY, eyeZ, atX, atY, atZ, upX, upY, upZ; //For perspective projection vectors

///Global externals

//Prints all application instructions to console
void displayInstructions() {
	printf("Object Transformation Application\n\n");
	printf("Object key and mouse controls:\n\n");
	printf("\t%-30s%-30s\n", "U, D, L, R", "Move object up, down, left, right");
	printf("\t%-30s%-30s\n", "u, d, l, r:", "Move viewport up, down, left, right");
	printf("\t%-30s%-30s\n", "+, -:", "Scale object up, down");
	printf("\t%-30s%-30s\n", "E, e:", "Scale viewport up, down");
	printf("\t%-30s%-30s\n", "X/x:", "Rotate object on x-axis (+15/-15 degrees)");
	printf("\t%-30s%-30s\n", "Y/y:", "Rotate object on y-axis (+15/-15 degrees)");
	printf("\t%-30s%-30s\n", "Z/z:", "Rotate object on z-axis (+15/-15 degrees)");
	printf("\t%-30s%-30s\n", "Left click drag:", "Move object with mouse");
	printf("\t%-30s%-30s\n", "Right click drag (with mouse):", "Rotate object with mouse");
	printf("\t%-30s%-30s\n", "Mouse wheel up/down", "Scale object with mouse wheel");
	printf("\t%-30s%-30s\n", "O, S, T:", "Orthographic projection front, side, top view");
	printf("\t%-30s%-30s\n", "P:", "Perspective projection of current view");
	printf("\t%-30s%-30s\n", "N, F:", "Move camera nearer, farther");
	printf("\t%-30s%-30s\n", "V:", "Four simultaneous varying views of orthographic and perspective projections");
	printf("\t%-30s%-30s\n", "I:", "Initial state (reset)");
	printf("\t%-30s%-30s\n\n", "Q:", "Quit");
}

void main(int argc, char** argv) {
	
	//Initializations and data reading
	FILE* fp = NULL;
	
	vertexCount = 0;
	vertexGroups = 0;
	vertices = NULL;
	verticesPerGroup = NULL;

	//Display instructions
	displayInstructions();

	char* fileName = promptForFile();
	openFile(fileName, &fp);

	countVerticesInFile(fp, &vertexCount, &vertexGroups);

	//Reopen file to beginning of file
	openFile(fileName, &fp);

	//Read vertex data
	readData(fp, vertexCount, vertexGroups, &verticesPerGroup, &vertices);

	//Set up and create window
	init_window(argc, argv);
	//Initialize other state variables
	other_init();

	initializeViewingVolume();

	//Center object on screen at reasonable scale
	initializeObject();

	//Normalize the vertices to positive world coordinates
	//normalizeVertices();

	

	initializeViewport();
	initializeCamera();
	
	//Assign callback functions
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardControls);
	glutMouseFunc(click);

	//Begin infinite event loop
	glutMainLoop();

	//Clean up memory
	if (vertices != NULL) {
		free(vertices);
	}
	if (verticesPerGroup != NULL) {
		free(verticesPerGroup);
	}
}





