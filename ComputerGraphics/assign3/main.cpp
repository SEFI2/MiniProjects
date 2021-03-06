/*
 * Skeleton code for CSE471 Spring 2017
 *
 * Won-Ki Jeong, wkjeong@unist.ac.kr
 */

#include <stdio.h>
#include <GL/glew.h>
#include <Windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cstdio>

#include <assert.h>
#include <string>
#include "textfile.h"
#include <cmath>
#include <math.h>


using namespace std;

void Mesh_Init();

void Input();

// Shader programs
GLuint p;

// light position
float width = 600, height = 600, winWidth = 600, winHeight = 600;
float angle = 0.0, axis[3], trans[3];

float lpos[4] = {2,-4,3,0};
float *vertex, *normals;
int *indices;
int  numVertex, numIndicies;
GLuint vertexVBO, indexVBO;
void trackball_ptov(int x, int y, int width, int height, float v[3]);
bool trackLeft = false, trackMiddle = false, trackRight = false;
float LeftX = 0.0f, LeftY = 0.0f, LeftZ = 0.0f, MiddleX = 0.0f, MiddleY = 0.0f, RightY = 0.0f, moveMiddleX = 0.0, moveMiddleY = 0.0, moveRightZ = 1.0f;
void pressMouseButton(int b, int s, int x, int y), normalize(int a), calcNormals(int a, int b, int c);
void keyboard(unsigned char key, int x, int y), Input();
int level = 1;
int levelID;

void mouseMove(int x, int y);


const float M_PI = 3.1415926535897;

float zoom = 0.2;

void draw_cube()
{
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 0, 0);

	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 0);

	glVertex3f(0, 1, 1);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 1);

	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 1);

	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 0);

	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 1, 1);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);

	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 1);

	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 0, 1);

	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 0);

	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 1);
	glEnd();
}


void changeSize(int w, int h) {

	if(h == 0) h = 1;
	winWidth = w;
	winHeight = h;
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}


void keyboard(unsigned char key, int x, int y)
{
	if(key == 'p') {
		// ToDo
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity(); 
	}
	if (key == '0') {
		level = 0;
	}if (key == '1') {
		level = 1;
	}
	if (key == '2') {
		level = 2;
	}
	if (key == '3') {
		level = 3;
	}
	if (key == '4') {
		level = 4;
	}
	glutPostRedisplay();
}

float matrix[16];


void renderScene(void) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	if (trackLeft)
	{
		glMatrixMode(GL_MODELVIEW);
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		glLoadIdentity();
		glRotatef(angle, axis[0], axis[1], axis[2]);
		glMultMatrixf(matrix);
	}

	if (trackMiddle)
	{
		glMatrixMode(GL_MODELVIEW);
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		glLoadIdentity();
		glTranslatef(moveMiddleX / 4.0f, -moveMiddleY / 4.0f, 0.0f);
		glMultMatrixf(matrix);

	}
	if (trackRight)
	{
		glMatrixMode(GL_MODELVIEW);
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		glLoadIdentity();
		if (zoom < 0) glScalef(0.95, 0.95, 0.95);
		else glScalef(1.05, 1.05, 1.05);
		glMultMatrixf(matrix);
	}

	glUniform1i(levelID , level);

	//glDrawElements(GL_TRIANGLES, 3 * numIndicies, GL_UNSIGNED_INT, 0);
	draw_cube();
	glutSwapBuffers();
}

void idle()
{
	// glutPostRedisplay();
}


int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("CSE471 - Assignment 3");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(mouseMove);
	glutMouseFunc(pressMouseButton);

	glutIdleFunc(idle);

	glEnable(GL_DEPTH_TEST);
	glewInit();

	//gluLookAt(0, 0, 0.1, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-1, 1, -1, 1, 1, -1);

	glOrtho(-1, 1, -1, 1, 3, -3);
	
	
	
	Input();
	Mesh_Init();
	
	glClearColor(1.0,1.0,0.0,1.0);

	//glewInit();
	if (glewIsSupported("GL_VERSION_3_3"))
		printf("Ready for OpenGL 3.3\n");
	else {
		printf("OpenGL 3.3 is not supported\n");
		return 0;
	}

	// Create shader program
	p = createGLSLProgram( "ex.vert", "ex.geom", "ex.frag" ); 
	
	levelID = glGetUniformLocation(p, "level");

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}


