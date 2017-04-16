#pragma once
#include "Camara.h"

void Camara::Init()
{
	angHor = 0.0;
	angVer = 0.0;

	SetPos(0, 2.5f, 0);

	velocidad=0.0f;
	velocidadHoriz = 0.0f;
	limite=0.04f;
}




void Camara::Refresh()
{
	
	float lx = cos(angHor);
	float ly = sin(angVer);
	float lz = sin(angHor);


	if (velocidadHoriz != 0 && velocidad != 0){
	
		posx = posx + (velocidad/2)*lx;
		//Esta linea esta comentada pra que non nos movamos no eje y
		//posy = posy + incr*ly;
		posz = posz + (velocidad / 2)*lz;

		dirx = cos(angHor);
		diry = sin(angVer);
		dirz = sin(angHor);

		//Igual pero restamos pi/2 para facelo perpendicular
		horiz_dirx = cos(angHor - M_PI_2);
		horiz_dirz = sin(angHor - M_PI_2);

		posx = posx + (velocidadHoriz / 2)*horiz_dirx;
		posz = posz + (velocidadHoriz / 2)*horiz_dirz;
	
	
	
	}
	else{

		posx = posx + velocidad*lx;
		//Esta linea esta comentada pra que non nos movamos no eje y
		//posy = posy + incr*ly;
		posz = posz + velocidad*lz;

		dirx = cos(angHor);
		diry = sin(angVer);
		dirz = sin(angHor);

		//Igual pero restamos pi/2 para facelo perpendicular
		horiz_dirx = cos(angHor - M_PI_2);
		horiz_dirz = sin(angHor - M_PI_2);

		posx = posx + velocidadHoriz*horiz_dirx;
		posz = posz + velocidadHoriz*horiz_dirz;

	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posx, posy, posz, posx + dirx, posy + diry, posz + dirz, 0.0,1.0,0.0);

}

void Camara::Refresh(bool fpsMode)
{

	float lx = cos(angHor);
	float ly = sin(angVer);
	float lz = sin(angHor);


	if (velocidadHoriz != 0 && velocidad != 0){

		posx = posx + (velocidad / 2)*lx;
		//Esta linea esta comentada pra que non nos movamos no eje y
		//posy = posy + incr*ly;
		posz = posz + (velocidad / 2)*lz;

		dirx = cos(angHor);
		diry = sin(angVer);
		dirz = sin(angHor);

		//Igual pero restamos pi/2 para facelo perpendicular
		horiz_dirx = cos(angHor - M_PI_2);
		horiz_dirz = sin(angHor - M_PI_2);

		posx = posx + (velocidadHoriz / 2)*horiz_dirx;
		posz = posz + (velocidadHoriz / 2)*horiz_dirz;



	}
	else{

		posx = posx + velocidad*lx;
		//Esta linea esta comentada pra que non nos movamos no eje y
		//posy = posy + incr*ly;
		posz = posz + velocidad*lz;

		dirx = cos(angHor);
		diry = sin(angVer);
		dirz = sin(angHor);

		//Igual pero restamos pi/2 para facelo perpendicular
		horiz_dirx = cos(angHor - M_PI_2);
		horiz_dirz = sin(angHor - M_PI_2);

		posx = posx + velocidadHoriz*horiz_dirx;
		posz = posz + velocidadHoriz*horiz_dirz;

	}
	if (fpsMode == true){
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		/*GLfloat LuzPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat SpotDir[] = { 0.0f, 0.0f, -1.0f };
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHTING);
		glLightfv(GL_LIGHT1, GL_POSITION, LuzPos);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, SpotDir);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHTING);

		
		GLfloat SpotDir2[] = { 0.0f, 0.0f, -1.0f };
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHTING);
		glLightfv(GL_LIGHT2, GL_POSITION, LuzPos);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, SpotDir2);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHTING);
*/



	



		gluLookAt(posx, posy, posz, posx + dirx, posy + diry, posz + dirz, 0.0, 1.0, 0.0);
	}
	else{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(-48.0f, 48.0f, 48.0f, 0.0f, 0.0f, 0.0f, 0.0, 1.0, 0.0);
	}

}


