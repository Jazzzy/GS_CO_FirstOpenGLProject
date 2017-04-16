#pragma once
#include "hud.h"

void setOrthographicProjection(int width, int height) {
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, width, height, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void renderBitmapString(

	float x,
	float y,
	int spacing,
	void *font,
	char *string) {

	char *c;
	int x1 = x;

	for (c = string; *c != '\0'; c++) {

		glRasterPos2f(x1, y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font, *c) + spacing;
	}
}

void hud(char* msg, int width, int height,int x, int y){

	glDisable(GL_TEXTURE_2D);

	setOrthographicProjection(width, height);

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(x, y, 2, GLUT_BITMAP_TIMES_ROMAN_24, msg);
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2d((width / 2) + 5, (height / 2));
	glVertex2d((width / 2) + 2, (height / 2));
	glVertex2d((width / 2) - 3, (height / 2));
	glVertex2d((width / 2) - 6, (height / 2));


	glVertex2d((width / 2), (height / 2) + 6);
	glVertex2d((width / 2), (height / 2) + 3);
	glVertex2d((width / 2), (height / 2) - 2);
	glVertex2d((width / 2), (height / 2) - 5);

	glEnd();
	glPopMatrix();

	restorePerspectiveProjection();
}


void fin(int width, int height){

	glDisable(GL_TEXTURE_2D);

	setOrthographicProjection(width, height);

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString((width / 2) - 90 , height/2 - 30 , 3, GLUT_BITMAP_TIMES_ROMAN_24, "FIN DEL JUEGO");
	glPopMatrix();


	restorePerspectiveProjection();
}

void hudBang(char* msg, int width, int height, int x, int y){

	glDisable(GL_TEXTURE_2D);

	setOrthographicProjection(width, height);

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 0.3f, 0.3f);
	renderBitmapString(x, y, 2, GLUT_BITMAP_TIMES_ROMAN_24, msg);
	glPopMatrix();

	restorePerspectiveProjection();
}