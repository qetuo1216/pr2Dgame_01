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
	//Sprite sprite;
	//readBmp("asset/Ʈ��1.bmp", &sprite);
	//addAniFrame(sprite, 0);
	//readBmp("asset/Ʈ��2.bmp", &sprite);
	////�浹ü �߰�
	//addSpriteCollider(&sprite, new AABB(0, 0, 31, 31, 0), px, py);
	//addAniFrame(sprite, 0);

	//idle
	for (int i = 0; i < 3; i++)
	{
		Sprite sprite;
		readBMPRect("asset/Ʈ��3.bmp", 963+i*(52+1),125,52,83,&sprite);
		addAniFrame(sprite, idle);

	}

	//attack
	for (int i = 0; i < 17; i++)
	{
		Sprite sprite;

		readBMPRect("asset/Ʈ��3.bmp", 0 + i * (153+1), 13, 153, 95, &sprite);
		addAniFrame(sprite, attack);
	}

	//death
	for (int i = 0; i < 3; i++)
	{
		Sprite sprite;

		readBMPRect("asset/Ʈ��3.bmp", 0+i*(85+1), 125, 85, 87, &sprite);
		addAniFrame(sprite, death);
	}

	//die
	Sprite sprite;
	readBMPRect("asset/Ʈ��3.bmp", 869, 125, 84, 87, &sprite);
	addAniFrame(sprite, die);

	state = attack;
	play(state);
	
	//�ִϸ��̼� �ӵ� �����ϱ�
	//setFrameDelay(1.0f);
}

void Trap::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	if (OtherObj->GetName() == "������"&&otherAABB->getId()==0)
	{
		printf("�÷��̾ ������ �ɸ�\n");
		OtherObj->DoDamage(this, OtherObj, myAABB, 10);
	}
}
