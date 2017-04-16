#pragma once
#include "colisiones.h"



//dibuja la caja semitransparente
void drawCaja(void){
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glutWireCube(12.0f);
	glFrontFace(GL_CW);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glutSolidCube(12.0f);
	//drawCube(12.0f);
	glFrontFace(GL_CCW);
	glPopMatrix();
}

//Dibujamos un cubo con las aristas del tamaño que queramos.
void drawCube(float size)
{
	glPushMatrix();
	float difamb[] = { 1.0, 0.5, 0.3, 1.0 };
	glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
	//glFrontFace(GL_CCW);
	glBegin(GL_QUADS);
	//glBegin(GL_LINES);
	//front face
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);

	//left face
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);

	//back face
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);

	//right face
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);

	//top face
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);

	//bottom face
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
	glPopMatrix();
}


//Devolvemos un float entre 0 y 1
float randomFloat() {
	return (float)rand() / ((float)RAND_MAX + 1);
}



//Pone todos los pares de bolas que existen en el vector de colisiones potenciales
//De esta forma comprobaremos si todas las bolas chocan entre si
//Este método es muy lento y he considerado intentar hacerlo con el particionado del
//espacio que menciona en teoría, pero la complejidad me parecía importante para
//el tiempo que tenía.
void potencialBolaABolaColisiones(vector<BallPar> &potencialColisiones,
	vector<Ball*> &balls) {


	for (unsigned int i = 0; i < balls.size(); i++) {
		for (unsigned int j = i + 1; j < balls.size(); j++) {
			BallPar bp;
			bp.ball1 = balls[i];
			bp.ball2 = balls[j];
			potencialColisiones.push_back(bp);
		}
	}

}

void potencialPlayerABolaColisiones(vector<PlayerABolaPar> &potencialColisiones,
	vector<Ball*> &balls, Ball* player) {



	for (unsigned int j = 0; j < balls.size(); j++) {
		PlayerABolaPar bp;
		bp.player = player;
		bp.ball = balls[j];
		potencialColisiones.push_back(bp);
	}


}

//Igual pero para pares de bolas y cajas
void potencialBolaACajaColisiones(vector<BolaACajaPar> &potencialColisiones, vector<Ball*> &balls, vector<Box*> &boxes) {


	for (unsigned int i = 0; i < balls.size(); i++) {
		for (unsigned int j = 0; j < boxes.size(); j++) {
			BolaACajaPar bp;
			bp.ball = balls[i];
			bp.box = boxes[j];
			potencialColisiones.push_back(bp);
		}
	}

}

//Igual pero para pares de cajas
void potencialCajaACajaColisiones(vector<CajaACajaPar> &potencialColisiones, vector<Box*> &boxes) {


	for (unsigned int i = 0; i < boxes.size(); i++) {
		for (unsigned int j = i + 1; j < boxes.size(); j++) {
			CajaACajaPar bp;
			bp.box1 = boxes[i];
			bp.box2 = boxes[j];
			potencialColisiones.push_back(bp);
		}
	}

}

void potencialPlayerACajaColisiones(vector<PlayerACajaPar> &potencialColisiones, vector<Box*> &boxes, Ball* player) {



	for (unsigned int j = 0; j < boxes.size(); j++) {
		PlayerACajaPar bp;
		bp.player = player;
		bp.box = boxes[j];
		potencialColisiones.push_back(bp);
	}


}

//Igual pero para cajas y muros
void potencialCajaAMuroColisiones(vector<CajaAMuroPar> &potencialColisiones, vector<Box*> &boxes) {

	Wall walls[] =
	{ WALL_LEFT, WALL_RIGHT, WALL_FAR, WALL_NEAR, WALL_TOP, WALL_BOTTOM };

	for (unsigned int i = 0; i < boxes.size(); i++) {
		for (unsigned int j = 0; j < 6; j++) {
			CajaAMuroPar bp;
			bp.box = boxes[i];
			bp.wall = walls[j];
			potencialColisiones.push_back(bp);
		}
	}

}



