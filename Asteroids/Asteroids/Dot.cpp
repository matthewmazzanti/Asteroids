#include "Dot.h"


Dot::Dot(int inX, int inY, int startX, int startY)
{
	_ScreenX = inX;
	_ScreenY = inY;

	_mainVect = new Vector2D();
	_changeVect = new Vector2D();

	_dotTexture = NULL;
	_renderer = NULL;
	_Center = new SDL_Point;
	_Center->x = 0;
	_Center->y = 0;

	_move = false;
}

void Dot::init(SDL_Renderer* inRenderer)
{
	_dotTexture = new Texture(inRenderer);
	_renderer = inRenderer;
}

void Dot::handleEvent(SDL_Event e)
{
	////If a key was pressed
	//if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	//{
	//	//Adjust the velocity
	//	switch (e.key.keysym.sym)
	//	{
	//	case SDLK_UP: _VelY -= DOT_VEL; break;
	//	case SDLK_DOWN: _VelY += DOT_VEL; break;
	//	case SDLK_LEFT: _VelX -= DOT_VEL; break;
	//	case SDLK_RIGHT: _VelX += DOT_VEL; break;
	//	}
	//}
	////If a key was released
	//else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	//{
	//	//Adjust the velocity
	//	switch (e.key.keysym.sym)
	//	{
	//	case SDLK_UP: _VelY += DOT_VEL; break;
	//	case SDLK_DOWN: _VelY -= DOT_VEL; break;
	//	case SDLK_LEFT: _VelX += DOT_VEL; break;
	//	case SDLK_RIGHT: _VelX -= DOT_VEL; break;
	//	}
	//}

	
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: 
			_changeVect->setMag(DOT_ACC);
			break;
		case SDLK_LEFT: 
			_AngleVel -= DOT_TURN;
			break;
		case SDLK_RIGHT: 
			_AngleVel += DOT_TURN; 
			break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: 
			_changeVect->setMag(0);
			break;
		case SDLK_LEFT: 
			_AngleVel += DOT_TURN;
			break;
		case SDLK_RIGHT:
			_AngleVel -= DOT_TURN;
			break;
		}
	}
}

void Dot::move(float timeStep)
{
	//Move the dot left or right
	_changeVect->addTheta(_AngleVel * timeStep);

	if (_mainVect->getMag() > 3)
	{
		_mainVect->setMag(_mainVect->getMag() - (_mainVect->getMag() * 0.7 * timeStep));
	}
	else
	{
		_mainVect->setMag(0);
	}
	
	/*float forceVectX, forceVectY;
	float addVectX, addVectY;
	float finalX, finalY;

	forceVectX = cos(VectAngle*PI / 180) * VectVelocity;
	forceVectY = sin(VectAngle*PI / 180) * VectVelocity;

	addVectX = cos(_Direction*PI / 180) * _Velocity * timeStep;
	addVectY = sin(_Direction*PI / 180) * _Velocity * timeStep;

	finalX = forceVectX + addVectX;
	finalY = forceVectY + addVectY;

	VectVelocity = sqrt((finalY*finalY) + (finalX*finalX));
	VectAngle = atan2(finalY, finalX) * 180/PI;*/

	*_mainVect += *_changeVect * timeStep;

	/*Coord temp;
	temp.x = _changeVect->getXYMag().x * timeStep;
	temp.y = _changeVect->getXYMag().y * timeStep;

	Coord temp2;
	temp2.x = _mainVect->getXYMag().x;
	temp2.y = _mainVect->getXYMag().y;

	temp2.x += temp.x;
	temp2.y += temp.y;

	_mainVect->setXYMag(temp2);*/

	if (_mainVect->getMag() >= DOT_MAX_VEL)
	{
		_mainVect->setMag(DOT_MAX_VEL);
	}

	/*float mag = _changeVect->getMag();
	float ang = _changeVect->getTheta() / PI * 180;
	float xmag = _changeVect->getXYMag().x;
	float ymag = _changeVect->getXYMag().y;
	printf("mag %i | ang %i | xmag %i | ymag %i\n", (int)mag, (int)ang, (int)xmag, (int)ymag);*/

	//float mag = _mainVect->getMag();
	//float ang = _mainVect->getTheta() / PI * 180;
	//float xmag = _mainVect->getXYMag().x;
	//float ymag = _mainVect->getXYMag().y;

	//printf("mag %i | ang %i | xmag %i | ymag %i\n", (int)mag, (int)ang, (int)xmag, (int)ymag);

	//printf("forceVectX %i | forceVectY %i | addVectX %i | addVectY %i\n", (int)forceVectX, (int)forceVectY, (int)addVectX, (int)addVectY);
	//printf("forceVectX %f | forceVectY %f | Velocity %i | Angle %i\n", forceVectX, forceVectY, (int)VectVelocity, (int)VectAngle);

	_PosX += _mainVect->getXYMag().x * timeStep;

	//If the dot went too far to the left or right
	if (_PosX < 0)
	{
		_PosX = _ScreenX;
	}
	else if (_PosX > _ScreenX)
	{
		_PosX = 0;
	}

	//Move the dot up or down
	//_PosY += _VelY * timeStep;

	_PosY += _mainVect->getXYMag().y * timeStep;

	//If the dot went too far up or down
	if (_PosY < 0)
	{
		_PosY = _ScreenY;
	}
	else if (_PosY > _ScreenY)
	{
		_PosY = 0;
	}

	_Center->x = _dotTexture->getWidth() / 2;
	_Center->y = _dotTexture->getHeight() / 2;

	float acc = _changeVect->getMag();
	float ang = _changeVect->getTheta() / PI * 180;
	float ang2 = _mainVect->getTheta() / PI * 180;
	printf("Acceleration %i | Angle %i | VectVel %f | VectAng %i\n", (int)acc, (int)ang, _mainVect->getMag(), (int)ang2);
}

void Dot::render()
{
	//Show the dot
	_dotTexture->render((int)(_PosX - _Center->x), (int)(_PosY - _Center->y), NULL, _changeVect->getTheta() / PI * 180 , _Center, SDL_FLIP_NONE);
}

bool Dot::loadFromFile(std::string path)
{
	return _dotTexture->loadFromFile(path);
}

void Dot::free()
{
	_dotTexture->free();
	_dotTexture = NULL;
}