#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <math.h>
#include "mat.h"
#include "Angel.h"
#include "textfile.h"
class Input;

using namespace std;
GLuint p[3];


float alpha = 10;

vec4 specularConst;
vec4 diffuseConst;
vec4 ambientConst;

float constantAttenuation = 1.0;
float linearAttenuation = 0;
float quadraticAttenuation = 0;

void trackball_ptov(int x, int y, int width, int height, float v[3]);
bool trackLeft = false , trackMiddle = false , trackRight = false;
float LeftX = 0.0f, LeftY = 0.0f, LeftZ = 0.0f , MiddleX = 0.0f, MiddleY = 0.0f , RightY = 0.0f , moveMiddleX = 0.0, moveMiddleY = 0.0, moveRightZ = 1.0f;
void pressMouseButton(int b, int s, int x, int y) , normalize(int a) , calcNormals(int a, int b, int c);
void keyboard(unsigned char key, int x, int y) , Input() , InitGL();

void mouseMove(int x, int y) , Mesh_Init();
	
float matrix[16];
float zoom = 0.2;
float *vertex , *normals;
int *indices;

float width = 600, height = 600, winWidth = 600, winHeight = 600;
float angle = 0.0, axis[3], trans[3];
int  numVertex, numIndicies;

GLuint vertexVBO, indexVBO;


bool PhongShading = true, ToonShading = false;
int range = 3;
float thickness = 0.003;



mat4 projectionMatrix = mat4(1.0);
mat4 modelViewMatrix = mat4(1.0);

vec4 LightSourceAmbient = vec4(0.4, 0.5, 0.5, 1.0);
vec4 LightSourceDiffuse = vec4(0.6, 0.2, 0.2, 1.0);
vec4 LightSourceSpecular = vec4(0.6, 1.0, 0.3, 1.0);
vec4 FrontMaterialAmbient = vec4(0.3, 0.0, 0.3, 1.0);
vec4 FrontMaterialDiffuse = vec4(0.5, 0.4, 0.2, 1.0);
vec4 FrontMaterialSpecular = vec4(0.6, 0.8, 0.0, 1.0);
vec4 lightSourcePosition = vec4(1, 1, 10, 0);

float Min(float a, float b) {
	if (a < b)return a;
	return b;
}
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'p') {
		PhongShading ^= true;
		ToonShading ^= true;
	}
	else
	if (PhongShading) {
		switch (key) {
		case '1':
			FrontMaterialAmbient *= 0.90;
			break;
		case '3':
			FrontMaterialAmbient *= 1.10;
			FrontMaterialAmbient[0] = Min(FrontMaterialAmbient[0], 1.0);
			FrontMaterialAmbient[1] = Min(FrontMaterialAmbient[1], 1.0);
			FrontMaterialAmbient[2] = Min(FrontMaterialAmbient[2], 1.0);
			break;
		case '4':
			FrontMaterialDiffuse *= 0.90;
			break;
		case '6':
			FrontMaterialDiffuse *= 1.10;
			FrontMaterialDiffuse[0] = Min(FrontMaterialDiffuse[0], 1.0);
			FrontMaterialDiffuse[1] = Min(FrontMaterialDiffuse[1], 1.0);
			FrontMaterialDiffuse[2] = Min(FrontMaterialDiffuse[2], 1.0);
			break;
		case '7':
			FrontMaterialSpecular *= 0.90;
			break;
		case '9':
			FrontMaterialSpecular *= 1.10;
			FrontMaterialSpecular[0] = Min(FrontMaterialSpecular[0], 1.0);
			FrontMaterialSpecular[1] = Min(FrontMaterialSpecular[1], 1.0);
			FrontMaterialSpecular[2] = Min(FrontMaterialSpecular[2], 1.0);
			break;
		case '+':
			alpha += 0.5;
			break;
		case '-':
			alpha -= 0.5;
			break;
		

		}
	}
	else {
		switch (key)
		{
		case '-':
			thickness -= 0.001;
			break;
		case '+':
			thickness += 0.001;
			break;
		default:
			range = (key - '0');
			break;
		}
	}

	glutPostRedisplay();
}

