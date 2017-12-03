#include "TextureMapping.h"

void readImage(char* fileName)
/*reads the image file assumes ppm format*/
{

	int w, h, max;
	int i, j;
	unsigned int r, g, b;
	int k;
	char ch;
	FILE *fp;

	fp = fopen(fileName, "r");

	printf("filename = %s\n", fileName);

	/*read the header*/

	fscanf(fp, "P%c\n", &ch);
	if (ch != '3') {
		fprintf(stderr, "Only ascii mode 3 channel PPM files");
		exit(-1);
	}

	/*strip comment lines*/
	ch = getc(fp);
	while (ch == '#') {
		do {
			ch = getc(fp);
		} while (ch != '\n');
		ch = getc(fp);
	}
	ungetc(ch, fp);

	/*read the width*/
	fscanf(fp, "%d", &w);

	/*read the height*/
	fscanf(fp, "%d", &h);

	/*max intensity - not used here*/
	fscanf(fp, "%d", &max);

	/*width and height must be powers of 2 - taking the simple option
	here of finding the max power of 2 <= w and h*/

	ImgWidth = w;
	ImgHeight = h;

	printf("Width = %d, Height = %d\n", ImgWidth, ImgHeight);

	Image = (Pixel *)malloc(ImgWidth*ImgHeight * sizeof(Pixel));


	for (i = 0; i<ImgHeight; ++i) {
		for (j = 0; j<ImgWidth; ++j) {
			fscanf(fp, "%d %d %d", &r, &g, &b);
			k = i*ImgWidth + j; /*ok, can be more efficient here!*/
			(*(Image + k))[0] = (GLubyte)r;
			(*(Image + k))[1] = (GLubyte)g;
			(*(Image + k))[2] = (GLubyte)b;
		}
		/*better scan to the end of the row*/
		for (j = ImgWidth; j<w; ++j) fscanf(fp, "%c %c %c", &r, &g, &b);
	}
	fclose(fp);
}


void initialiseTextures(char* fileName)
{
	GLint level = 0;      /*only one level - no level of detail*/
	GLint components = 3; /*3 means R, G, and B components only*/
	GLint border = 0;     /*no border around the image*/

						  /*read the image file*/
	readImage(fileName);

	/*each pixelrow on a byte alignment boundary*/
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/*define information about the image*/
	glTexImage2D(GL_TEXTURE_2D, level, components,
		(GLsizei)ImgWidth, (GLsizei)ImgHeight,
		border, GL_RGB, GL_UNSIGNED_BYTE, Image);

	/*ensures that image is not wrapped*/
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	/*chooses mapping type from texels to pixels*/
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	/*this says for minification and magnfication choose texel that
	GL_NEAREST chooses the texel nearest the centre of the pixel
	is nearest to the centre of the pixel, rather than GL_LINEAR which
	performs a linear interpolation on the 4 surrounding texels*/

	/*GL_DECAL - this says overwrite pixel with texture colour*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	/*an alternative is GL_MODULATE which modulates the lighting
	by the texel value by multiplication*/

	/*this enables texturing*/
	glEnable(GL_TEXTURE_2D);
}

void bindTextures() {
	glGenTextures(1, texName);
	/*glBindTexture(GL_TEXTURE_2D, texName[0]);
	initialiseTextures("main.ppm");

	glBindTexture(GL_TEXTURE_2D, texName[1]);
	initialiseTextures("ground.ppm");

	glBindTexture(GL_TEXTURE_2D, texName[2]);
	initialiseTextures("field.ppm");*/

	glBindTexture(GL_TEXTURE_2D, texName[3]);
	initialiseTextures("soccerMap3.ppm");

	/*glBindTexture(GL_TEXTURE_2D, texName[4]);
	initialiseTextures("lampTexture.ppm");*/

}