/*
De la misma forma que la función anterior, aquí ponemos todos los pares posibles de
bolas y muros que existen en nuestro sistema en el vector de colisiones potenciales.
Es simple pero bastante ineficiente
*/
void potencialBolaMuroColisiones(vector<BolaAMuroPar> &potencialColisiones,
	vector<Ball*> &balls) {

	Wall walls[] =
	{ WALL_LEFT, WALL_RIGHT, WALL_FAR, WALL_NEAR, WALL_TOP, WALL_BOTTOM };
	for (unsigned int i = 0; i < balls.size(); i++) {
		for (int j = 0; j < 6; j++) {
			BolaAMuroPar bmp;
			bmp.ball = balls[i];
			bmp.wall = walls[j];
			potencialColisiones.push_back(bmp);
		}
	}

}

void potencialPlayerAMuroColisiones(vector<PlayerAMuroPar> &potencialColisiones,
	Ball* player) {

	Wall walls[] =
	{ WALL_LEFT, WALL_RIGHT, WALL_FAR, WALL_NEAR, WALL_TOP, WALL_BOTTOM };

	for (int j = 0; j < 6; j++) {
		PlayerAMuroPar bmp;
		bmp.player = player;
		bmp.wall = walls[j];
		potencialColisiones.push_back(bmp);
	}
}



//Esta función simplemente mueve las bolas en la dirección que tenían
//La variable dt se usa para aumentar o diminuir su velocidad si lo deseamos
void moverBolas(vector<Ball*> &balls, float dt) {
	for (unsigned int i = 0; i < balls.size(); i++) {
		Ball* ball = balls[i];
		ball->pos += ball->v * dt;
		alSource3f(ball->source, AL_POSITION, ball->pos[0], ball->pos[1], ball->pos[2]);
		// check for errors
		alSource3f(ball->source, AL_VELOCITY, ball->v[0], ball->v[1], ball->v[2]);
		// check for errors
	}
}

//Igual pero para cajas
void moverCajas(vector<Box*> &boxes, float dt) {
	for (unsigned int i = 0; i < boxes.size(); i++) {
		Box* box = boxes[i];
		box->pos += box->v * dt;
		box->minBounds += box->v * dt;
		box->maxBounds += box->v * dt;
	}
}


//Esta es una función encontrada en un foro (StackOverflow) adaptada a nuestro caso que
//cambia el vector director del movimiento de las bolas restándole
//Un nuevo vector que solo tiene componente y, en la que guarda el valor de la fuerza
//de la gravedad, de esta forma podemos hacer que las bolas caigan al fondo de la
//caja
void gravedad(vector<Ball*> &balls, vector<Box*> &boxes) {
	for (unsigned int i = 0; i < balls.size(); i++) {
		Ball* ball = balls[i];
		ball->v -= Vec3f(0, GRAVITY * TIME_BETWEEN_UPDATES, 0);
	}

	/*for (unsigned int i = 0; i < boxes.size(); i++) {
		Box* box = boxes[i];
		box->v -= Vec3f(0, GRAVITY * TIME_BETWEEN_UPDATES, 0);
		}*/

}

/*
Esta función es la que realmente calcula si dos bolas están chocando o no.
*/
bool testColisionBolaABola(Ball* b1, Ball* b2) {

	float r = b1->r + b2->r;
	//Aqui miramos si el modulo al cuadrado de la resta de los vectores es menor que
	//la suma de sus radios al cuadrado, si es así consideramos que están chocando.
	if ((b1->pos - b2->pos).magnitudeSquared() < r * r) {

		//Aquí comprobamos si realmente las bolas se mueven una hacia la otra

		Vec3f diffVelocidad = b1->v - b2->v;
		Vec3f desplazamiento = b1->pos - b2->pos;

		//Si este calculo es positivo consideramos que no existe choque pues la bola que va
		//"Adelante" va lo sudifientemente rápido como para no hacer que la distancia entre las dos sea
		//lo suficientemente pequeña para ser choque.
		return diffVelocidad.dot(desplazamiento) < 0;
	}
	else
		return false;
}