void normalize(int a) {
	float len = sqrt(vertex[a * 6 + 3] * vertex[a * 6 + 3] + vertex[a * 6 + 4] * vertex[a * 6 + 4] + vertex[a * 6 + 5] * vertex[a * 6 + 5]);
	vertex[a * 6 + 3] /= len;
	vertex[a * 6 + 4] /= len;
	vertex[a * 6 + 5] /= len;
}

void calcNormals(int a, int b, int c) {
	float vec1X = vertex[b * 6] - vertex[a * 6];
	float vec1Y = vertex[b * 6 + 1] - vertex[a * 6 + 1];
	float vec1Z = vertex[b * 6 + 2] - vertex[a * 6 + 2];

	float vec2X = vertex[c * 6] - vertex[a * 6];
	float vec2Y = vertex[c * 6 + 1] - vertex[a * 6 + 1];
	float vec2Z = vertex[c * 6 + 2] - vertex[a * 6 + 2];

	float vec3X = vec1Y*vec2Z - vec2Y*vec1Z;
	float vec3Y = vec1Z*vec2X - vec2Z*vec1X;
	float vec3Z = vec1X*vec2Y - vec2X*vec1Y;

	vertex[a * 6 + 3] += vec3X, vertex[a * 6 + 4] += vec3Y, vertex[a * 6 + 5] += vec3Z;
	vertex[b * 6 + 3] += vec3X, vertex[b * 6 + 4] += vec3Y, vertex[b * 6 + 5] += vec3Z;
	vertex[c * 6 + 3] += vec3X, vertex[c * 6 + 4] += vec3Y, vertex[c * 6 + 5] += vec3Z;
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


	if (trackMiddle) {
		moveMiddleX = (x - MiddleX) / (float)width;
		moveMiddleY = (y - MiddleY) / (float)height;
		MiddleX = x;
		MiddleY = y;
	}

	if (trackRight)
	{
		if (RightY > y) zoom = -1;
		else if (RightY < y)zoom = +1;
		
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
			trackball_ptov(x, y, winWidth, winHeight, tempUse);
			LeftX = tempUse[0], LeftY = tempUse[1], LeftZ = tempUse[2];
		}
		else
			if (s == GLUT_UP) {
				trackLeft = false;
			}
	}
	if (b == GLUT_MIDDLE_BUTTON)
	{
		if (s == GLUT_DOWN) {
			MiddleX = x;
			MiddleY = y;
			trackMiddle = true;
		}
		else
			if (s == GLUT_UP) {
				trackMiddle = false;
			}
	}
	if (b == GLUT_RIGHT_BUTTON)
	{
		if (s == GLUT_DOWN) {
			RightY = y;
			trackRight = true;
		}
		else
			if (s == GLUT_UP) {
				trackRight = false;
			}
	}




}



void Input() {
	freopen("fandisk.off", "r", stdin);
	string OFFstring;
	char offs;
	cin >> OFFstring;
	
	cin >> numVertex >> numIndicies >> offs;
	vertex = new float[6 * numVertex];
	indices = new int[3 * numIndicies];

	for (int i = 0; i < numVertex; ++i) {
		float x, y, z; cin >> x >> y >> z;
		vertex[i * 6] = x, vertex[i * 6 + 1] = y, vertex[i * 6 + 2] = z;
		vertex[i * 6 + 3] = 0, vertex[i * 6 + 4] = 0, vertex[i * 6 + 5] = 0;
	}

	for (int i = 0; i < numIndicies; ++i) {
		int off, a, b, c;
		cin >> off >> a >> b >> c;
		indices[i * 3] = a, indices[i * 3 + 1] = b, indices[i * 3 + 2] = c;
		calcNormals(a, b, c);
		
	}
	for (int i = 0; i < numVertex; ++i) {
		normalize(i);
	}
}
// done part
void Mesh_Init() {
	//rendering vertecies
	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertex * 6, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 6 * numVertex, vertex);

	//rendering indices
	glGenBuffers(1, &indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * numIndicies * 3, indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(float) * 6, ((float*)(sizeof(float) * 3)));
	glVertexPointer(3, GL_FLOAT, sizeof(float) * 6, 0);
}
