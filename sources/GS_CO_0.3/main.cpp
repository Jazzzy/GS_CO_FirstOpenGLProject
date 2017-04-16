#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <Windows.h>
#include "Camara.h"
#include "objLoader.h"
#include "player.h"
#include "Luz.h"
#include "hud.h"
#include "mundo.h"
#include "colisiones.h"
#include <conio.h>
#include <stdlib.h>
#include <al\al.h>
#include <al\alc.h>
#include "sound.h"
//#include <al\alu.h>
//#include <al\alut.h>

using namespace std;

void Display();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MueveRaton(int x, int y);
void PulsaRaton(int button, int state, int x, int y);
void Timer(int value);
void Idle();
void Iniciar();
void Malla();
void update(int value);
void updatePlayer(int value);
void chase(int value);

bool endGame = false;
bool g_key[256] = {false};
bool g_shift_down = false;
bool g_fps_mode = true;
int g_viewport_width = 1240;
int g_viewport_height = 720;
int bang_g_viewport_width = 1240;
int bang_g_viewport_height = 720;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;

// Movement settings
const float velMov = 0.1;
const float g_rotation_speed = M_PI / 180 * 0.1;
const float velAc = 0.0075;
const float velDec = -0.0025;

//Player
Player *player;
objloader *cargador;
GLuint suelo;
int caja;
int test;


//Light
Luz *luz;
GLfloat LuzPos[] = { 0.0f, 200.0f, 0.0f, 1.0f };
GLfloat SpotDir[] = { 0.0f, -200.0f, 0.0f };

//World
Mundo *mundo;
int dificultad = 1;
vector<Ball*> _ranas;
vector<Box*> _cajas;
float _timeUntilUpdate = 0;
float _timeUntilUpdatePlayer = 0;

//Frogs
int chaseNum = 0;

//Sound
sound *audio;


//HUD
char msg[50];
char datosHud[50];
int bangCounter = 0;
char *bang;
char bang1[10] = "BANG!!";
char bang2[10] = "PIUM!!";
char bang3[10] = "PUM!!";
char bang4[10] = "PAYUM!!";

/*
*/
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1240, 720);
	glutCreateWindow("Global Strike: Counter Offensive");

	glutIgnoreKeyRepeat(1);

	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(PulsaRaton);
	glutMotionFunc(MueveRaton);
	glutPassiveMotionFunc(MueveRaton);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutIdleFunc(Idle);

	Iniciar();

	glutTimerFunc(TIMER_MS, update, 0);
	glutTimerFunc(TIMER_MS, updatePlayer, 0);
	glutTimerFunc(3000, chase, chaseNum);
	glutTimerFunc(1, Timer, 0);
	glutMainLoop();

	return 0;
}

void Iniciar(){

	audio = new sound;


	GLfloat Ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat SpecRef[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	
	printf("\n\n*_*_*_*_*_*_*_*_*_*_*_*_WELCOME TO FROGZ_*_*_*_*_*_*_*_*_*_*_*_*\n\n");
	printf("Inserte dificultad:\n\n\tTest: 0\n\n\tFacil: 1\n\n\tNormalillo: 2\n\n\tRanas Astronautas: 3\n");
	do{
		scanf(" %d", &dificultad);
	} while (dificultad != 1 && dificultad != 2 && dificultad != 0 && dificultad != 3);

	mundo = new Mundo(audio,dificultad);
	player = new Player(mundo,audio);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_SMOOTH);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	
	glEnable(GL_NORMALIZE);

	// Ilumination
	luz = new Luz();


	glutSetCursor(GLUT_CURSOR_NONE);




	

}

void Reshape(int w, int h) {
	g_viewport_width = w;
	g_viewport_height = h;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0); //set the perspective (angle of sight, width, height, ,depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {
		exit(0);
	}

	if (key == 'p') {
		g_fps_mode = !g_fps_mode;

		if (g_fps_mode) {
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);
		}
		else {
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}

	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
		g_shift_down = true;
	}
	else {
		g_shift_down = false;
	}

	if (key == 'r' || key == 'R'){
		player->Recargar();
	}

	g_key[key] = true;
}

void KeyboardUp(unsigned char key, int x, int y)
{
	g_key[key] = false;
}

