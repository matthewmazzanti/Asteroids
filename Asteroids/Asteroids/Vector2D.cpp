
#include "Vector2D.h"
#include <cmath>
#include <exception>
#include <stdexcept>

Vector2D::Vector2D()
{
	_vectorData.origin.x = 0;
	_vectorData.origin.y = 0;

	_vectorData.XYMag.x = 0;
	_vectorData.XYMag.y = 0;

	_vectorData.magintude = 0;
	_vectorData.theta = 0;
}


Vector2D::~Vector2D()
{
}

void Vector2D::setOrigin(Coord origin)
{
	_vectorData.origin = origin;
}

void Vector2D::setXYMag(Coord XYMag)
{
	_vectorData.XYMag = XYMag;
	
	float x, y;
	x = XYMag.x;
	y = XYMag.y;
	_vectorData.magintude = sqrt((x*x) + (y*y));
	_vectorData.theta = atan2(y, x);
}

void Vector2D::setTheta(float theta)
{
	if (-PI > theta || PI < theta)
	{
		std::invalid_argument arg("Theta outside of range");
		throw arg;
	}
	else
	{
		_vectorData.theta = theta;
		_vectorData.XYMag.x = cos(theta) * _vectorData.magintude;
		_vectorData.XYMag.y = sin(theta) * _vectorData.magintude;
	}
}

void Vector2D::addTheta(float theta)
{
	_vectorData.theta += theta;
	while (_vectorData.theta > PI)
	{
		_vectorData.theta -= 2 * PI;
	}
	while (_vectorData.theta <= -PI)
	{
		_vectorData.theta += 2 * PI;
	}
	_vectorData.XYMag.x = cos(_vectorData.theta) * _vectorData.magintude;
	_vectorData.XYMag.y = sin(_vectorData.theta) * _vectorData.magintude;
}

void Vector2D::setMag(float Mag)
{
	_vectorData.magintude = Mag;
	_vectorData.XYMag.x = cos(_vectorData.theta) * Mag;
	_vectorData.XYMag.y = sin(_vectorData.theta) * Mag;
}

//void Vector2D::translate(float xChange, float yChange)
//{
//	_vectorData.origin.x += xChange;
//	_vectorData.origin.y += yChange;
//}
//
//void Vector2D::rotate(float theta, Coord rotatePoint)
//{
//	//if (-PI > theta || PI < theta)
//	//{
//	//	std::invalid_argument arg("Theta outside of range");
//	//	throw arg;
//	//}
//	//else
//	//{
//	//	
//	//}
//}
//
//void Vector2D::reflect(ReflectAxis axis, Coord reflectOrigin)
//{
//
//}
//
//void Vector2D::add(Vector2D* inVect)
//{
//	
//}
//
//void Vector2D::sub(Vector2D* inVect)
//{
//	
//}
//
//void Vector2D::mult(Vector2D* inVect)
//{
//	
//}
//
//void Vector2D::multScalar(float scalar)
//{
//	
//}

Coord Vector2D::getOrigin()
{
	return _vectorData.origin;
}

Coord Vector2D::getXYMag()
{
	return _vectorData.XYMag;
}

float Vector2D::getMag()
{
	return _vectorData.magintude;
}

float Vector2D::getTheta()
{
	return _vectorData.theta;
}

Vector2D Vector2D::operator+(Vector2D& inVector2D)
{
	Vector2D tempVector;
	float x, y;

	x = _vectorData.XYMag.x + inVector2D._vectorData.XYMag.x;
	y = _vectorData.XYMag.y + inVector2D._vectorData.XYMag.y;
	
	tempVector._vectorData.XYMag.x = x;
	tempVector._vectorData.XYMag.y = y;
	tempVector._vectorData.magintude = sqrt((x*x) + (y*y));
	tempVector._vectorData.theta = atan2(y, x);
	//printf("scalar add\n");
	return tempVector;
}

Vector2D Vector2D::operator- (Vector2D& inVector2D)
{
	Vector2D tempVector;
	float x, y;

	x = _vectorData.XYMag.x - inVector2D._vectorData.XYMag.x;
	y = _vectorData.XYMag.y - inVector2D._vectorData.XYMag.y;

	tempVector._vectorData.XYMag.x = x;
	tempVector._vectorData.XYMag.y = y;
	tempVector._vectorData.magintude = sqrt((x*x) + (y*y));
	tempVector._vectorData.theta = atan2(y, x);

	return tempVector;
}

void Vector2D::operator=(Vector2D& inVector2D)
{
	_vectorData = inVector2D._vectorData;
	//printf("internal %i, entry %i\n", &_vectorData, &inVector2D._vectorData);
}

float Vector2D::operator*(Vector2D& inVector2D)
{
	return (_vectorData.XYMag.x * inVector2D._vectorData.XYMag.x) + (_vectorData.XYMag.y * inVector2D._vectorData.XYMag.y);
}

Vector2D Vector2D::operator*(float& scalar)
{
	Vector2D tempVector;
	tempVector._vectorData.theta = _vectorData.theta;
	tempVector._vectorData.magintude = _vectorData.magintude * scalar;
	tempVector._vectorData.XYMag.x = tempVector._vectorData.magintude * cos(tempVector._vectorData.theta);
	tempVector._vectorData.XYMag.y = tempVector._vectorData.magintude * sin(tempVector._vectorData.theta);
	//printf("scalar mult\n");
	return tempVector;
}

void Vector2D::operator+=(Vector2D& inVector2D)
{
	float x, y;

	x = _vectorData.XYMag.x + inVector2D._vectorData.XYMag.x;
	y = _vectorData.XYMag.y + inVector2D._vectorData.XYMag.y;

	_vectorData.XYMag.x = x;
	_vectorData.XYMag.y = y;
	_vectorData.magintude = sqrt((x*x) + (y*y));
	_vectorData.theta = atan2(y, x);
}

void Vector2D::operator-=(Vector2D& inVector2D)
{
	float x, y;

	x = _vectorData.XYMag.x - inVector2D._vectorData.XYMag.x;
	y = _vectorData.XYMag.y - inVector2D._vectorData.XYMag.y;

	_vectorData.XYMag.x = x;
	_vectorData.XYMag.y = y;
	_vectorData.magintude = sqrt((x*x) + (y*y));
	_vectorData.theta = atan2(y, x);
}