bool testColisionPlayerABola(Ball* b1, Ball* b2) {

	float r = b1->r + b2->r;
	r *= 1.7f;
	//Aqui miramos si el modulo al cuadrado de la resta de los vectores es menor que
	//la suma de sus radios al cuadrado, si es así consideramos que están chocando.
	if ((b1->pos - b2->pos).magnitudeSquared() < ((r * r))) {

		//Aquí comprobamos si realmente las bolas se mueven una hacia la otra

		Vec3f diffVelocidad = b1->v - b2->v;
		Vec3f desplazamiento = b1->pos - b2->pos;

		//Si este calculo es positivo consideramos que no existe choque pues la bola que va
		//"Adelante" va lo sudifientemente rápido como para no hacer que la distancia entre las dos sea
		//lo suficientemente pequeña para ser choque.
		return diffVelocidad.dot(desplazamiento) < 0;
	}
	else
		return false;
}


float maximo(float a, float b){
	if (a > b) return a;
	else if (b > a) return b;
	else return a;
}

float minimo(float a, float b){
	if (a < b) return a;
	else if (b < a) return b;
	else return a;
}


//Igual pero para bolas y cajas
bool testColisionBolaACaja(Ball* ball, Box* box) {

	bool face = false;
	int i;
	float a = 0.0f;
	float b = 0.0f;
	float dmin = 0.0f;
	float dmax = 0.0f;
	float r2 = pow(ball->r, 2);

	for (i = 0; i < 3; i++){
		a = pow(ball->pos[i] - box->minBounds[i], 2);
		b = pow(ball->pos[i] - box->maxBounds[i], 2);
		dmax += maximo(a, b);
		if (ball->pos[i] < box->minBounds[i]){
			face = true;
			dmin += a;
		}
		else if (ball->pos[i] > box->maxBounds[i]){
			face = true;
			dmin += b;
		}
		else if (minimo(a, b) <= r2){
			face = true;
		}
	}

	if (face && (dmin <= r2) && (r2 <= dmax)){


		return true;

	}
	else {
		return false;
	}


	//Algoritmo sacado de http://tog.acm.org/resources/GraphicsGems/gems/BoxSphere.c

	/*
	A Simple Method for Box-Sphere Intersection Testing
	by Jim Arvo
	from "Graphics Gems", Academic Press, 1990
	*/

}

//Igual pero para bolas y cajas
bool testColisionCajaACaja(Box* A, Box* B) {

	return (A->minBounds.v[0] <= B->maxBounds.v[0]) && (A->maxBounds.v[0] >= B->minBounds.v[0])
		&& (A->minBounds.v[1] <= B->maxBounds.v[1]) && (A->maxBounds.v[1] >= B->minBounds.v[1])
		&& (A->minBounds.v[2] <= B->maxBounds.v[2]) && (A->maxBounds.v[2] >= B->minBounds.v[2]);


}




/*Esta función es la que hace todas las llamadas a la función anterior necesarias
para ver si que bolas están chocando.
*/
void ColisionesBolaABola(vector<Ball*> &balls) {
	vector<BallPar> bps;
	potencialBolaABolaColisiones(bps, balls);
	for (unsigned int i = 0; i < bps.size(); i++) {
		BallPar bp = bps[i];

		Ball* b1 = bp.ball1;
		Ball* b2 = bp.ball2;
		if (testColisionBolaABola(b1, b2)) {
			float x1, x2, x3;

			Vec3f desplazamiento = (b2->pos - b1->pos);

			Vec3f desplazamientoUnitario = (b1->pos - b2->pos).normalize();


			for (unsigned int j = 0; j < 3; j++) {

				float mag = desplazamiento.magnitude();
				//Para que as bolas non se metan dentro de bolas
				if (mag < ((b1->r * 0.80) + (b2->r *0.80))){
					if (desplazamiento[j] < 0){
						x1 = b1->pos[j] - ((b1->r));
						x2 = b2->pos[j] + ((b1->r) / 2);

						x3 = abs(x2 - x1);
						x3 = (x3 / 2);
						b1->pos[j] += x3;
						b2->pos[j] -= x3;
					}
					else if (desplazamiento[j] > 0){
						x1 = b1->pos[j] + ((b1->r));
						x2 = b2->pos[j] - (b1->r);

						x3 = abs(x2 - x1);
						x3 = (x3 / 2);
						b1->pos[j] -= x3;
						b2->pos[j] += x3;
					}
				}


			}



			b1->v -= 2 * desplazamientoUnitario * b1->v.dot(desplazamientoUnitario);
			b2->v -= 2 * desplazamientoUnitario * b2->v.dot(desplazamientoUnitario);
		}
	}
}

