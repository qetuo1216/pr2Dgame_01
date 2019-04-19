#include "stdafx.h"
#include "Trap.h"
#include "Input.h"

Trap::Trap(float px, float py) : Animation("Ʈ��", 1, true, px, py)
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

		readBMPRect("asset/Ʈ��3.bmp", 963 + i * (52 + 1), 125, 52, 83, &sprite);
		
		//Ž�� �浹ü
		//addSpriteCollider(&sprite, new AABB(-51, -5, 153, 95, 0), px, py);		
		addSpriteCollider(&sprite, new AABB(-100, 0, 52 + 200, 83, 0), px, py);
		
		addSpriteCollider(&sprite, new AABB(0, 30, 52, 83 - 40, 2), px, py);//���� ���� �ֱ�

		setColColor(0, 0, 255);
		addAniFrame(sprite, idle);
	}

	//attack
	for (int i = 0; i < 17; i++)
	{
		Sprite sprite;

		readBMPRect("asset/Ʈ��3.bmp", 0 + i * (153 + 1), 13, 153, 95, &sprite);
		sprite.ax = 51;
		sprite.ay = 5;

		//Ž�� �浹ü
		addSpriteCollider(&sprite, new AABB(-110, 30, 52 + 200, 83-40, 0), px, py);	//���� Ž��

		//���� �浹ü
		if(3<=i&&i>14)
		{
		addSpriteCollider(&sprite, new AABB(0, 30, 52 + 40, 80 - 40, 1), px, py);//���� ���� �ֱ�
		//addSpriteCollider(&sprite, new AABB(-20,30, 52+40, 80-40, 0), px, py);
		}
		else
		{

			addSpriteCollider(&sprite, new AABB(0, 30, 52, 83-40, 2), px, py);//���� ���� �ֱ�
		}

		addAniFrame(sprite, attack);
	}

	//death
	for (int i = 0; i < 3; i++)
	{
		Sprite sprite;

		readBMPRect("asset/Ʈ��3.bmp", 0 + i * (85 + 1), 125, 85, 87, &sprite);
		sprite.ax = 20;
		addAniFrame(sprite, death);
	}

	//die
	Sprite sprite;

	readBMPRect("asset/Ʈ��3.bmp", 869, 125, 84, 87, &sprite);
	sprite.ax = 20;
	addAniFrame(sprite, die);

	changeAniState(idle);

	//�ִϸ��̼� �ӵ� �����ϱ�
	//setFrameDelay(1.0f);
}

void Trap::update()
{
	if (getKey('1') == true)
	{
		play(idle);//0�� �����Ӻ��� ��
	}

	if (getKey('2') == true)
	{
		play(attack);
	}

	if (getKey('3') == true)
	{
		play(death);
	}

	if (getKey('4') == true)
	{
		play(die);
	}
}

void Trap::DoDamage(GameObject * fromObj, GameObject * toObj, AABB * fromAABB, int damage)
{
	//hp����

	//hp�� ����
	changeAniState(death);
}

void Trap::changeAniState(State s)
{
	this->state = s;
	play(this->state);
}



void Trap::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	/*if (OtherObj->GetName() == "������"&&otherAABB->getId()==0)
	{
		printf("�÷��̾ ������ �ɸ�\n");
		OtherObj->DoDamage(this, OtherObj, myAABB, 10);
	}*/
	//�÷��̾� ���� ����
	if (state != death) 
	{

		if (OtherObj->GetName() == "������" && myAABB->getId() == 0)
		{
			changeAniState(attack);
		}

		if (OtherObj->GetName() == "������" && myAABB->getId() == 1)
		{
			printf("�÷��̾ ������ �ɸ�\n");
			OtherObj->DoDamage(this, OtherObj, myAABB, 10);
		}
	}


}

void Trap::onTriggerExit(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	if (state != death)
	{
		if (OtherObj->GetName() == "������" && myAABB->getId() == 0)
		{
			changeAniState(idle);
		}
	}
}
