#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <math.h>

class Input;


using namespace std;

void trackball_ptov(int x, int y, int width, int height, float v[3]);
void startLeft(int x, int y);
void startMiddle(int x, int y);
void startRight(int x, int y);
void stopLeft(int x, int y);
void stopMiddle(int x, int y);
void stopRight(int x, int y);
bool trackLeft = false;
bool trackMiddle = false;
bool trackRight = false;
float LeftX = 0.0f, LeftY = 0.0f, LeftZ = 0.0f;
float MiddleX = 0.0f, MiddleY = 0.0f;
float RightY = 0.0f;
float moveMiddleX = 0.0, moveMiddleY = 0.0, moveRightZ = 1.0f;


const float M_PI = 3.14159265359;
void pressMouseButton(int b, int s, int x, int y);
void normalize(int a);
void calcNormals(int a, int b, int c);
void keyboard(unsigned char key, int x, int y);
void Input();
void InitGL();
void mouseMove(int x, int y);
void Mesh_Init();
void putLights();
float matrix[16];

float *vertex;
float *normals;
int *indices;

float width = 600, height = 600, winWidth = 600, winHeight = 600;
float angle = 0.0, axis[3], trans[3];

int  numVertex, numIndicies;
GLuint vertexVBO, indexVBO;


float zoom = 0.2;
bool projection = 0;

void keyboard(unsigned char key, int x, int y) {
	if (key == 'o') {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-0.2, 0.2, -0.2, 0.2, -100, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		projection = 0;

	}
	else
	if (key == 'p') {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(200*zoom, width / (float)height, 0.001, 100);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(0, 0, -0.5);
			projection = 1;
	}
	if (key == 'f')
	{
		glEnable(GL_FLAT);
		glShadeModel(GL_FLAT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
		if (key == 'w') {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
			if (key == 's') {
				glEnable(GL_SMOOTH);
				glShadeModel(GL_SMOOTH);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
	glutPostRedisplay();
}


void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (trackLeft)
	{
		if (projection == 0) {
			glMatrixMode(GL_MODELVIEW);
			glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
			glLoadIdentity();
			glRotatef(angle, axis[0], axis[1], axis[2]);
			glMultMatrixf(matrix);
		}
		else {
			glMatrixMode(GL_MODELVIEW);
			glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
			glLoadIdentity();
			glMultMatrixf(matrix);
			glRotatef(angle, axis[0], axis[1], axis[2]);
		}
	}

	if (trackMiddle)
	{
		glMatrixMode(GL_MODELVIEW);
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		glLoadIdentity();							
		glTranslatef(moveMiddleX/4.0f, -moveMiddleY/4.0f, 0.0f);
		glMultMatrixf(matrix);

	}
	if (trackRight)
	{
		if (projection == 0) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-zoom, zoom, -zoom, zoom, -100, 100);
		}
		else {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(200 * zoom, width / (float)height, 0.01, 100);
		}
	}



	//drawing
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(GL_FLOAT, sizeof(float) * 6, ((float*)(sizeof(float) * 3)));
	glVertexPointer(3, GL_FLOAT, sizeof(float) * 6, 0);

	glDrawElements(GL_TRIANGLES, 3 * numIndicies, GL_UNSIGNED_INT, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	
	glutSwapBuffers();
}

void reshape(int w, int h) {
	winWidth = w;
	winHeight = h;
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}





int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	InitGL();


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-0.2, 0.2, -0.2, 0.2, -100, 100);

	
	putLights();
	glEnable(GL_DEPTH_TEST);
	Input();
	Mesh_Init();


	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);

	//glutKeyboardFunc(keyboard);
	glutMotionFunc(mouseMove);
	glutMouseFunc(pressMouseButton);
	glutKeyboardFunc(keyboard);


	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}




/*







FUNCTIONS








*/



void Input() {
	freopen("bunny.off", "r", stdin);
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
		if (RightY > y) zoom += 0.001;
		else if (RightY < y)zoom-= 0.001;
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
	if (b == GLUT_MIDDLE_BUTTON    )
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

void InitGL() {
	// init GLUT and create Window
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("CSE471 - Assignment 1");
	glewInit();
}
void putLights() {
	GLfloat lightPos1[] = { 0, 1, 1, 0 };
	GLfloat diffuse1[] = { 0.7,0.7,0.0,1 };
	GLfloat specular1[] = { 0.4,0.5,1.0,1 };
	GLfloat ambient1[] = { 0.1,1,0.1,0.1 };

	GLfloat lightPos2[] = { 2, 2, 8, 1 };
	GLfloat diffuse2[] = { 1.0,0.0,0.0,0.2 };
	GLfloat specular2[] = { 0.0,1.0,1,0.1 };
	GLfloat ambient2[] = { 0,0.1,0.6,0.3 };

	GLfloat lightPos3[] = { 8, 3, 8, 1 };
	GLfloat diffuse3[] = { 0.0,0.8,0.9,0.3 };
	GLfloat specular3[] = { 1.3,0.1,0.0,0.5 };
	GLfloat ambient3[] = { 0.3,0.1,0.6,1.0 };

	GLfloat materialColor[] = { 0.1f, 0.1f, 0.0f, 0.3f };
	GLfloat materialSpecular[] = { 0.1,0.1,0.0,0.1 };
	GLfloat materialEmission[] = { 0.1f,0.1f,0.1, 0.0f };
	GLfloat shininess = 128;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient2);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular3);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient3);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

