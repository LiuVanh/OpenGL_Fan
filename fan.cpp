#include <iostream>
#include <conio.h>
#include <GL/freeglut.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265
#endif


//remote view
int x_mouse_pos, y_mouse_pos;
double rotate_x, rotate_y;
double zoom_z = 0;

bool isfanon = false;
bool isRotale = false;

GLint fanPart1, fanPart2, fanPart3;

bool isLightMove = false, lightState = true;

int fan_state = 0;
double powerbtn = 0;
double twobtn = 0;
double onebtn = 0;
double threebtn = 0;

void vetruc() {
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-20.0, 0.0, 0.0);
	glVertex3f(20.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -20.0, 0.0);
	glVertex3f(0.0, 20.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -20.0);
	glVertex3f(0.0, 0.0, 20.0);
	glEnd();
	glEnable(GL_LIGHTING);
}

void dequat() {
	glTranslated(0,1,0);
	glRotated(180,0,1,0);
	glColor3d(0.3, 0.3, 0.3);
	glScaled(4,1,4);
	glutSolidCube(2);
	glScaled(0.25,1,0.25);
}

void chanquat() {
	glTranslated(0,0,2);
	glPushMatrix();
	glTranslated(0,1,0);
	glRotated(-90,1,0,0);
	glColor3d(0.8, 0.8, 0.8);
	glutSolidCylinder(1,8,7,1);
	glPopMatrix();
}

void nutbam(){
    glPushMatrix();
    glScaled(1,1,1.5);
    glColor3d(0.6,0.9,0.9);
    glTranslated(-2,1.3,-2.82);

    glPushMatrix();
    glPushMatrix();
    glPushMatrix();

    //so 3
    glTranslated(0,threebtn,0);
    glutSolidCube(0.75);
    glPopMatrix();
    //so 2
    glTranslated(0,twobtn,0);
    glTranslated(1.25,0,0);
    glutSolidCube(0.75);
    glPopMatrix();
    //so 1
    glTranslated(0,onebtn,0);
    glTranslated(2.5,0,0);
    glutSolidCube(0.75);
    glPopMatrix();
    //bat tat
    glTranslated(0,powerbtn,0);
    glColor3d(1,0.12,0.12);
    glTranslated(3.75,0,0);
    glutSolidCube(0.75);
    glPopMatrix();
}

void dongco() {
	glTranslated(0,9,-2);

	glPushMatrix();
	glRotated(-90,0,0,1);
	glColor3d(0.3, 0.3, 0.3);
	glutSolidCylinder(2,4,24,24);
	glPopMatrix();

	glColor3d(0.5, 0.5, 0.5);
	glTranslated(0,0,3.5);
	glutSolidTorus(1.95,0,40,40);

	//truc quat
	glTranslated(0,0,-5);
	glPushMatrix();
	glColor3d(0.85, 0.85, 0.85);
	glutSolidCylinder(0.35,3,24,24);
	glPopMatrix();

}

void canh() {
	glTranslated(3,0,0);
	glColor3d(1,0.55,0.45);
	glRotatef(180.0, 0.0, 0.0, 0.0);

	float centerX = 0.0;
	float centerY = 0.0;

	int numofEdge = 03;
	float angleIncrement = (2*M_PI) / numofEdge;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(centerX, centerY);
	float radius = 2.75;
	for (int i = 0; i <= numofEdge; i++) {
		float angle = i * angleIncrement;
		float x = centerX + cos(angle) * radius;
		float y = centerY + sin(angle) * radius;
		glVertex2f(x, y);
	}
	glEnd();

}

int fanspeed = 0;

void canhquat() {
	glRotated(fanspeed,0,0,1);
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	canh();
	glPopMatrix();

	glRotated(120,0,0,1);
	canh();
	glPopMatrix();
	glRotated(-120,0,0,1);
	canh();
	glPopMatrix();

	glColor3d(1,0.25,0.25);
	glutSolidTorus(0.5,0.5,36,36);
}

void longquat() {
	glPushMatrix();
	glScaled(1,1,0.5);
	glColor3d(0.1, 0.1, 0.1);
	glutWireTorus(3,3,9,30);
	glTranslated(10,5,5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0,-1.5);
	glutSolidCone(1.5,0.75,24,24);
	glPopMatrix();
}


void reshape(int w,int h) {
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1, 500.0);
	gluLookAt(0,15,25,0,7,0,0,1,0);
	glMatrixMode(GL_MODELVIEW);
}

void moveCamera() {
	glTranslated(0,0,zoom_z);
	glRotated (rotate_y,1,0,0);
	glRotated (rotate_x,0,1,0);
}


double swing_control = 0.3;

