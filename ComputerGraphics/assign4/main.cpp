/*
* Skeleton code for CSE471 Spring 2017
*
* Won-Ki Jeong, wkjeong@unist.ac.kr
*/

#include <stdio.h>
#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <assert.h>


#define  DYNAMIC_CUBEMAP
//#define  TASK1
//#define  STATIC_CUBEMAP




#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "glm\glm\glm.hpp"
//
// Definitions
//

#include "glm\glm\gtx\transform.hpp"
using namespace glm;


class BodyPart
{
public:
	float vertices[48];
	glm::mat4 bodyMatrix;
};


int vert[] = {
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f
};

class Minecraft
{
public:
	Minecraft() {
		buildCharacter();
	}
	BodyPart hand[2];
	BodyPart head;
	BodyPart body;
	BodyPart foot[2];
	const int LEFT_HAND = 0;
	const int RIGHT_HAND = 1;
	const int LEFT_FOOT = 0;
	const int RIGHT_FOOT = 1;


	void initHand(float a[]) {
		for (int i = 0; i < 48; ++i) hand[LEFT_HAND].vertices[i] = a[i];
		for (int i = 0; i < 48; ++i) hand[RIGHT_HAND].vertices[i] = a[i];
	}
	void initFoot(float a[]) {
		for (int i = 0; i < 48; ++i) foot[LEFT_HAND].vertices[i] = a[i];
		for (int i = 0; i < 48; ++i) foot[RIGHT_HAND].vertices[i] = a[i];
	}
	void initHead(float a[]) { for (int i = 0; i < 48; ++i) { head.vertices[i] = a[i]; } }
	void initBody(float a[]) { for (int i = 0; i < 48; ++i) { body.vertices[i] = a[i]; } }

	float matrix[16];
	void showCharacter() {

		glMatrixMode(GL_MODELVIEW);
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		glPushMatrix();

		//head
		glLoadIdentity();	head.bodyMatrix = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
		glMultMatrixf(&head.bodyMatrix[0][0]);
		glMultMatrixf(matrix);
		glBegin(GL_QUADS); for (int i = 0; i < 24; i++) {
			glTexCoord2f(head.vertices[i * 2], head.vertices[i * 2 + 1]); glVertex3f(vert[i * 3 + 0], vert[i * 3 + 1], vert[i * 3 + 2]);
		}
		glEnd();

		//body
		glLoadIdentity(); body.bodyMatrix = glm::translate(glm::vec3(0.0f, -2.0f, 0.0f)); //* glm::scale(mat4(1.0f), vec3(0.9, 1, 0.9));
		glMultMatrixf(&body.bodyMatrix[0][0]); glMultMatrixf(matrix);
		glBegin(GL_QUADS); for (int i = 0; i < 24; i++) {
			glTexCoord2f(body.vertices[i * 2], body.vertices[i * 2 + 1]); glVertex3f(vert[i * 3 + 0], vert[i * 3 + 1], vert[i * 3 + 2]);
		}
		glEnd();
#ifdef DYNAMIC_CUBEMAP
		glPopMatrix();
		return;
#endif // DYNAMIC_CUBEMAP




		//left foot
		glLoadIdentity(); foot[LEFT_FOOT].bodyMatrix = glm::translate(glm::vec3(-0.5f, -3.5f, 0.0f))* glm::scale(mat4(1.0f), vec3(0.2, 1, 0.2)) * glm::rotate(glm::radians(90.0f), vec3(1, 0, 0));
		glMultMatrixf(&foot[LEFT_FOOT].bodyMatrix[0][0]); glMultMatrixf(matrix);
		glBegin(GL_QUADS); for (int i = 0; i < 24; i++) {
			glTexCoord2f(foot[LEFT_FOOT].vertices[i * 2], foot[LEFT_FOOT].vertices[i * 2 + 1]); glVertex3f(vert[i * 3 + 0], vert[i * 3 + 1], vert[i * 3 + 2]);
		}
		glEnd();

		//right foot
		glLoadIdentity(); foot[RIGHT_FOOT].bodyMatrix = glm::translate(glm::vec3(+0.5f, -3.5f, 0.0f))* glm::scale(mat4(1.0f), vec3(0.2, 1, 0.2)) * glm::rotate(glm::radians(90.0f), vec3(1, 0, 0));
		glMultMatrixf(&foot[RIGHT_FOOT].bodyMatrix[0][0]); glMultMatrixf(matrix);
		glBegin(GL_QUADS); for (int i = 0; i < 24; i++) {
			glTexCoord2f(foot[RIGHT_FOOT].vertices[i * 2], foot[RIGHT_FOOT].vertices[i * 2 + 1]); glVertex3f(vert[i * 3 + 0], vert[i * 3 + 1], vert[i * 3 + 2]);
		}
		glEnd();

		//left hand
		glLoadIdentity(); hand[LEFT_HAND].bodyMatrix = glm::translate(glm::vec3(-1.2f, -2.0f, 0.0f))* glm::scale(mat4(1.0f), vec3(0.2, 1.0, 0.2))  * glm::rotate(glm::radians(90.0f), vec3(1, 0, 0));
		glMultMatrixf(&hand[LEFT_HAND].bodyMatrix[0][0]); glMultMatrixf(matrix);
		glBegin(GL_QUADS); for (int i = 0; i < 24; i++) {
			glTexCoord2f(hand[LEFT_HAND].vertices[i * 2], hand[LEFT_HAND].vertices[i * 2 + 1]); glVertex3f(vert[i * 3 + 0], vert[i * 3 + 1], vert[i * 3 + 2]);
		}
		glEnd();

		//right hand
		glLoadIdentity();
		hand[RIGHT_HAND].bodyMatrix = glm::translate(glm::vec3(+1.2f, -2.0f, 0.0f))* glm::scale(mat4(1.0f), vec3(0.2, 1.0, 0.2)) * glm::rotate(glm::radians(90.0f), vec3(1, 0, 0));
		glMultMatrixf(&hand[RIGHT_HAND].bodyMatrix[0][0]); glMultMatrixf(matrix);
		glBegin(GL_QUADS); for (int i = 0; i < 24; i++) {
			glTexCoord2f(hand[RIGHT_HAND].vertices[i * 2], hand[RIGHT_HAND].vertices[i * 2 + 1]); glVertex3f(vert[i * 3 + 0], vert[i * 3 + 1], vert[i * 3 + 2]);
		}
		glEnd();

		glPopMatrix();
	}



