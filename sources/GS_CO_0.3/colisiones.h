#pragma once
using namespace std;

#include <math.h>
#include <stdio.h>
#include <C:\glut\glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <set>
#include <stdlib.h>
#include <vector>
#include "vec3f.h"
#include "player.h"
#include <al\al.h>
#include <al\alc.h>
#include "sound.h"
#include "Mundo.h"


class Player;

enum Wall { WALL_LEFT, WALL_RIGHT, WALL_FAR, WALL_NEAR, WALL_TOP, WALL_BOTTOM };


//Si cambiamos el tama�o de la caja que dibujamos tenemos que cambiar aqu� tambi�n
//El tama�o de la caja para los muros de las colisiones
const float GRAVITY = 100.0f;
const float BOX_SIZE = 100.0f;
const float TIME_BETWEEN_UPDATES = 0.01f;
const int TIMER_MS = 25;
//const int TIMER_MS = 1;


struct Ball {
	Vec3f v; //Velocidad
	Vec3f pos; //Posicion
	float r; //Radio
	Vec3f color;
	ALuint source;
};

struct Box {
	Vec3f v; //Velocidad
	Vec3f pos; //Posicion
	float side; //Lado del cubo
	Vec3f color;
	Vec3f minBounds;
	Vec3f maxBounds;
};

//Pares de las bolas
struct BallPar {
	Ball* ball1;
	Ball* ball2;
};

struct BolaACajaPar {
	Ball* ball;
	Box* box;
};

struct BolaAMuroPar {
	Ball* ball;
	Wall wall;
};

//Pares de las cajas
struct CajaACajaPar {
	Box* box1;
	Box* box2;
};

//struct CajaABolaPar {
//	Box* ball1;
//	Box* ball2;
//};

struct CajaAMuroPar {
	Box* box;
	Wall wall;
};

struct PlayerAMuroPar {
	Ball* player;
	Wall wall;
};

struct PlayerABolaPar {
	Ball* player;
	Ball* ball;
};

struct PlayerACajaPar {
	Ball* player;
	Box* box;
};



//Disparo de jugador
bool checkDisparo(Vec3f direccion, Vec3f origen, vector<Ball*> &balls);

//dibuja la caja semitransparente
void drawCaja(void);

//Dibujamos un cubo con las aristas del tama�o que queramos.
void drawCube(float size);

//Devolvemos un float entre 0 y 1
float randomFloat();


//Pone todos los pares de bolas que existen en el vector de colisiones potenciales
//De esta forma comprobaremos si todas las bolas chocan entre si
//Este m�todo es muy lento y he considerado intentar hacerlo con el particionado del
//espacio que menciona en teor�a, pero la complejidad me parec�a importante para
//el tiempo que ten�a.
void potencialBolaABolaColisiones(vector<BallPar> &potencialColisiones, vector<Ball*> &balls);


/*
De la misma forma que la funci�n anterior, aqu� ponemos todos los pares posibles de
bolas y muros que existen en nuestro sistema en el vector de colisiones potenciales.
Es simple pero bastante ineficiente
*/
void potencialBolaMuroColisiones(vector<BolaAMuroPar> &potencialColisiones, vector<Ball*> &balls);



//Esta funci�n simplemente mueve las bolas en la direcci�n que ten�an
//La variable dt se usa para aumentar o diminuir su velocidad si lo deseamos
void moverBolas(vector<Ball*> &balls, float dt);

//Esta es una funci�n encontrada en un foro (StackOverflow) adaptada a nuestro caso que
//cambia el vector director del movimiento de las bolas rest�ndole
//Un nuevo vector que solo tiene componente y, en la que guarda el valor de la fuerza
//de la gravedad, de esta forma podemos hacer que las bolas caigan al fondo de la
//caja
void gravedad(vector<Ball*> &balls);

/*
Esta funci�n es la que realmente calcula si dos bolas est�n chocando o no.
*/
bool testColisionBolaABola(Ball* b1, Ball* b2);

/*Esta funci�n es la que hace todas las llamadas a la funci�n anterior necesarias
para ver si que bolas est�n chocando.
*/
void ColisionesBolaABola(vector<Ball*> &balls);


//Simplemente devolvemos las normales correspondientes a cada muro
Vec3f normalMuro(Wall wall);

//Miramos si una bola y un muro est�n colisionando
bool testColisionBolaAMuro(Ball* ball, Wall wall);

//Igual que colisiones bola a bola pero para los pares bola/muro
void ColisionesBolaAMuro(vector<Ball*> &balls);

//Actualiza el estado de las bolas haciendo las llamadas a lasfunciones que se encargan de cada cosa.
void performUpdate(vector<Ball*> &balls);

//Avanza el estado de las bolas
void advance(vector<Ball*> &balls, vector<Box*> &boxes, float t, float &timeUntilUpdate, Mundo *mundo,bool gravedad);

//Avanza el estado del jugador si este choca
void advancePlayer(Ball* playerBall, Player* jugador, vector<Ball*> &balls, vector<Box*> &boxes, float t, float &timeUntilUpdate);

//Para que las ranas persiguan al jugador
void chasePlayer(Ball* playerBall, Player* jugador, vector<Ball*> &balls, int rana);

