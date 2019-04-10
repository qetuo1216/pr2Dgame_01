#include "stdafx.h"
#include "AABB.h"
#include "graphic.h"

AABB::AABB(float x, float y, float width, float height,int id)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->id = id;
}


AABB::~AABB()
{
}

void AABB::getBB(float * x0, float * y0, float * x1, float * y1)
{
	*x0 = x;
	*y0 = y;
	*x1 = x+width;
	*y1 = y+height;
}

void AABB::getBB(float & x0, float & y0, float & x1, float & y1)//오버로딩
{
	x0 = x;
	y0 = y;
	x1 = x + width;
	y1 = y + height;
}

int AABB::getId()
{
	return id;
}

void AABB::setId(int id)
{
	this->id = id;
}

void AABB::translate(float dx, float dy)
{
	x = x + dx;
	y = y + dy;
}

void AABB::debugDraw(unsigned char r, unsigned char g, unsigned char b)
{
	float x0 = x;
	float y0 = y;
	float x1 = x + width;
	float y1 = y + height;

	drawRect(x0,y0,x1,y1,r,g,b);
}