	void buildCharacter() {
		float head[] = {
			(float)816 / 1480, (float)588 / 1169,
			(float)1118 / 1480, (float)588 / 1169,
			(float)1118 / 1480, (float)794 / 1169,
			(float)816 / 1480, (float)794 / 1169,
			(float)512 / 1480, (float)588 / 1169,
			(float)512 / 1480, (float)794 / 1169,
			(float)214 / 1480, (float)794 / 1169,
			(float)214 / 1480, (float)588 / 1169,
			(float)816 / 1480, (float)1098 / 1169,
			(float)816 / 1480, (float)794 / 1169,
			(float)1118 / 1480, (float)794 / 1169,
			(float)1118 / 1480, (float)1098 / 1169,
			(float)1118 / 1480, (float)588 / 1169,
			(float)816 / 1480, (float)588 / 1169,
			(float)816 / 1480, (float)286 / 1169,
			(float)1118 / 1480, (float)286 / 1169,
			(float)1424 / 1480, (float)588 / 1169,
			(float)1424 / 1480, (float)794 / 1169,
			(float)1118 / 1480, (float)794 / 1169,
			(float)1118 / 1480, (float)588 / 1169,
			(float)512 / 1480, (float)588 / 1169,
			(float)816 / 1480, (float)588 / 1169,
			(float)816 / 1480, (float)794 / 1169,
			(float)512 / 1480, (float)794 / 1169
		};
		initHead(head);
		float body[] = {
			(float)450 / 1480, (float)246 / 1169,
			(float)258 / 1480, (float)246 / 1169,
			(float)258 / 1480, (float)60 / 1169,
			(float)450 / 1480, (float)60 / 1169,
			(float)640 / 1480, (float)246 / 1169,
			(float)640 / 1480, (float)60 / 1169,
			(float)838 / 1480, (float)60 / 1169,
			(float)838 / 1480, (float)246 / 1169,
			(float)816 / 1480, (float)1098 / 1169,
			(float)816 / 1480, (float)794 / 1169,
			(float)1118 / 1480, (float)794 / 1169,
			(float)1118 / 1480, (float)1098 / 1169,
			(float)258 / 1480, (float)246 / 1169,
			(float)450 / 1480, (float)246 / 1169,
			(float)450 / 1480, (float)442 / 1169,
			(float)258 / 1480, (float)442 / 1169,
			(float)66 / 1480, (float)246 / 1169,
			(float)66 / 1480, (float)60 / 1169,
			(float)258 / 1480, (float)60 / 1169,
			(float)258 / 1480, (float)246 / 1169,
			(float)640 / 1480, (float)246 / 1169,
			(float)450 / 1480, (float)246 / 1169,
			(float)450 / 1480, (float)60 / 1169,
			(float)640 / 1480, (float)60 / 1169,
		};
		initBody(body);
		float hand[] = {
			(float)240 / 1480, (float)918 / 1169,
			(float)170 / 1480, (float)918 / 1169,
			(float)170 / 1480, (float)850 / 1169,
			(float)240 / 1480, (float)850 / 1169,
			(float)312 / 1480, (float)1060 / 1169,
			(float)312 / 1480, (float)1132 / 1169,
			(float)240 / 1480, (float)1132 / 1169,
			(float)240 / 1480, (float)1060 / 1169,
			(float)240 / 1480, (float)1060 / 1169,
			(float)240 / 1480, (float)918 / 1169,
			(float)312 / 1480, (float)918 / 1169,
			(float)312 / 1480, (float)1060 / 1169,
			(float)170 / 1480, (float)1060 / 1169,
			(float)96 / 1480, (float)1060 / 1169,
			(float)96 / 1480, (float)918 / 1169,
			(float)170 / 1480, (float)918 / 1169,
			(float)240 / 1480, (float)1060 / 1169,
			(float)170 / 1480, (float)1060 / 1169,
			(float)240 / 1480, (float)918 / 1169,
			(float)170 / 1480, (float)918 / 1169,
			(float)170 / 1480, (float)1060 / 1169,
			(float)170 / 1480, (float)918 / 1169,
			(float)240 / 1480, (float)918 / 1169,
			(float)240 / 1480, (float)1060 / 1169
		};
		initHand(hand);
		float foot[] = {
			(float)240 / 1480, (float)918 / 1169		,
			(float)170 / 1480, (float)918 / 1169		,
			(float)170 / 1480, (float)850 / 1169		,
			(float)240 / 1480, (float)850 / 1169		,

			(float)312 / 1480, (float)1060 / 1169		,
			(float)312 / 1480, (float)1132 / 1169		,
			(float)240 / 1480, (float)1132 / 1169		,
			(float)240 / 1480, (float)1060 / 1169		,

			(float)240 / 1480, (float)1060 / 1169		,
			(float)240 / 1480, (float)918 / 1169		,
			(float)312 / 1480, (float)918 / 1169		,
			(float)312 / 1480, (float)1060 / 1169		,

			(float)170 / 1480, (float)1060 / 1169		,
			(float)96 / 1480, (float)1060 / 1169		,
			(float)96 / 1480, (float)918 / 1169			,
			(float)170 / 1480, (float)918 / 1169		,

			(float)240 / 1480, (float)1060 / 1169		,
			(float)170 / 1480, (float)1060 / 1169		,
			(float)240 / 1480, (float)918 / 1169		,
			(float)170 / 1480, (float)918 / 1169		,

			(float)170 / 1480, (float)1060 / 1169		,
			(float)170 / 1480, (float)918 / 1169		,
			(float)240 / 1480, (float)918 / 1169		,
			(float)240 / 1480, (float)1060 / 1169
		};
		initFoot(foot);

	}

};



