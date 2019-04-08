#include "stdafx.h"
#include "AABB.h"
#include "graphic.h"

AABB::AABB(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


AABB::~AABB()
{
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