void ColisionesPlayerABola(Ball* player, Player *jugador, vector<Ball*> &balls) {
	vector<PlayerABolaPar> bps;
	potencialPlayerABolaColisiones(bps, balls, player);
	for (unsigned int i = 0; i < bps.size(); i++) {
		PlayerABolaPar bp = bps[i];

		Ball* b1 = bp.player;
		Ball* b2 = bp.ball;
		if (testColisionPlayerABola(b1, b2)) {
			float x1, x2, x3;

			Vec3f desplazamiento = (b2->pos - b1->pos);

			Vec3f desplazamientoUnitario = (b1->pos - b2->pos).normalize();


			for (unsigned int j = 0; j < 3; j++) {

				float mag = desplazamiento.magnitude();
				//Para que as bolas non se metan dentro de bolas
				if (mag < ((b1->r * 0.80) + (b2->r *0.80))){
					if (desplazamiento[j] < 0){
						x1 = b1->pos[j] - ((b1->r));
						x2 = b2->pos[j] + ((b1->r) / 2);

						x3 = abs(x2 - x1);
						x3 = (x3 / 2);
						//b1->pos[j] += x3;
						b2->pos[j] -= x3;
					}
					else if (desplazamiento[j] > 0){
						x1 = b1->pos[j] + ((b1->r));
						x2 = b2->pos[j] - (b1->r);

						x3 = abs(x2 - x1);
						x3 = (x3 / 2);
						//b1->pos[j] -= x3;
						b2->pos[j] += x3;
					}
				}


			}



			//b1->v -= 2 * desplazamientoUnitario * b1->v.dot(desplazamientoUnitario);
			b2->v -= 2 * desplazamientoUnitario * b2->v.dot(desplazamientoUnitario);
			jugador->RecibirDano();
			printf("Recibes golpe de una rana!!\n");

		}
	}
}

void ColisionesBolaACaja(vector<Ball*> &balls, vector<Box*> &boxes) {
	vector<BolaACajaPar> bps;
	potencialBolaACajaColisiones(bps, balls, boxes);


	for (unsigned int i = 0; i < bps.size(); i++) {
		BolaACajaPar bp = bps[i];

		Ball* b1 = bp.ball;
		Box* b2 = bp.box;
		if (testColisionBolaACaja(b1, b2)) {


			float x1, x2, x3;

			Vec3f desplazamiento = (b2->pos - b1->pos);

			Vec3f desplazamientoUnitario = (b1->pos - b2->pos).normalize();


			for (unsigned int j = 0; j < 3; j++) {

				float mag = desplazamiento.magnitude();
				//Para que as bolas non se metan dentro de caixas
				if (mag < ((b2->side / 2) + (b1->r)) - 0.10f){
					if (desplazamiento[j] < 0){
						x1 = b1->pos[j] - ((b1->r));
						x2 = b2->pos[j] + ((b2->side) / 2);

						x3 = abs(x2 - x1);
						x3 = (x3 / 2);
						b1->pos[j] += x3;
						//b2->pos[j] -= x3;
						//b2->minBounds[j] -= x3;
						//b2->maxBounds[j] -= x3;
					}
					else if (desplazamiento[j] > 0){
						x1 = b1->pos[j] + ((b1->r));
						x2 = b2->pos[j] - (b2->side / 2);

						x3 = abs(x2 - x1);
						x3 = (x3 / 2);
						b1->pos[j] -= x3;
						//b2->pos[j] += x3;
						//b2->minBounds[j] += x3;
						//b2->maxBounds[j] += x3;
					}
				}


			}



			b1->v -= 2 * desplazamientoUnitario * b1->v.dot(desplazamientoUnitario);
			b2->v -= 2 * desplazamientoUnitario * b2->v.dot(desplazamientoUnitario);
		}
	}
}