const float M_PI = 3.14159265359;


typedef struct {
	unsigned char x, y, z, w;
} uchar4;
typedef unsigned char uchar;

float matrix[16];

Minecraft steve;


void trackball_ptov(int x, int y, int width, int height, float v[3]);
bool trackLeft = false, trackMiddle = false, trackRight = false;
float LeftX = 0.0f, LeftY = 0.0f, LeftZ = 0.0f, MiddleX = 0.0f, MiddleY = 0.0f, RightY = 0.0f, moveMiddleX = 0.0, moveMiddleY = 0.0, moveRightZ = 1.0f;
float angle = 0.0, axis[3], trans[3];
int programID;
int width, height;
// BMP loader
void LoadBMPFile(uchar4 **dst, int *width, int *height, const char *name);

#define screenSize 1024
#define	imageSize 4

void pressMouseButton(int b, int s, int x, int y), normalize(int a), calcNormals(int a, int b, int c);
void keyboard(unsigned char key, int x, int y), Input(), InitGL();
void mouseMove(int x, int y), Mesh_Init();

mat4 projectionMatrix = mat4(1.0);
mat4 modelViewMatrix = mat4(1.0);

//
// Variables
//

// array to store synthetic cubemap raw image
static GLubyte image1[imageSize][imageSize][4];
static GLubyte image2[imageSize][imageSize][4];
static GLubyte image3[imageSize][imageSize][4];
static GLubyte image4[imageSize][imageSize][4];
static GLubyte image5[imageSize][imageSize][4];
static GLubyte image6[imageSize][imageSize][4];

