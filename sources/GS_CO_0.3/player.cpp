#pragma once
#include "player.h"
#include "Mundo.h"
#include "vec3f.h"



Player::Player()
{
	camara = new Camara();
	//hitbox
	hitball = new Ball();
	hitball->pos = Vec3f(0.0f,2.5f,0.0f);
	//ball->pos = Vec3f(8 * randomFloat() - 4, 8 * randomFloat() + 20, 8 * randomFloat() - 4);
	hitball->v = Vec3f(0.0f,0.0f,0.0f);
	hitball->r = 1.0f;
	hitball->color = Vec3f(1.0f,1.0f,1.0f);

	//camara
	camara->Init();

	//Arma
	cargador = new objloader();
	arma = cargador->load("obj/M4.obj");
	armaPosi = glGenLists(2);
	glNewList(armaPosi, GL_COMPILE);
	glLoadIdentity();
	glScalef(0.1f, 0.1f, 0.1f);
	glTranslatef(0.0f, -7.0f, 0.0f);
	glTranslatef(12.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -25.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glCallList(arma);
	glEndList();

}

Player::Player(Mundo *exMundo,sound *audio)
{

	vida = 100;
	balas = 30;

	myAudio = audio;
	myMundo = exMundo;

	dano = myAudio->loadSound("datos/bulletbody.wav");
	disparo= myAudio->loadSound("datos/silencedGun.wav");
	recargar = myAudio->loadSound("datos/recargar.wav");
	myAudio->playSound(dano);

	camara = new Camara();
	//hitbox
	hitball = new Ball();
	hitball->pos = Vec3f(0.0f, 2.5f, 0.0f);
	//ball->pos = Vec3f(8 * randomFloat() - 4, 8 * randomFloat() + 20, 8 * randomFloat() - 4);
	hitball->v = Vec3f(0.0f, 0.0f, 0.0f);
	hitball->r = 1.0f;
	hitball->color = Vec3f(1.0f, 1.0f, 1.0f);

	//camara
	camara->Init();

	//Arma
	cargador = new objloader();
	arma = cargador->load("obj/M4.obj");
	armaPosi = glGenLists(2);
	glNewList(armaPosi, GL_COMPILE);
	glLoadIdentity();
	glScalef(0.1f, 0.1f, 0.1f);
	glTranslatef(0.0f, -7.0f, 0.0f);
	glTranslatef(12.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -25.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glCallList(arma);
	glEndList();

	//Modelo
	cargador = new objloader();
	modelo = cargador->load("obj/modeloPersonaje.obj");


	

}


Player::~Player()
{
}

void Player::Acelerar(float incr){
	camara->Acelerar(incr);
}

void Player::Decelerar(float incr){
	camara->Decelerar(incr);
}

void Player::AcelerarHorizontal(float incr){
	camara->AcelerarHorizontal(incr);
}

void Player::DecelerarHorizontal(float incr){
	camara->DecelerarHorizontal(incr);
}

void Player::RotarHorizontal(float incr){
	camara->RotarHorizontal(incr);
}

void Player::RotarVertical(float incr){
	camara->RotarVertical(incr);
}

void Player::Refresh(){
	
	camara->Refresh();
}

void Player::Refresh(bool fpsMode){
	
	
	camara->Refresh(fpsMode);

	
}

void Player::dibujaArma(){
	glPushMatrix();
	glClear(GL_DEPTH_BUFFER_BIT);
	glCallList(armaPosi);
	glPopMatrix();


	

}

void Player::dibujarModelo(){
	Vec3f *pos=camara->GetPos();
	glPushMatrix();
	glTranslatef(pos->v[0], pos->v[1], pos->v[2]);
	glCallList(modelo);
	glPopMatrix();
}

void Player::Disparo(){
	if (balas > 0){
		balas--;

		//sndPlaySound("datos/silencedGun.wav", SND_ASYNC | SND_FILENAME );
		//myAudio->playSound(disparo, *camara->GetPos(), *camara->GetDir());
		myAudio->playSound(disparo);
		myMundo->disparoPlayer(*(camara->GetDir()), *(camara->GetPos()));
	}
}

void Player::Recargar(){

	myAudio->playSound(recargar);
	balas = 30;
	
}

int Player::getBalas(){
	return balas;
}

int Player::getVida(){
	return vida;
}

void Player::RecibirDano(){
	
	vida -= 10;

	myAudio->playSound(dano);
	//myAudio->playSound(dano, *camara->GetPos(), *camara->GetDir());
	//sndPlaySound("datos/bulletbody.wav", SND_ASYNC | SND_FILENAME);


}