void ColisionesPlayerACaja(Ball* player, Player *jugador, vector<Box*> &boxes) {
	vector<PlayerACajaPar> bps;
	potencialPlayerACajaColisiones(bps, boxes, player);


	for (unsigned int i = 0; i < bps.size(); i++) {
		PlayerACajaPar bp = bps[i];

		Ball* b1 = bp.player;
		Box* b2 = bp.box;
		if (testColisionBolaACaja(b1, b2)) {


			float x1, x2, x3;

			Vec3f desplazamiento = (b2->pos - b1->pos);

			Vec3f desplazamientoUnitario = (b1->pos - b2->pos).normalize();


			//for (unsigned int j = 0; j < 3; j += 2) {

			//	float mag = desplazamiento.magnitude();
			//	//Para que as bolas non se metan dentro de caixas
			//	if (mag < ((b2->side / 2) + (b1->r)) - 0.10f){
			//		if (desplazamiento[j] < 0){
			//			x1 = b1->pos[j] - ((b1->r));
			//			x2 = b2->pos[j] + ((b2->side) / 2);

			//			x3 = abs(x2 - x1);
			//			x3 = (x3 / 2);
			//			b1->pos[j] += x3;
			//			//b2->pos[j] -= x3;
			//			//b2->minBounds[j] -= x3;
			//			//b2->maxBounds[j] -= x3;
			//		}
			//		else if (desplazamiento[j] > 0){
			//			x1 = b1->pos[j] + ((b1->r));
			//			x2 = b2->pos[j] - (b2->side / 2);

			//			x3 = abs(x2 - x1);
			//			x3 = (x3 / 2);
			//			b1->pos[j] -= x3;
			//			//b2->pos[j] += x3;
			//			//b2->minBounds[j] += x3;
			//			//b2->maxBounds[j] += x3;
			//		}
			//	}

			//}

			//printf("Tenemos colision de Cajas\n");

			desplazamiento /= 15;
			float altura = b1->pos[1];
			b1->pos -= desplazamiento;
			b1->pos[1] = altura;

			Vec3f* posicionJug = jugador->camara->GetPos();
			*posicionJug = b1->pos;
			jugador->camara->SetPos(*posicionJug);
			jugador->camara->SetVel(0.0f);

			//jugador->camara->NegVel();

		}
	}
}

void ColisionesCajaACaja(vector<Box*> &boxes) {
	vector<CajaACajaPar> bps;
	potencialCajaACajaColisiones(bps, boxes);

	for (unsigned int i = 0; i < bps.size(); i++) {
		CajaACajaPar bp = bps[i];
		Box* b1 = bp.box1;
		Box* b2 = bp.box2;

		if (testColisionCajaACaja(b1, b2)) {

			float x1, x2, x3;

			Vec3f desplazamiento = (b2->pos - b1->pos);

			Vec3f desplazamientoUnitario = (b1->pos - b2->pos).normalize();


			for (unsigned int j = 0; j < 3; j++) {

				float mag = desplazamiento.magnitude();
				//Para que as caixan non se metan dentro de outras
				if (mag < b1->side - 0.10f){
					if (desplazamiento[j] < 0){
						x1 = b1->pos[j] - ((b1->side) / 2);
						x2 = b2->pos[j] + ((b2->side) / 2);

						x3 = abs(x2 - x1);
						x3 = (x3 / 2);
						b1->pos[j] += x3;
						b1->minBounds[j] += x3;
						b1->maxBounds[j] += x3;
						b2->pos[j] -= x3;
						b2->minBounds[j] -= x3;
						b2->maxBounds[j] -= x3;
					}
					else if (desplazamiento[j] > 0){
						x1 = b1->pos[j] + (b1->side / 2);
						x2 = b2->pos[j] - (b2->side / 2);

						x3 = abs(x2 - x1);
						x3 = (x3 / 2);
						b1->pos[j] -= x3;
						b1->minBounds[j] -= x3;
						b1->maxBounds[j] -= x3;
						b2->pos[j] += x3;
						b2->minBounds[j] += x3;
						b2->maxBounds[j] += x3;
					}
				}


			}




			b1->v -= 2 * desplazamientoUnitario * b1->v.dot(desplazamientoUnitario);
			b2->v -= 2 * desplazamientoUnitario * b2->v.dot(desplazamientoUnitario);

		}
	}
}