// texture object handles, FBO handles
GLuint cube_tex, color_tex , robot_tex , spongebob_tex;
GLuint anakin_tex, steve_tex, other_tex;
GLuint fb, depth_rb;

//
// Functions
//

// create synthetic data for 4static cubemap
void makeSyntheticImages(void)
{
	int i, j, c;

	for (i = 0; i < imageSize; i++) {
		for (j = 0; j < imageSize; j++) {
			c = ((((i & 0x1) == 0) ^ ((j & 0x1)) == 0)) * 255;
			image1[i][j][0] = (GLubyte)c;
			image1[i][j][1] = (GLubyte)c;
			image1[i][j][2] = (GLubyte)c;
			image1[i][j][3] = (GLubyte)255;

			image2[i][j][0] = (GLubyte)c;
			image2[i][j][1] = (GLubyte)c;
			image2[i][j][2] = (GLubyte)0;
			image2[i][j][3] = (GLubyte)255;

			image3[i][j][0] = (GLubyte)c;
			image3[i][j][1] = (GLubyte)0;
			image3[i][j][2] = (GLubyte)c;
			image3[i][j][3] = (GLubyte)255;

			image4[i][j][0] = (GLubyte)0;
			image4[i][j][1] = (GLubyte)c;
			image4[i][j][2] = (GLubyte)c;
			image4[i][j][3] = (GLubyte)255;

			image5[i][j][0] = (GLubyte)255;
			image5[i][j][1] = (GLubyte)c;
			image5[i][j][2] = (GLubyte)c;
			image5[i][j][3] = (GLubyte)255;

			image6[i][j][0] = (GLubyte)c;
			image6[i][j][1] = (GLubyte)c;
			image6[i][j][2] = (GLubyte)255;
			image6[i][j][3] = (GLubyte)255;
		}
	}
}

void init(void)
{
	// You need to ues glew
	glewInit();

	GLfloat diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };

	glClearColor(1.0, 1.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	// make synthetic cubemap data
	//makeSyntheticImages();

	//
	// Creating a 2D texture from image
	// 
	int width, height;
	uchar4 *dst1;
	LoadBMPFile(&dst1, &width, &height, "anakin_papercraft.bmp"); // this is how to load image
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); glGenTextures(1, &anakin_tex); glBindTexture(GL_TEXTURE_2D, anakin_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst1);

	uchar4 *dst2;
	LoadBMPFile(&dst2, &width, &height, "steve.bmp"); // this is how to load image
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); glGenTextures(1, &steve_tex); glBindTexture(GL_TEXTURE_2D, steve_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst2);
	

	uchar4 *dst3;
	LoadBMPFile(&dst3, &width, &height, "hah.bmp"); // this is how to load image
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); glGenTextures(1, &robot_tex); glBindTexture(GL_TEXTURE_2D, robot_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst3);


	uchar4 *dst4;
	LoadBMPFile(&dst4, &width, &height, "pikachu.bmp"); // this is how to load image
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); glGenTextures(1, &spongebob_tex); glBindTexture(GL_TEXTURE_2D, spongebob_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst4);


	//
	// creating cube map texture (either static or dynamic)
	//

#ifdef STATIC_CUBEMAP
	// create static cubemap from synthetic data
	glGenTextures(1, &cube_tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_tex);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	//uchar4 *dst;
	//LoadBMPFile(&dst, &width, &height, "mob.bmp"); // this is how to load image

	std::cout << width << " " << height << "\n";
	
	

	uchar4 *cube1;
	LoadBMPFile(&cube1, &width, &height, "A.bmp"); // this is how to load image
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cube1);
	uchar4 *cube4;
	LoadBMPFile(&cube4, &width, &height, "B.bmp"); // this is how to load image
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cube4);

	uchar4 *cube2;
	LoadBMPFile(&cube2, &width, &height, "C.bmp"); // this is how to load image
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cube2);
	
	uchar4 *cube5;
	LoadBMPFile(&cube5, &width, &height, "D.bmp"); // this is how to load image
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cube5);

	uchar4 *cube3;
	LoadBMPFile(&cube3, &width, &height, "E.bmp"); // this is how to load image
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cube3);
	
	uchar4 *cube6;
	LoadBMPFile(&cube6, &width, &height, "F.bmp"); // this is how to load image
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, cube6);
	

	/*
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, imageSize, imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, imageSize, imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, imageSize, imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image3);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, imageSize, imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image4);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, imageSize, imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image5);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, imageSize, imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image6);
	*/
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);



