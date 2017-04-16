#pragma once
#include "Mundo.h"
#include "player.h"

#define PI 3.141592653589793

Mundo::Mundo()
{

	


	for (int i = 0; i < numRanas; i++) {
		Ball* ball = new Ball();
		ball->pos = Vec3f(90 * randomFloat() - 45,
			15 * randomFloat() ,
			90 * randomFloat() - 45);
		//ball->pos = Vec3f(8 * randomFloat() - 4, 8 * randomFloat() + 20, 8 * randomFloat() - 4);
		ball->v = Vec3f(16 * randomFloat() - 8,
			8 * randomFloat() - 4,
			16 * randomFloat() - 8);
		//ball->r = 1.0f * randomFloat() + 0.1f;
		ball->r = 1.0f;
		//esta línea comentada sirve para hacer bolas más grandes para facilitar que choquen entre si
		//ball->r = 0.8f * randomFloat() + 0.1f;
		ball->color = Vec3f(0.6f * randomFloat() + 0.2f,
			0.6f * randomFloat() + 0.2f,
			0.6f * randomFloat() + 0.2f);
		

		_ranas.push_back(ball);
	}

	for (int i = 0; i < 60; i++) {
		Box* box = new Box();
		box->pos = Vec3f(90 * randomFloat() - 45,
			1,
			90 * randomFloat() - 45);
		box->v = Vec3f(0.0f,0.0f,0.0f);
		box->side = 2.0f;
		//esta línea comentada sirve para hacer bolas más grandes para facilitar que choquen entre si
		//ball->r = 0.8f * randomFloat() + 0.1f;
		box->color = Vec3f(0.6f * randomFloat() + 0.2f,
			0.6f * randomFloat() + 0.2f,
			0.6f * randomFloat() + 0.2f);
		box->minBounds = box->pos + Vec3f(-1.0f, -1.0f, -1.0f);
		box->maxBounds = box->pos + Vec3f(1.0f, 1.0f, 1.0f);

		_cajas.push_back(box);
	}


	cargador = new objloader();
	caja = cargador->load("obj/crate2.obj");

	cargador = new objloader();
	fachada = cargador->load("obj/fachada.obj");

	cargador = new objloader();
	suelo = cargador->load("obj/ground.obj");

	cargador = new objloader();
	rana = cargador->load("obj/rana3.obj");

	mundoEstatico = glGenLists(1);
	glNewList(mundoEstatico, GL_COMPILE);
	listaDibujarMundoEstatico();
	glEndList();


}

void Mundo::end(){

	myAudio->playSound(FIN);
	Sleep(2000);
	

}

Mundo::Mundo(sound *audio,int dificultad)
{

	
	unsigned int locked;
	myAudio = audio;
	Vec3f position = Vec3f(0, 0, 0);
	Vec3f orientation = Vec3f(0, 0, 0);
	myAudio->setListener(position, orientation);

	locked = audio->loadSound("datos/LockedWithMe.wav");
	audio->playSound(locked, position, orientation, 0.5, false);
	
	bump = audio->loadSound("datos/smb_bump.wav");
	BSO = audio->loadSound("datos/bso.wav");
	FIN = audio->loadSound("datos/end.wav");
	HIT = audio->loadSound("datos/hitmarker.wav");
	
	/*Vec3f position = Vec3f(0, 0, 0);
	Vec3f orientation = Vec3f(0, 0, 0);*/
	myAudio->setListener(position, orientation);

	
	
	if (dificultad != 0){
		for (int i = 0; i < numRanas; i++) {
			Ball* ball = new Ball();
			ball->pos = Vec3f(90 * randomFloat() - 45,
				15 * randomFloat(),
				90 * randomFloat() - 45);
			//ball->pos = Vec3f(8 * randomFloat() - 4, 8 * randomFloat() + 20, 8 * randomFloat() - 4);

			switch (dificultad){

			case 1:
				ball->v = Vec3f(7 * randomFloat() - 3.5,
					8 * randomFloat() - 4,
					7 * randomFloat() - 3.5);
				break;

			case 2:
				ball->v = Vec3f(16 * randomFloat() - 8,
					8 * randomFloat() - 4,
					16 * randomFloat() - 8);
				break;

			case 3:
				ball->v = Vec3f(64 * randomFloat() - 8,
					32 * randomFloat() - 4,
					64 * randomFloat() - 8);
				break;

			default:
				ball->v = Vec3f(8 * randomFloat() - 4,
					4 * randomFloat() - 2,
					8 * randomFloat() - 4);
				break;

			}

			//ball->r = 1.0f * randomFloat() + 0.1f;
			ball->r = 1.0f;
			//esta línea comentada sirve para hacer bolas más grandes para facilitar que choquen entre si
			//ball->r = 0.8f * randomFloat() + 0.1f;
			ball->color = Vec3f(0.6f * randomFloat() + 0.2f,
				0.6f * randomFloat() + 0.2f,
				0.6f * randomFloat() + 0.2f);


			_ranas.push_back(ball);
		}
	}

	for (int i = 0; i < 60; i++) {
		Box* box = new Box();
		box->pos = Vec3f(90 * randomFloat() - 45,
			1,
			90 * randomFloat() - 45);
		box->v = Vec3f(0.0f, 0.0f, 0.0f);
		box->side = 2.0f;
		//esta línea comentada sirve para hacer bolas más grandes para facilitar que choquen entre si
		//ball->r = 0.8f * randomFloat() + 0.1f;
		box->color = Vec3f(0.6f * randomFloat() + 0.2f,
			0.6f * randomFloat() + 0.2f,
			0.6f * randomFloat() + 0.2f);
		box->minBounds = box->pos + Vec3f(-1.0f, -1.0f, -1.0f);
		box->maxBounds = box->pos + Vec3f(1.0f, 1.0f, 1.0f);

		_cajas.push_back(box);
	}


	cargador = new objloader();
	caja = cargador->load("obj/crate2.obj");

	cargador = new objloader();
	fachada = cargador->load("obj/fachada2.obj");

	cargador = new objloader();
	suelo = cargador->load("obj/ground.obj");

	cargador = new objloader();
	rana = cargador->load("obj/rana3.obj");

	cargador = new objloader();
	foco = cargador->load("obj/foco.obj");

	mundoEstatico = glGenLists(1);
	glNewList(mundoEstatico, GL_COMPILE);
	listaDibujarMundoEstatico();
	glEndList();
	rotFoco = 0.0f;

	audio->playSound(BSO, true);

}

