#include "stdafx.h"
#include "Barrel.h"


Barrel::Barrel(float px, float py) : SpliteObject("����",2,true,px,py)
{
}

Barrel::~Barrel()
{
}

void Barrel::init()
{
	readBmp("asset/����.bmp", &sprite);
}
