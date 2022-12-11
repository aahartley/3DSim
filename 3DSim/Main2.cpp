#define TO_RADIANS 3.141592/180.0
#include <GL/freeglut.h>
#include <iostream>


// angles and starting position
float xangle = 0.0f, yangle = 1.0f, zangle = -1.0f;

// XYZ position of the camera
float  x = 0.0f, y = 1.0f, z = 5.0f;

// Mouse rotation sensitivity
float sensitivity = 0.2f;

// width and height of the window
int ww, hh;

// Mouse position and yaw  
float x_pos = 0.0f, y_pos = 0.0f;

void mouseMove(int xx, int yy) {

	// Get mouse position scaling by the center of the scene
	x_pos = (xx - ww / 2) * 0.01;
	y_pos = (yy - hh / 2) * 0.01;

	// Get the angle of the coordinate: we just use sin for both x/y and 
	// - cos for the z coordinate (since we're looking into the scene)
	xangle = sin(x_pos);
	yangle = sin(y_pos);
	zangle = -cos(x_pos);
	std::cout << xx << " " << x_pos << " " << xangle << std::endl;

	// Do not exceed the vertical view angle of the camera by 45 degree
	if (yangle * TO_RADIANS > 45 || yangle * TO_RADIANS < -45) {
		yangle = 45.0f;
	}

}


void pressKey(unsigned char key, int xx, int yy) {

	// Speed of movement
	float speed = 0.50f;

	// Case switch
	switch (key) {

		// We're moving left/right/up/down with the keyboard. For example, to achieve a 360 degree rotation
		// based on the camera angle given by the mouse, we add to the x variable the z angle and 
		// the z the x one in the A (left) case. Same happens with D. 
		// With W/S, since we just want too move forward and backward the camera, we add the correct 
		// angle to the x and z variable.
	case 'A':
	case 'a':
		x += zangle * speed;
		z -= xangle * speed;
		break;
	case 'D':
	case 'd':
		x -= zangle * speed;
		z += xangle * speed;
		break;
	case 'W':
	case 'w':
		x += xangle * speed;
		z += zangle * speed;
		break;
	case 'S':
	case 's':
		x -= xangle * speed;
		z -= zangle * speed;
		break;
	}

}


void drawScene(void) {

	// Clearing procedures 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	glLoadIdentity();

	// Looking at the coordinate calculated by moving mouse/keyboard. 
	// The first three parameters: the camera position vector. 
	// The second three parameters: the point we're looking at 
	// Thee last three parameters: the UP vector 
	gluLookAt(x, y, z, x + xangle, y - yangle, z + zangle, 0.0f, y, 0.0f);

	// Draw a square in the air
	glBegin(GL_QUADS);
	glVertex3f(-2.0, 2.0, -40.0);
	glVertex3f(2.0, 2.0, -40.0);
	glVertex3f(2.0, 6.0, -40.0);
	glVertex3f(-2.0, 6.0, -40.0);
	glEnd();

	// Draw an XZ plane
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	// Swap front and back buffer
	glutSwapBuffers();

}

void resize(int w, int h) {

	// Setting ratio and new window size
	float ratio = w * 1.0 / h;
	ww = w;
	hh = h;

	// Setting the viewport
	glViewport(0, 0, w, h);

	// Setting the projection 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	//glOrtho(-10.0, 10.0, -10.0, 10.0, 0.0, 10.0); 

	// Resettign the modelview matrix 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Redisplay the scene
	glutPostRedisplay();

}

void update(int value) {

	// Timer function in which we redisplay the content of the screen each 1000/60 
	// msec, meaning that we want to achieve a 60fps configuration.
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);
}

void setup(void) {

	// Clearing background color and setting up to black
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Other init procedures if needed

}

void main(int argc, char** argv) {

	// Init procedures
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);

	// Creating a window 
	glutCreateWindow("Camera.cpp");

	// Func callback
	glutReshapeFunc(resize);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(pressKey);
	glutPassiveMotionFunc(mouseMove);

	// here are the new entries
	glutTimerFunc(100, update, 0);

	// Setup func 
	setup();

	// start loop
	glutMainLoop();

}