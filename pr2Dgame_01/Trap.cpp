#include "stdafx.h"
#include "Trap.h"


Trap::Trap(float px, float py) : Animation("트랩",1,true,px,py)
{
}


Trap::~Trap()
{
}

void Trap::init()
{
	Sprite sprite;
	readBmp("asset/트랩1.bmp", &sprite);
	addAniFrame(sprite, 0);
	readBmp("asset/트랩2.bmp", &sprite);
	addAniFrame(sprite, 0);

	//애니메이션 속도 조절하기
	setFrameDelay(1.0f);
}
