#include "Point.h"

Point::Point(int x, int y, int z)
	: mX(x), mY(y), mZ(z)
{
}

Point::~Point() 
{
}

int Point::X()
{
	return mX;
}

int Point::Y()
{
	return mY;
}

int Point::Z()
{
	return mZ;
}
