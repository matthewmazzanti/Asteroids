#pragma once
#ifndef DOT_H
#define DOT_H

#include <SDL.h>
#include <string>
#include "Texture.h"
#include "Vector2D.h"



class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	////Maximum axis velocity of the dot
	//static const int DOT_VEL = 1000;
	//static const int DOT_TURN = 1080;

	//Initializes the variables
	Dot(int inX, int inY, int startX, int startY);

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event e);

	//Moves the dot
	void move(float timeStep);

	//Shows the dot on the screen
	void render();

	bool loadFromFile(std::string path);

	void init(SDL_Renderer* inRenderer);
	void free();

private:

	

	float _PosX, _PosY;
	float _AngleVel;
	//float _VelX, _VelY;
	//float _Direction;
	//float _Velocity;
	//ForceVect _ForceVect;
	//float VectAngle;
	//float VectVelocity;
	//float temp;

	int DOT_ACC = 700;
	int DOT_MAX_VEL = 2000;
	float DOT_TURN = 720 * PI/180;

	int _ScreenX, _ScreenY;

	bool _move;

	Vector2D* _mainVect;
	Vector2D* _changeVect;

	SDL_Point* _Center;
	Texture* _dotTexture;
	SDL_Renderer* _renderer;
};

#endif // !DOT_H

//The dot that will move around on the screen