//Simplemente devolvemos las normales correspondientes a cada muro
Vec3f normalMuro(Wall wall) {
	switch (wall) {
	case WALL_LEFT:
		return Vec3f(-1, 0, 0);
	case WALL_RIGHT:
		return Vec3f(1, 0, 0);
	case WALL_FAR:
		return Vec3f(0, 0, -1);
	case WALL_NEAR:
		return Vec3f(0, 0, 1);
	case WALL_TOP:
		return Vec3f(0, 1, 0);
	case WALL_BOTTOM:
		return Vec3f(0, -1, 0);
	default:
		return Vec3f(0, 0, 0);
	}
}

//Miramos si una bola y un muro están colisionando
bool testColisionBolaAMuro(Ball* ball, Wall wall) {
	Vec3f dir = normalMuro(wall);
	//Miramos si la bola se mueve hacia el muro y si está lo suficientemente cerca del muro como para considerarlo una colisión

	if (wall == WALL_BOTTOM){
		return ball->pos.dot(dir) + ball->r > 0 &&
			ball->v.dot(dir) > 0;
	}

	return ball->pos.dot(dir) + ball->r > BOX_SIZE / 2 &&
		ball->v.dot(dir) > 0;
}

bool testColisionPlayerAMuro(Ball* ball, Wall wall) {
	Vec3f dir = normalMuro(wall);
	//Miramos si la bola se mueve hacia el muro y si está lo suficientemente cerca del muro como para considerarlo una colisión

	if (wall == WALL_BOTTOM){
		return ball->pos.dot(dir) + ball->r > 0 &&
			ball->v.dot(dir) > 0;
	}

	return ball->pos.dot(dir) + ball->r > BOX_SIZE / 2;
}

//Igual para cajas
bool testColisionCajaAMuro(Box* box, Wall wall) {
	Vec3f dir = normalMuro(wall);

	return box->pos.dot(dir) + (box->side) / 2 > BOX_SIZE / 2 &&
		box->v.dot(dir) > 0;
}

//Igual que colisiones bola a bola pero para los pares bola/muro
void ColisionesBolaAMuro(vector<Ball*> &balls, Mundo *mundo) {
	vector<BolaAMuroPar> bmps;
	potencialBolaMuroColisiones(bmps, balls);
	for (unsigned int i = 0; i < bmps.size(); i++) {
		BolaAMuroPar bmp = bmps[i];

		Ball* b = bmp.ball;
		Wall w = bmp.wall;
		if (testColisionBolaAMuro(b, w)) {
			//Hacemos que la bola rebote contra el muro multiplicando la dirección anterior por su normal
			Vec3f dir = (normalMuro(w)).normalize();
			//b->v -= 2.0 * dir * b->v.dot(dir);
			b->v -= 2.0 * dir * b->v.dot(dir);
			mundo->myAudio->playSound(mundo->bump,b->pos,b->v);
		}
	}
}

//Igual para cajas
void ColisionesCajaAMuro(vector<Box*> &boxes) {
	vector<CajaAMuroPar> bmps;
	potencialCajaAMuroColisiones(bmps, boxes);
	for (unsigned int i = 0; i < bmps.size(); i++) {
		CajaAMuroPar bmp = bmps[i];

		Box* b = bmp.box;
		Wall w = bmp.wall;

		if (testColisionCajaAMuro(b, w)) {
			//Hacemos que la bola rebote contra el muro multiplicando la dirección anterior por su normal
			Vec3f dir = (normalMuro(w)).normalize();
			b->v -= 2 * dir * b->v.dot(dir);
			//b->v -= 1.8 * dir * b->v.dot(dir);
		}
	}
}

void ColisionesPlayerAMuro(Ball* player, Player* jugador) {
	vector<PlayerAMuroPar> bmps;
	potencialPlayerAMuroColisiones(bmps, player);
	for (unsigned int i = 0; i < bmps.size(); i++) {
		PlayerAMuroPar bmp = bmps[i];

		

		Ball* b = bmp.player;
		Wall w = bmp.wall;

		b->pos = *jugador->camara->GetPos();

		if (testColisionPlayerAMuro(b, w)) {
			//printf("Tenemos colision\n");
			//Movemos al jugador acorde a lo que se está metiendo en el muro
			Vec3f dir = (normalMuro(w)).normalize();
			dir /= 10;
			b->pos -= dir;
			Vec3f* posicionJug = jugador->camara->GetPos();
			*posicionJug = b->pos;
			jugador->camara->SetPos(*posicionJug);
			jugador->camara->SetVel(0.0f);
			//b->v -= 2 * dir * b->v.dot(dir);
			//b->v -= 1.8 * dir * b->v.dot(dir);
		}
	}
}



