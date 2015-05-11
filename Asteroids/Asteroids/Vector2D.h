#pragma once

//move this to another area?
#define PI 3.14159265

enum ReflectAxis{ XReflect, YReflect, XYReflect};

struct Coord
{
	float x;
	float y;
};

class Vector2D
{
public:
	//Initialize the info to zero
	Vector2D();
	~Vector2D();

	//Set the vector data to a specific state. 
	//Overloaded (?) to allow for the reset of specific factors. 
	//Info recalculated and returned

	void setOrigin(Coord origin);
	void setXYMag(Coord XYMag);
	void setTheta(float theta);
	void setMag(float magnitude);

	void addTheta(float theta);
	/*//Geometric translations with specificiations

	//Moves the origin and end coords.
	//Theta and magnitude unchanged.
	void translate(float xChange, float yChange);

	//Rotate all information based upon a theta and a rotation point.
	void rotate(float theta, Coord rotatePoint);

	//Reflect info around axis, default to 0 (x/y axes).
	//Magnitude remains unchanged.
	void reflect(ReflectAxis axis, Coord reflectOrigin);

	//Basic vector math

	//add vectors
	void add(Vector2D* inVect);

	//Subtract vectors
	void sub(Vector2D* inVect);

	//Multiply two vectors resulting in median vector
	void mult(Vector2D* inVect);

	//Multiply vector by scalar
	void multScalar(float scalar);*/

	//Return data

	Coord getOrigin();
	Coord getXYMag();
	float getMag();
	float getTheta();

	//addition overloading
	Vector2D operator+(Vector2D& inVector2D);
	//subtraction overloading
	Vector2D operator-(Vector2D& inVector2D);
	//assignment overloading
	void operator=(Vector2D& inVector2D);
	//vector multiplication resulting in scalar
	float operator*(Vector2D& inVector2D);
	//vector and scalar multiplication resulting in vector
	Vector2D operator*(float& scalar);
	//addition but with built in assignment
	void operator+=(Vector2D& inVector2D);
	//subtraction with built in assignment
	void operator-=(Vector2D& inVector2D);
	
private:

	struct VectorData
	{
		//Starting point for vector
		Coord origin;
		//X and Y lengths of the vector
		Coord XYMag;
		//Magnitude of the vector line
		float magintude;
		//Angle of the vector
		float theta;
	};

	//Private vector data.
	VectorData _vectorData;
};

