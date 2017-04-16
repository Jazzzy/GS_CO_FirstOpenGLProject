#pragma once
#include "colisiones.h"
#include "objLoader.h"
#include "vec3f.h"
#include <math.h>
#include "sound.h"
#include "Luz.h"

#define numRanas 5



struct Ball;
struct Box;

class Player;

class Mundo
{
public:
	Mundo();
	Mundo(sound *audio,int dificultad);
	~Mundo();

	int suelo;
	int caja;
	int rana;
	int mundoEstatico;
	int fachada;
	int foco;
	

	float rotFoco;

	

	unsigned int bump;
	unsigned int BSO;
	unsigned int FIN;
	unsigned int HIT;

	sound *myAudio;
	objloader *cargador;

	ALCdevice *device;
	ALCcontext *context;
	ALuint bufferRanas;

	vector<Ball*> _ranas;
	
	vector<Box*> _cajas;

	void Mundo::Malla();
	void end();
	void Mundo::Suelo();

	void Mundo::dibujarMundoEstatico();

	void Mundo::listaDibujarMundoEstatico();

	void Mundo::dibujarMundoDinamico();

	float Mundo::rotacionRana(Ball* bola);

	vector<Ball*> Mundo::getRanas();

	vector<Box*> Mundo::getCajas();

	void Mundo::disparoPlayer(Vec3f direccion, Vec3f origen);

	void Mundo::IniciaSonido();

};