#endif


	// generate cubemap on-the-fly
#ifdef DYNAMIC_CUBEMAP
	//RGBA8 Cubemap texture, 24 bit depth texture, 256x256
	glGenTextures(1, &cube_tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_tex);
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	const int scene_size = 200;

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, scene_size, scene_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, scene_size, scene_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, scene_size, scene_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, scene_size, scene_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, scene_size, scene_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, scene_size, scene_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);


	//
	// creating FBO and attach cube map texture
	//

	//-------------------------
	glGenFramebuffersEXT(1, &fb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	//Attach one of the faces of the Cubemap texture to this FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_CUBE_MAP_POSITIVE_X, cube_tex, 0);
	//-------------------------
	glGenRenderbuffersEXT(1, &depth_rb);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_rb);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, 200, 200);
	//-------------------------
	//Attach depth buffer to FBO
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_rb);
	//-------------------------
	//Does the GPU support current FBO configuration?
	GLenum status;
	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch (status)
	{
	case GL_FRAMEBUFFER_COMPLETE_EXT:
		std::cout << "good" << std::endl; break;
	default:
	//	assert(false); 
		break;
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

#endif
}
float a = 0;
float b = 0;
bool up = true;

void idle()
{
	// do something for animation here b/c this will be called when idling
	a += 3;
	if (up) {
		b += 0.02;
		if (b >= 3.5) {
			up = false;
		}
	}
	else {
		b -= 0.02;
		if (b <= -3.5) {
			up = true;
		}
	}
	glutPostRedisplay();
}

// dynamically update cubemap
void update_cubemap()
{
	// bind FBO to render to texture
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	glMatrixMode(GL_MODELVIEW);	glPushMatrix();
	glMatrixMode(GL_PROJECTION);	glPushMatrix();
	glPushAttrib(GL_VIEWPORT_BIT); glViewport(0, 0, 200, 200);
	for (int face = 0; face < 6; face++) {
		// render to +x face
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, cube_tex, 0);
			
		// clear
		glClearColor(1, 0, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90, 1, 0.001, 1000);
		gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(b, 0, 0);
		glRotatef(a, 0, 1, 0);

		glColor3f(1, 1, 0.3);

		if (face == 2 || face == 3) {
			continue;

		}
		glActiveTexture(GL_TEXTURE0);
		if (face == 2) {
			glBindTexture(GL_TEXTURE_2D, anakin_tex);
		//	return;
		}
		else
		if (face == 4) {
			glBindTexture(GL_TEXTURE_2D, robot_tex);
		}
		else if (face == 0){
			glBindTexture(GL_TEXTURE_2D, steve_tex);
		}
		else if (face == 1) {
			glBindTexture(GL_TEXTURE_2D, spongebob_tex);
		}
		

		glEnable(GL_TEXTURE_2D);
		steve.showCharacter();
		
		glDisable(GL_TEXTURE_2D);
		
	}

	//popMatrix
	glMatrixMode(GL_MODELVIEW);	glPopMatrix();
	glMatrixMode(GL_PROJECTION);	glPopMatrix();
	glPopAttrib();

	// unbind FBO
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}







void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 0, 1);
	// update dynamic cubemap per frame
#ifdef TASK1

	if (trackLeft) {
		glMatrixMode(GL_MODELVIEW); glGetFloatv(GL_MODELVIEW_MATRIX, matrix); glLoadIdentity(); glRotatef(angle, axis[0], axis[1], axis[2]); glMultMatrixf(matrix);
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, robot_tex);
	steve.showCharacter();
	glDisable(GL_TEXTURE_2D);
#endif // TASK1