void PassUniforms(int shaderNum) {
	glUniformMatrix4fv(glGetUniformLocation(p[shaderNum], "ModelViewMatrix"), 1, GL_TRUE, modelViewMatrix);
	glUniformMatrix4fv(glGetUniformLocation(p[shaderNum], "ProjectionMatrix"), 1, GL_TRUE, projectionMatrix);
	glUniform4fv(glGetUniformLocation(p[shaderNum], "LightSourcePosition"), 1, lightSourcePosition);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (trackLeft)
	{
		modelViewMatrix = RotateX(axis[0] * angle * 10) * RotateY(axis[1] * angle * 10) *  RotateZ(axis[2] * angle * 10)  * modelViewMatrix;
	}

	if (trackMiddle)
	{
		modelViewMatrix = Translate(vec3(moveMiddleX / 4.0f, -moveMiddleY / 4.0f, 0.0f)) * modelViewMatrix;
	}

	if (trackRight)
	{
		projectionMatrix = Ortho(-zoom, zoom, -zoom, zoom, -100, 100);
	}

	if (PhongShading) {
		glUseProgram(p[0]);
		PassUniforms(0);
		glUniform4fv(glGetUniformLocation(p[0], "ambientConst"), 1, LightSourceAmbient * FrontMaterialAmbient);
		glUniform4fv(glGetUniformLocation(p[0], "diffuseConst"), 1, LightSourceDiffuse * FrontMaterialDiffuse);
		glUniform4fv(glGetUniformLocation(p[0], "specularConst"), 1, LightSourceSpecular * FrontMaterialSpecular);
		glUniform1f(glGetUniformLocation(p[0], "constantAttenuation"), constantAttenuation);
		glUniform1f(glGetUniformLocation(p[0], "linearAttenuation"), linearAttenuation);
		glUniform1f(glGetUniformLocation(p[0], "quadraticAttenuation"), quadraticAttenuation);
		glUniform1f(glGetUniformLocation(p[0], "alpha"), alpha);

		glDrawElements(GL_TRIANGLES, 3 * numIndicies, GL_UNSIGNED_INT, 0);
	}
	else if (ToonShading) {
		
		glEnable(GL_CULL_FACE);
		
		
		glCullFace(GL_FRONT);
		glUseProgram(p[1]);
		PassUniforms(1);
		glUniform1f(glGetUniformLocation(p[1], "thickness"), thickness);
		glDrawElements(GL_TRIANGLES, 3 * numIndicies, GL_UNSIGNED_INT, 0);
		
		glCullFace(GL_BACK);
		glUseProgram(p[2]);
		PassUniforms(2);
		glUniform1f(glGetUniformLocation(p[2], "range"), range);
		glDrawElements(GL_TRIANGLES, 3 * numIndicies, GL_UNSIGNED_INT, 0);
		
		glDisable(GL_CULL_FACE);

	}
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
	glClearColor(1.1,1.1,0.1,1.0);
	projectionMatrix = Ortho(-0.2, 0.2, -0.2, 0.2, -100, 100);

	glEnable(GL_DEPTH_TEST);
	Input();
	Mesh_Init();


	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);
	glutMotionFunc(mouseMove);
	glutMouseFunc(pressMouseButton);
	glutKeyboardFunc(keyboard);

	/* 
	p[1] = createGLSLProgram("silhouette.vert", NULL, "silhouette.frag"); // Silhouette
	p[2] = createGLSLProgram("toon.vert", NULL, "toon.frag"); // Cartoon
	p[0] = createGLSLProgram("phong.vert", NULL, "phong.frag"); // Phong
	*/
	p[1] = createGLSLProgram("../silhouette.vert", NULL, "../silhouette.frag"); // Silhouette
	p[2] = createGLSLProgram("../toon.vert", NULL, "../toon.frag"); // Cartoon
	p[0] = createGLSLProgram("../phong.vert", NULL, "../phong.frag"); // Phong
																
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
		else if (RightY < y)zoom -= 0.001;
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

