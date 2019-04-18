#include "stdafx.h"
#include "Barrel.h"


Barrel::Barrel(float px, float py) : SpliteObject("º£·²",2,true,px,py)
{
}

Barrel::~Barrel()
{
}

void Barrel::init()
{
	readBmp("asset/º£·².bmp", &sprite);
}