#ifdef DYNAMIC_CUBEMAP

	update_cubemap();

	
	
	if (trackLeft) {
		glMatrixMode(GL_MODELVIEW); glGetFloatv(GL_MODELVIEW_MATRIX, matrix); glLoadIdentity(); glRotatef(angle, axis[0], axis[1], axis[2]); glMultMatrixf(matrix);
	}
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_tex);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	//glLoadIdentity();
	//glRotatef(90, 1, 1, 1);
				

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutSolidSphere(5, 50, 50);
	//glutSolidTeapot(4);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_CUBE_MAP);
	
	
	
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, steve_tex);
	glLoadIdentity();
	glTranslatef(-10, 0, 0);
	glTranslatef(0, 0, 1.5* b);
	glRotatef(-a + 90, 0, 1, 0);
	steve.showCharacter();

	glBindTexture(GL_TEXTURE_2D, spongebob_tex);
	glLoadIdentity();
	glTranslatef(10, 0, 0);
	glTranslatef(0, 0, -1.5* b);
	glRotatef(-a + 270, 0, 1, 0);
	steve.showCharacter();

	glBindTexture(GL_TEXTURE_2D, robot_tex);
	glLoadIdentity();
	glTranslatef(0, 0, 10);
	glTranslatef(1.5*b, 0, 0);
	glRotatef(-a + 180, 0, 1, 0);
	steve.showCharacter();

	glBindTexture(GL_TEXTURE_2D, anakin_tex);
	glLoadIdentity();
	glTranslatef(0, 0, -10);
	glTranslatef(-b*2, 0, 0);
	glRotatef(-a, 0, 1, 0);
	steve.showCharacter();
	
	glDisable(GL_TEXTURE_2D);


	


#endif

	// render something here...
#ifdef STATIC_CUBEMAP
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (GLfloat)width / (GLfloat)height, 4, 300.0);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	if (trackLeft) {
		glMatrixMode(GL_MODELVIEW); glGetFloatv(GL_MODELVIEW_MATRIX, matrix); glLoadIdentity(); glRotatef(angle, axis[0], axis[1], axis[2]); glMultMatrixf(matrix);
	}

//	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_CUBE_MAP);

	//glBindTexture(GL_TEXTURE_CUBE_MAP, cube_tex);
	//glutSolidTorus(0.2 , 0.5, 20 , 20);
	//glutSolidCube(1.0);


	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_tex); glutSolidTorus(0.25 , 0.5, 30 , 30);
	glMatrixMode(GL_MODELVIEW); 
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix); 
	glLoadIdentity();
	glutSolidCube(4.0);
	glMultMatrixf(matrix);
#endif



	glutSwapBuffers();
}

void reshape(int w, int h)
{
	width = w, height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, float(w) / h, 0.001, 10000);
	gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

#ifdef TASK1
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, float(w) / h, 0.001, 10000);
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	//	glScalef(0.2, 0.2, 0.2);
#endif // TASK1




}

void keyboard(unsigned char key, int x, int y)
{

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenSize, screenSize);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(mouseMove);
	glutMouseFunc(pressMouseButton);


	glutMainLoop();
	return 0;
}




void mouseMove(int x, int y) {
	float currentPosition[3], distanceMovedX, distanceMovedY, distanceMovedZ;
	trackball_ptov(x, y, width, height, currentPosition);
	if (trackLeft) {
		distanceMovedX = currentPosition[0] - LeftX, distanceMovedY = currentPosition[1] - LeftY, distanceMovedZ = currentPosition[2] - LeftZ;
		if (distanceMovedX || distanceMovedY || distanceMovedZ)
		{
			angle = 90.0 * sqrt(distanceMovedX*distanceMovedX + distanceMovedY*distanceMovedY + distanceMovedZ *distanceMovedZ);
			axis[0] = LeftY * currentPosition[2] - LeftZ * currentPosition[1];
			axis[1] = LeftZ * currentPosition[0] - LeftX * currentPosition[2];
			axis[2] = LeftX * currentPosition[1] - LeftY * currentPosition[0];
			LeftX = currentPosition[0], LeftY = currentPosition[1], LeftZ = currentPosition[2];
		}
	}


	glutPostRedisplay();


}


float tempUse[3];
void pressMouseButton(int b, int s, int x, int y)
{

	if (b == GLUT_LEFT_BUTTON)
	{
		if (s == GLUT_DOWN) {

			trackLeft = true;
			trackball_ptov(x, y, width, height, tempUse);
			LeftX = tempUse[0], LeftY = tempUse[1], LeftZ = tempUse[2];
		}
		else
			if (s == GLUT_UP) {
				trackLeft = false;
			}
	}
}
void trackball_ptov(int x, int y, int W, int H, float v[3])
{
	float distance, a;
	v[1] = (H - 2.0F*y) / H, v[0] = (2.0F*x - W) / W;
	distance = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[2] = cos(M_PI * ((distance < 1.0F) ? distance : 1.0F) / 2.0);
	a = 1.0F / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] *= a, v[1] *= a, v[2] *= a;
}
