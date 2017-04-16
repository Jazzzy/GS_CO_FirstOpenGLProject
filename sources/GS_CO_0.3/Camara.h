#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#ifndef M_PI
#define M_PI       3.14159265358979323846264338328      // Pi 
#endif

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923132169164      // Pi/2 
#endif

#ifndef M_PI_4
#define M_PI_4     0.78539816339744830961566084582      // Pi/4 
#endif

#include "vec3f.h"
#include <stdio.h>
#include <math.h>
#include <C:\glut\glut.h>

class Camara{
public:
	Camara() { Init(); }

	//Setters e Getters
	void SetPos(float x, float y, float z);
	void SetPos(Vec3f posicion);
	Vec3f* Camara::GetPos();
	Vec3f* Camara::GetDir();
	void GetDirectionVector(float x, float y, float z);
	void SetRotHoriz(float angulo);
	void SetRotVer(float angulo);
	void SetVel(float vel);
	void NegVel();

	void Init();
	void Refresh();
	void Refresh(bool fpsMode);
	

	void Camara::Acelerar(float incr);
	void Camara::Decelerar(float incr);
	void Camara::AcelerarHorizontal(float incr);
	void Camara::DecelerarHorizontal(float incr);
	void Mover(float incr);
	void MoverHorizontal(float incr);
	void MoverVertical(float incr);
	void RotarHorizontal(float angulo);
	void RotarVertical(float angulo);

private:
	float posx, posy, posz;   // Position
    float dirx, diry, dirz; // Direction vector of where we are looking at
	float angHor, angVer; // Various rotation angulos
	float horiz_dirx, horiz_dirz; // Always 90 degree to direction vector
	float velocidad;
	float velocidadHoriz;
	float limite;
};

#endif
