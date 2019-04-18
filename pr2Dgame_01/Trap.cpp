#include "stdafx.h"
#include "Trap.h"


Trap::Trap(float px, float py) : Animation("Æ®·¦",1,true,px,py)
{
}


Trap::~Trap()
{
}

void Trap::init()
{
	Sprite sprite;
	readBmp("asset/Æ®·¦1.bmp", &sprite);
	addAniFrame(sprite, 0);
	readBmp("asset/Æ®·¦2.bmp", &sprite);
	addAniFrame(sprite, 0);
}
