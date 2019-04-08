#include "stdafx.h"
#include "AABB.h"


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

void AABB::debugDraw(unsigned char r, unsigned char g, unsigned char b)
{
}

