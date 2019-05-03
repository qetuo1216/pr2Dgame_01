#include "stdafx.h"
#include "Wolf.h"
#include "Input.h"
#include "HUDBar.h"



Wolf::Wolf(float px, float py): Animation("����",1,true,px,py)
{
}

Wolf::~Wolf()
{
}

void Wolf::init()
{

	setColColor(0, 255, 0);

	int atkCol[10][4] = { {18,15,60,32}, {22,8,54,40}, {22,8,54,40}, {23,9,54,36}, {15,7,56,35}, {3,5,56,35},
						  {18,11,51,34},{18,11,51,34},{18,11,51,34},{18,11,51,34} };
	for (int i = 0; i < 10; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/wolf.bmp", 0 + i * (84 + 2), 42, 84, 56, &sprite);

		//���� �浹ü - 0��			
		addSpriteCollider(&sprite, new AABB(atkCol[i][0], atkCol[i][1], atkCol[i][2], atkCol[i][3], 0), px, py);

		if (i == 3 || i == 4 || i == 5)
		{
			addSpriteCollider(&sprite, new AABB(-10,0,18,15, 2), px, py);
		}
		addSpriteCollider(&sprite, new AABB(-3, 15, 13, 34, 1), px, py); //Ž�� �浹ü - 1

		addAniFrame(sprite, attack);

	}


	for (int i = 0; i < 8; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/wolf.bmp", 0 + i * (66 + 2), 100, 66, 43, &sprite);
		sprite.ax = -10;
		sprite.ay = -10;
		//���� �浹ü - 0��			
		addSpriteCollider(&sprite, new AABB(13, 15, 60, 34, 0), px, py); //���� �浹ü - 0
		addSpriteCollider(&sprite, new AABB(-3, 15, 13, 34, 1), px, py); //Ž�� �浹ü - 1

		//�÷��̾� Ž�� �浹ü - 1��			
		//addSpriteCollider(&sprite, new AABB(-5, -5, 45, 49, 1), px, py);

		addAniFrame(sprite, run);

	}

	Sprite sprite;
	readBMPRect("asset/monster/wolf.bmp", 0,187,40,56, &sprite);
	sprite.ax = -28;
	sprite.ay = 10;
	addSpriteCollider(&sprite, new AABB(30, -8, 35, 50, 0), px, py);
	addAniFrame(sprite, hit);

	for (int i = 0; i < 10; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/wolf.bmp", 0 + i * (58 + 2), 245, 58, 59, &sprite);

		sprite.ax = -28;
		sprite.ay = 10;

		//���� �浹ü - 0��			
		//addSpriteCollider(&sprite, new AABB(-5, -5, 45, 49, 0), px, py);

		//�÷��̾� Ž�� �浹ü - 1��			
		//addSpriteCollider(&sprite, new AABB(-5, -5, 45, 49, 1), px, py);

		addAniFrame(sprite, death);

	}


	 hp =100;//���� ü�� 	
	 hpBar = new HUDBar(px - 11, py - 10);
	 addChildObject(hpBar, 2);

	changeAniState(run);

}

void Wolf::update()
{

	if (getKey('1') == true)
	{
		play(attack);//0�� �����Ӻ��� ��
	}

	if (getKey('2') == true)
	{
		play(hit);
	}

	if (getKey('3') == true)
	{
		play(run);
	}

	if (getKey('4') == true)
	{
		play(death);
	}
}

void Wolf::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	if (myAABB->getId()==1&& OtherObj->GetName()=="������"&&otherAABB->getId()==1)
	{
		changeAniState(attack);
	}	
	if (myAABB->getId() == 0 && OtherObj->GetName() == "knife"&&otherAABB->getId() == 0)
	{
		hp = hp - 50;
		hpBar->setValue((float)hp / 100.0f); //ü�¹� ǥ��
		if (hp <= 0)//ü���� �� ����
		{
			changeAniState(death);
		}
		else
		{
			changeAniState(hit);
		}
	}
}

void Wolf::onTriggerExit(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	if (myAABB->getId() == 1 && OtherObj->GetName() == "������"&&otherAABB->getId() == 1)
	{
		changeAniState(run);
	}	

}

void Wolf::OnAnimationEvent(int aniId, int aniFrame)
{
	if (aniId == death && aniFrame == 0)
	{
		delChildObject(this);//���� �����
		delGameObject(this);
	}	
	if (aniId == hit && aniFrame == 0)
	{
		changeAniState(run);//���� �����
	}
}

void Wolf::changeAniState(State s)
{
	state = s;
	play(state);
}
