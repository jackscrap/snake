#include <GL/gl.h>
#include <GL/glut.h>

#include "game.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <typeinfo>

const int size = 40;
int fps = 10;

void line(int x, int y) {
	glBegin(GL_LINE_LOOP);

	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);

	glEnd();
}

void grid() {
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			line(x, y);
		}
	}
}

std::vector<int> pos = {
	rand() % size,
	rand() % size
};
	std::vector<std::vector<int>> hist;
int dir = 0,
		inc = 1,
		len = 1;

int applePos[2];

void newApple() {
	applePos[0] = rand() % size;
	applePos[1] = rand() % size;
}

void apple() {
	glRectd(applePos[0], applePos[1], applePos[0] + 1, applePos[1] + 1);
}

void slither() {
	pos[dir] += inc;

	if (pos[dir] > size) {
		pos[dir] = 0;
	}

	if (pos[dir] < 0) {
		pos[dir] = size;
	}

	if (pos[0] == applePos[0] && pos[1] == applePos[1]) {
		len++;
		newApple();
	}

	if (std::find(hist.begin(), hist.end(), pos) != hist.end()) {
		exit(1);
	}

	hist.push_back(pos);
	if (hist.size() > len) {
		hist.erase(hist.begin());
	}
}

void drawHist() {
	for (std::vector<int> dot : hist) {
		glRectd(dot[0], dot[1], dot[0] + 1, dot[1] + 1);
	}
}

void timer_callback(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / fps, timer_callback, 0);
}

void display_callback() {
	glClear(GL_COLOR_BUFFER_BIT);

	grid();
	drawHist();
	slither();
	apple();

	glutSwapBuffers();
}

void reshape_callback(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, size, 0.0, size, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard_callback(int key, int, int) {
	switch(key) {
		case GLUT_KEY_UP:
			dir = 1;
			inc = 1;

			break;

		case GLUT_KEY_DOWN:
			dir = 1;
			inc = -1;

			break;

		case GLUT_KEY_LEFT:
			dir = 0;
			inc = -1;

			break;

		case GLUT_KEY_RIGHT:
			dir = 0;
			inc = 1;

			break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(512, 512);
	glutCreateWindow("Snake");

	newApple();

	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0, timer_callback, 0);

	glutSpecialFunc(keyboard_callback);

	glutMainLoop();

	return 0;
}
