#include "stdafx.h"
#include "Trap.h"


Trap::Trap(float px, float py) : Animation("Ʈ��",1,true,px,py)
{
}


Trap::~Trap()
{
}

void Trap::init()
{
	Sprite sprite;
	readBmp("asset/Ʈ��1.bmp", &sprite);
	addAniFrame(sprite, 0);
	readBmp("asset/Ʈ��2.bmp", &sprite);
	addAniFrame(sprite, 0);

	//�ִϸ��̼� �ӵ� �����ϱ�
	setFrameDelay(1.0f);
}