Mundo::~Mundo()
{
}

void Mundo::disparoPlayer(Vec3f direccion,Vec3f origen){
	
	if (checkDisparo(direccion, origen, _ranas)){
	//Hacer sonido de rana muerta!!
		myAudio->playSound(HIT);
	}
	//printf("Size despois: %d\n", getRanas().size());
}


static inline ALenum GetFormatFromInfo(short channels, short bitsPerSample) {
	if (channels == 1)
		return AL_FORMAT_MONO16;
	return AL_FORMAT_STEREO16;
}

void  Mundo::Malla()
{
	//Malla desde -50 hasta +50
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.0f, 0.0001f, 0.0f);
	for (int i = -50; i < 50; i++) {
		glBegin(GL_LINES);
		glVertex3f(i, 0, -50);
		glVertex3f(i, 0, 50);
		glEnd();
	}

	for (int i = -50; i < 50; i++) {
		glBegin(GL_LINES);
		glVertex3f(-50, 0, i);
		glVertex3f(50, 0, i);
		glEnd();
	}

	glPopMatrix();
}


void  Mundo::Suelo()
{
	glPushMatrix();

	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-50.0f, 0.0f, -50.0f);
	glVertex3f(-50.0f, 0.0f, 50.0f);
	glVertex3f(50.0f, 0.0f, 50.0f);
	glVertex3f(50.0f, 0.0f, -50.0f);
	glEnd();

	glPopMatrix();
}

void  Mundo::listaDibujarMundoEstatico(){

	glPushMatrix();
	glCallList(suelo);
	glPopMatrix();

	glPushMatrix();
	glCallList(fachada);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glCallList(fachada);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glCallList(fachada);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glCallList(fachada);
	glPopMatrix();

	

	//glPopMatrix();

}

void Mundo::dibujarMundoEstatico(){

	glCallList(mundoEstatico);

}

void Mundo::dibujarMundoDinamico(){

	//Bolas, o ranas...
	for (unsigned int i = 0; i < _ranas.size(); i++) {
		Ball* ball = _ranas[i];
		glPushMatrix();


		glTranslatef(ball->pos[0], ball->pos[1], ball->pos[2]);
		glColor3f(ball->color[0], ball->color[1], ball->color[2]);
		//glutSolidSphere(ball->r, 40, 40); //Draw a sphere
		//glutWireSphere(ball->r, 5, 5);
		//Calcular rotación de la rana
		//glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
		glRotatef(rotacionRana(ball), 0.0f,1.0f, 0.0f);
		glCallList(rana);
		glPopMatrix();
		glPopMatrix();
	}

	for (unsigned int i = 0; i < _cajas.size(); i++) {
		Box* box = _cajas[i];
		glPushMatrix();
		glTranslatef(box->pos[0], box->pos[1], box->pos[2]);
		glCallList(caja);
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0.0f,30.0f,0.0f);
	glRotatef(rotFoco, 0.0f, 1.0f, 0.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	glPushMatrix();
	for (unsigned int i = 0; i < 3; i++) {
		
		
		glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
		glCallList(foco);
		
	}
	glPopMatrix();
	
	/*LUZ*/
	GLfloat LuzPos[] = { 0.0f, 30.0f, 0.0f, 1.0f };
	GLfloat SpotDir[] = { -15.0f, -30.0f, 0.0f };
	GLfloat SpotDir2[] = { 10.0f, -30.0f, -10.0f };
	GLfloat SpotDir3[] = { 10.0f, -30.0f, 10.0f };

	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHTING);
	glLightfv(GL_LIGHT1, GL_POSITION, LuzPos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, SpotDir);
	glLightfv(GL_LIGHT2, GL_POSITION, LuzPos);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, SpotDir2);
	glLightfv(GL_LIGHT3, GL_POSITION, LuzPos);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, SpotDir3);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHTING);


	/*END LUZ*/

	glPopMatrix();
	rotFoco += 0.5;

}

float Mundo::rotacionRana(Ball* bola){

	float angulo;

	angulo = atan2(-bola->v[2] , bola->v[0]);

	angulo = angulo*180/PI;

	//printf("Angulo rana: %f\n", angulo);

	return angulo;

}


vector<Ball*> Mundo::getRanas(){

	return Mundo::_ranas;
}

vector<Box*> Mundo::getCajas(){

	return Mundo::_cajas;
	
}