double swing = 0;
bool swing_state = false;
bool prev_swing_state = swing_state;

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			exit(0);
			break;
		case 'q':
			if (fan_state == 0)
				prev_swing_state = !prev_swing_state;
			else {
				swing_state = !swing_state;
				prev_swing_state = swing_state;
			}

			if (prev_swing_state)
				swing_control = 0;
			else
				swing_control = 0.3;
			break;
		case '0':
			powerbtn = -0.5;
        	fan_state = 0;
        	onebtn = 0;
        	twobtn = 0;
        	threebtn = 0;
			prev_swing_state = swing_state;
			swing_state = false;
			break;
		case '1':
			fan_state = 1;
			onebtn = -0.5;
        	twobtn = 0;
        	threebtn = 0;
			swing_state = prev_swing_state;
			break;
		case '2':
			fan_state = 2;
			twobtn = -0.5;
        	onebtn = 0;
        	threebtn = 0;
			swing_state = prev_swing_state;
			break;
		case '3':
			fan_state = 3;
			threebtn = -0.5;
        	onebtn = 0;
        	twobtn = 0;
			swing_state = prev_swing_state;
			break;
	}
}

void mouseFunc(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:

			if (state == GLUT_DOWN) {
				x_mouse_pos = x;
				y_mouse_pos = y;
				isRotale = true;
			} else
				isRotale = false;
			break;
	}
}

void motionFunc(int x, int y) {
	if (isRotale) {
		rotate_x += (x - x_mouse_pos) * 0.7;
		rotate_y += (y - y_mouse_pos) * 0.7;
		x_mouse_pos = x;
		y_mouse_pos = y;
	}
}

void mouseWheel(int button, int dir, int x, int y){
    if (dir>0)
        zoom_z += 1;
    else
        zoom_z -= 1;
}

bool state = true;
void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000/60,timer,0);
	if (swing_state) {
		switch(state) {
			case true:
				if (swing < 60)
					swing += 0.5;
				else state = false;
				break;
			case false:
				if (swing >-60)
					swing -= 0.5;
				else state = true;
				break;
		}
	}
	switch (fan_state) {
		case 0:
			if (powerbtn < 0) powerbtn += 0.05;
			break;
		case 1:
			fanspeed = (fanspeed +10) % 360 ;
			break;
		case 2:
			fanspeed = (fanspeed +15) % 360 ;
			break;
		case 3:
			fanspeed = (fanspeed +30) % 360 ;
			break;
	}
}

GLfloat lightPosition[] = {0,15,15,0};

void initLight() {
	
	GLfloat ambient_light[] = {0, 0, 0, 1.0};
	GLfloat diffuse_light[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat specular_light[] = {0.1, 0.1, 0.1, 1.0};

	GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
	GLfloat mat_diffuse[] = {0.7, 0.7, 0.7, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat high_shininess[] = {10.0};

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glDepthFunc(GL_LEQUAL);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init(void) {
	glClearColor(1.0, 0.9, 0.8, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	initLight();
	
	fanPart1 = glGenLists (1);
	glNewList (fanPart1, GL_COMPILE);
	dequat();
	chanquat();
	glEndList ();

	fanPart2 = glGenLists (1);
	glNewList (fanPart2, GL_COMPILE);
	dongco();
	longquat();
	glEndList ();

	fanPart3 = glGenLists (1);
	glNewList (fanPart3, GL_COMPILE);
	canhquat();
	glEndList ();
}

void san(){
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glColor3d(1.0, 1.0, 0.7);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-25,0,-25.0);
    glTexCoord2f(0,10); glVertex3f(25.0,0, -25.0);
    glTexCoord2f(10,10); glVertex3f(25.0,0, 25.0);
    glTexCoord2f(10,0); glVertex3f(-25.0,0, 25.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void cantocnang(){
    glColor3f(0.2,0.7,0.4);
    glPushMatrix();
    glTranslated(0,11.5+swing_control,1);
    glRotated(90,1,0,0);
    glutSolidCylinder(0.2,2,24,24);
    glColor3f(0.7,0.3,0.4);
    glutSolidTorus(0.2,0.2,12,12);
    glPopMatrix();
}

void fan() {
	san();
	glCallList(fanPart1);
	nutbam();
	
	glRotated(swing,0,1,0);
	cantocnang();
	glCallList(fanPart2);

	glRotated(fanspeed,0,0,1);
	glCallList(fanPart3);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glLoadIdentity();
	glLightfv (GL_LIGHT0, GL_POSITION, lightPosition);
	moveCamera();
	glPushMatrix();
	//vetruc();
	fan();
	glPopMatrix();

	// draw light source position
	/*
	glPushMatrix();
	glTranslatef(lightPosition[0],lightPosition[1],lightPosition[2]);
	glutSolidSphere(1,24,24);
	glPopMatrix();
	*/
	glutSwapBuffers();

}

int main(int argc, char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800,450);
	glutInitWindowPosition(20,20);
	glutCreateWindow("Floor Fan");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);
	glutMouseWheelFunc(mouseWheel);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(0,timer,0);
	init();
	glutMainLoop();
	return 0;
}