//Actualiza el estado de las bolas haciendo las llamadas a lasfunciones que se encargan de cada cosa.
void performUpdate(vector<Ball*> &balls, vector<Box*> &boxes, Mundo *mundo,bool gravity) {
	if (gravity == true){
		gravedad(balls, boxes);
	}
	//Bolas
	ColisionesBolaABola(balls);
	ColisionesBolaAMuro(balls, mundo);

	//Cajas
	//ColisionesCajaACaja(boxes);
	//ColisionesCajaAMuro(boxes);

	//Ambas
	ColisionesBolaACaja(balls, boxes);

}


//Actualiza el estado de las bolas haciendo las llamadas a lasfunciones que se encargan de cada cosa.
void performUpdatePlayer(Ball* playerBall, vector<Ball*> &balls, vector<Box*> &boxes, Player* jugador) {



	(playerBall->pos) = *(jugador->camara->GetPos());

	//playerBall->pos.print();

	ColisionesPlayerABola(playerBall,jugador,balls);
	ColisionesPlayerAMuro(playerBall, jugador);
	ColisionesPlayerACaja(playerBall, jugador, boxes);
	
}

//Avanza el estado de las bolas
void advance(vector<Ball*> &balls, vector<Box*> &boxes, float t, float &timeUntilUpdate, Mundo *mundo, bool gravedad) {
	while (t > 0) {
		if (timeUntilUpdate <= t) {
			moverBolas(balls, timeUntilUpdate);
			//En este caso las cajas son estaticas
			//moverCajas(boxes, timeUntilUpdate);
			performUpdate(balls, boxes,mundo,gravedad);
			t -= timeUntilUpdate;
			timeUntilUpdate = TIME_BETWEEN_UPDATES;
		}
		else {
			moverBolas(balls, t);
			moverCajas(boxes, t);
			timeUntilUpdate -= t;
			t = 0;
		}
	}
}


void advancePlayer(Ball* playerBall, Player* jugador, vector<Ball*> &balls, vector<Box*> &boxes, float t, float &timeUntilUpdate) {
	while (t > 0) {
		if (timeUntilUpdate <= t) {

			performUpdatePlayer(playerBall, balls, boxes, jugador);
			t -= timeUntilUpdate;
			timeUntilUpdate = TIME_BETWEEN_UPDATES;
		}
		else {

			timeUntilUpdate -= t;
			t = 0;
		}

		Vec3f posicion = *jugador->camara->GetPos();
		Vec3f velocidad = *jugador->camara->GetDir();
		alListener3f(AL_POSITION, posicion[0], posicion[1], posicion[2]);
		alListener3f(AL_VELOCITY, velocidad[0], velocidad[1], velocidad[2]);

	}

}

void chasePlayer(Ball* playerBall, Player* jugador, vector<Ball*> &balls,int rana){

	Ball *ball;
	Vec3f diff;
	Vec3f normDiff;
	float magnitude;

	if (rana < balls.size() && rana >= 0 ) {
	
			ball = balls[rana];
			diff = (playerBall->pos) - (ball->pos);
			normDiff=diff.normalize();
			magnitude = ball->v.magnitude();
			ball->v = normDiff*magnitude;
			
	}


}

bool checkDisparo(Vec3f direccion, Vec3f origen, vector<Ball*> &balls){
	Ball *ball;
	float distance = 1000;

	

	for (unsigned int j = 0; j < balls.size(); j++) {
		
		

		ball = balls[j];

		distance=direccion.distanceToPoint(origen, ball->pos);
		if (distance <= ball->r){


			
			Ball *toberemoved = balls[j];
			balls.erase(remove(balls.begin(), balls.end(), toberemoved), balls.end());
			printf("Rana zombie eliminada!!!\n", j);
			
			return true;

			

		}
		
	}
	return false;

}