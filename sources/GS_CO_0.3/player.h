#pragma once
#include "Camara.h"
#include "objLoader.h"
#include "sound.h"

class Mundo;
struct Ball;



class Player
{
public:
	Player();
	Player(Mundo *myMundo,sound *audio);
	~Player();

	Mundo *myMundo;
	sound *myAudio;
	Ball *hitball;
	Camara *camara;
	objloader *cargador;
	GLuint arma;
	GLuint armaPosi;
	GLuint modelo;
	
	//Variables
	int vida;
	int balas;


	//Sonidos
	unsigned int dano;
	unsigned int disparo;
	unsigned int recargar;

	int Player::getVida();
	int Player::getBalas();



	//Actions
	void Player::Disparo();
	void Player::RecibirDano();
	void Player::Recargar();

	//Movement settings
	const float velMov = 0.1;
	const float g_rotation_speed = M_PI / 180 * 0.1;
	const float velAc = 0.0075;
	const float velDec = -0.0025;

	//movimiento
	void Player::Acelerar(float incr);
	void Player::Decelerar(float incr);
	void Player::AcelerarHorizontal(float incr);
	void Player::DecelerarHorizontal(float incr);
	void Player::RotarHorizontal(float angulo);
	void Player::RotarVertical(float angulo);

	//refresco
	void Refresh();
	void Refresh(bool fpsMode);
	void dibujaArma();
	void dibujarModelo();

};