void Camara::SetPos(float x, float y, float z)
{
	posx = x;
	posy = y;
	posz = z;

	Refresh();
}

void Camara::SetVel(float vel){
	velocidad = vel;
	velocidadHoriz = vel;
}

void Camara::NegVel(){
	velocidad = -1.0f*velocidad;
	velocidadHoriz = -1.0f*velocidadHoriz;
}

void Camara::SetPos(Vec3f posicion)
{
	posx = posicion[0];
	posy = posicion[1];
	posz = posicion[2];

	Refresh();
}

Vec3f* Camara::GetPos()
{
	return new Vec3f(posx, posy, posz);
}

Vec3f* Camara::GetDir()
{
	return new Vec3f(dirx, diry, dirz);
}

void Camara::GetDirectionVector(float x, float y, float z)
{
    x = dirx;
    y = diry;
    z = dirz;
}

void Camara::Mover(float incr)
{

	float lx = cos(angHor);
    float ly = sin(angVer);
	float lz = sin(angHor);

	posx = posx + incr*lx;
	//Esta linea esta comentada pra que non nos movamos no eje y
	//posy = posy + incr*ly;
	posz = posz + incr*lz;

	Refresh();
	//Ver();
}

void Camara::Acelerar(float incr)
{

	float lx = cos(angHor);
	float ly = sin(angVer);
	float lz = sin(angHor);

	velocidad += incr;
	if (velocidad >= limite){
		velocidad = limite;
	}
	if (velocidad <= -limite){
		velocidad = -limite;
	}



	Mover(velocidad);

	Refresh();
	//Ver();
}

void Camara::Decelerar(float incr)
{

	incr = abs(incr);

	float lx = cos(angHor);
	float ly = sin(angVer);
	float lz = sin(angHor);

	if (velocidad == 0.0f){
		return;
	}

	if (velocidad > 0.0f){
		velocidad -= incr;
		if (velocidad <= 0.0f){
			velocidad = 0.0f;
		}
	}else if (velocidad < 0.0f){
		velocidad += incr;
		if (velocidad >= 0.0f){
			velocidad = 0.0f;
		}
	}
		


	Mover(velocidad);

	Refresh();
	//Ver();
}


void Camara::MoverHorizontal(float incr)
{
	posx = posx + incr*horiz_dirx;
	posz = posz + incr*horiz_dirz;

	Refresh();
}


void Camara::AcelerarHorizontal(float incr)
{

	
	velocidadHoriz += incr;
	if (velocidadHoriz >= limite){
		velocidadHoriz = limite;
	}
	if (velocidadHoriz <= -limite){
		velocidadHoriz = -limite;
	}


	MoverHorizontal(velocidadHoriz);

	Refresh();
	//Ver();
}

void Camara::DecelerarHorizontal(float incr){
	
	incr = abs(incr);


	if (velocidadHoriz == 0.0f){
		return;
	}

	if (velocidadHoriz > 0.0f){
		velocidadHoriz -= incr;
		if (velocidadHoriz <= 0.0f){
			velocidadHoriz = 0.0f;
		}
	}
	else if (velocidadHoriz < 0.0f){
		velocidadHoriz += incr;
		if (velocidadHoriz >= 0.0f){
			velocidadHoriz = 0.0f;
		}
	}



	MoverHorizontal(velocidadHoriz);

	Refresh();


}


void Camara::MoverVertical(float incr)
{
	posy = posy + incr;

	Refresh();
}

void Camara::RotarHorizontal(float angulo)
{
	angHor += angulo;

	Refresh();
}

void Camara::RotarVertical(float angulo)
{
    const float limit = 89.0 * M_PI / 180.0;

	angVer -= angulo;

    if(angVer < -limit)
        angVer = -limit;

    if(angVer > limit)
        angVer = limit;

	Refresh();
}


//Estes dous setters non os usamos ahora mismo pero poden ser de utilidad
void Camara::SetRotHoriz(float angulo)
{
	angHor = angulo;

	Refresh();
}

void Camara::SetRotVer(float angulo)
{
    angVer = angulo;

    Refresh();
}