void Timer(int value)
{
	if (g_fps_mode) {
		if (g_key['w'] || g_key['W']) {
			player->Acelerar(velAc);
		}
		else if (g_key['s'] || g_key['S']) {
			player->Acelerar(-velAc);
		}
		else if (!g_key['w'] && !g_key['W'] && !g_key['s'] && !g_key['S']){
			player->Decelerar(velDec);
		}
		
		
		if (g_key['a'] || g_key['A']) {
			player->AcelerarHorizontal(velAc);
		}
		else if (g_key['d'] || g_key['D']) {
			player->AcelerarHorizontal(-velAc);
		}
		else if (!g_key['a'] && !g_key['A'] && !g_key['d'] && !g_key['D']){
			player->DecelerarHorizontal(velDec);
		}


		
		

	}

	glutTimerFunc(1, Timer, 0);
}

void Idle()
{
	Display();
}

void PulsaRaton(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			if (g_fps_mode){
				g_mouse_left_down = true;
				player->Disparo();
				bangCounter = 40;

				switch (rand() % 4){
				case 0:
					bang = bang1;
					break;
				case 1:
					bang = bang2;
					break;
				case 2:
					bang = bang3;
					break;
				case 3:
					bang = bang4;
					break;
				}

				bang_g_viewport_width = (rand() % (g_viewport_width - 200)) + 100;
				bang_g_viewport_height = (rand() % (g_viewport_height - 100)) + 50;
			}
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			g_mouse_right_down = true;
		}
	}
	else if (state == GLUT_UP) {
		if (button == GLUT_LEFT_BUTTON) {
			g_mouse_left_down = false;
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			g_mouse_right_down = false;
		}
	}
}

void MueveRaton(int x, int y)
{
	static bool just_warped = false;

	if (just_warped) {
		just_warped = false;
		return;
	}

	if (g_fps_mode) {
		int dx = x - g_viewport_width / 2;
		int dy = y - g_viewport_height / 2;

		if (dx) {
			player->RotarHorizontal(g_rotation_speed*dx);
		}

		if (dy) {
			player->RotarVertical(g_rotation_speed*dy);
		}

		glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);

		just_warped = true;
	}
}



void Display(void) {

	glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	

	glMatrixMode(GL_PROJECTION); //set the matrix to projection

	glLoadIdentity();
	gluPerspective(60, (GLfloat)g_viewport_width / (GLfloat)g_viewport_height, 0.1, 200.0); //set the perspective (angle of sight, width, height, ,depth)

	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
	glLoadIdentity();

	if (endGame){
	
		mundo->end();

		exit(0);
	}
	

	//Camera Position
	player->Refresh(g_fps_mode);


	//Light
	luz->refresh(LuzPos,SpotDir);

	//World
	mundo->dibujarMundoEstatico();
	mundo->dibujarMundoDinamico();

	//Weapon
	if (g_fps_mode){
		player->dibujaArma();
	}
	else{
		player->dibujarModelo();
	}
	

	//HUD
	sprintf(msg, "Ranas restantes: [%d]", mundo->getRanas().size());

	sprintf(datosHud,"Vida: [%d] Balas: [%d]",player->getVida(),player->getBalas());
	


	hud(msg, g_viewport_width, g_viewport_height,5,20);
	hud(datosHud, g_viewport_width, g_viewport_height, g_viewport_width -400 , g_viewport_height-20);
	if (player->getBalas() > 0){
		if (bangCounter > 0){
			bangCounter--;
			hudBang(bang, g_viewport_width, g_viewport_height, bang_g_viewport_width, bang_g_viewport_height);
		}
	}

	if ((mundo->getRanas().size() <= 0 && dificultad!=0) || player->getVida()<= 0){

		fin(g_viewport_width, g_viewport_height);
		Sleep(500);
		endGame = true;
		

		
	}

	glutSwapBuffers(); //swap the buffers
}




void update(int value) {
	if (g_fps_mode){
	_ranas = mundo->getRanas();
	_cajas = mundo->getCajas();

	

	advance(_ranas, _cajas, (float)TIMER_MS / 1000.0f, _timeUntilUpdatePlayer, mundo,(dificultad!=3));
	glutPostRedisplay();
	}
	glutTimerFunc(TIMER_MS, update, 0);
}

void updatePlayer(int value) {
	if (g_fps_mode){
		_ranas = mundo->getRanas();
		_cajas = mundo->getCajas();


		advancePlayer(player->hitball, player, _ranas, _cajas, (float)TIMER_MS / 1000.0f, _timeUntilUpdatePlayer);
		glutPostRedisplay();
	}
	glutTimerFunc(1, updatePlayer, 0);
}

void chase(int value) {
	if (g_fps_mode){
		_ranas = mundo->getRanas();

		chasePlayer(player->hitball, player, _ranas, chaseNum);

		chaseNum++;
		if (chaseNum >= numRanas){
			chaseNum = 0;
		}

		glutPostRedisplay();
	}
	glutTimerFunc(500, chase, 0);
}


