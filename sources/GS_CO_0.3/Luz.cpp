#pragma once
#include "Luz.h"


Luz::Luz()
{


	GLfloat LuzPos[] = { 0.0f, 200.0f, 0.0f, 1.0f };
	GLfloat SpotDir[] = { 0.0f, -200.0f, 0.0f };
	GLfloat Ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat Diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat SpecRef[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };


	glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);


	glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
	glLightfv(GL_LIGHT0, GL_POSITION, LuzPos);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotDir);

	// Efectos de foco
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0f);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100.0f);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotDir);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);


	// Definimos propiedades luminosas de los materiales
	glEnable(GL_COLOR_MATERIAL);

	// Definimos las propiedades de brillo metálico
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecRef);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);


	Linterna();

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

}


Luz::~Luz()
{
}


void Luz::refresh(GLfloat* LuzPos, GLfloat* SpotDir){

	
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, LuzPos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotDir);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);


}

void Luz::Linterna(){

	GLfloat Ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat Diffuse[] = { 0.7f, 0.7f, 0.3f, 1.0f };
	GLfloat Specular[] = { 1.0f, 1.0f, 0.5f, 1.0f };

	GLfloat Ambient2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat Diffuse2[] = { 0.7f, 0.2f, 0.2f, 1.0f };
	GLfloat Specular2[] = { 1.0f, 0.4f, 0.4f, 1.0f };

	GLfloat Ambient3[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat Diffuse3[] = { 0.2f, 0.7f, 0.2f, 1.0f };
	GLfloat Specular3[] = { 0.4f, 1.0f, 0.4f, 1.0f };


	GLfloat LuzPos[] = { 0.0f, 30.0f, 0.0f, 1.0f };
	GLfloat SpotDir[] = { -25.0f, 0.0f, 0.0f };

	glLightfv(GL_LIGHT1, GL_AMBIENT, Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Specular);
	glLightfv(GL_LIGHT1, GL_POSITION, LuzPos);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotDir);

	// Efectos de foco
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100.0f);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, SpotDir);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);


	GLfloat SpotDir2[] = { 20.0f, 0.0f, -20.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, Ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Specular2);
	glLightfv(GL_LIGHT2, GL_POSITION, LuzPos);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotDir);

	// Efectos de foco
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0f);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100.0f);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, SpotDir2);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHTING);

	GLfloat SpotDir3[] = { 20.0f, 0.0f, 20.0f };
	glLightfv(GL_LIGHT3, GL_AMBIENT, Ambient3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Diffuse3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, Specular3);
	glLightfv(GL_LIGHT3, GL_POSITION, LuzPos);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotDir);

	// Efectos de foco
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 15.0f);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100.0f);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, SpotDir);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHTING);

}