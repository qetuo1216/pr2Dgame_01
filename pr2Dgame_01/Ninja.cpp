#include "stdafx.h"
#include "Ninja.h"
#include "bmp.h"
#include "Input.h"
#include "Scythe.h"
#include "HUDBar.h"
#include "timer.h"
Ninja::Ninja(float px, float py):Animation("����", 1, true, px, py)
{
}


Ninja::~Ninja()
{
}

void Ninja::init()
{
	//drop �̹���
	for(int i = 0; i < 2; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0+i*(56+2),159,56,57, &sprite);
		sprite.ax = 10;
		sprite.ay = 10;
		//���� �浹ü - 0��			
		addSpriteCollider(&sprite, new AABB(-5,-5,45,49,0), px, py);

		//�÷��̾� Ž�� �浹ü - 1��			
		addSpriteCollider(&sprite, new AABB(-5, -5, 45, 49, 1), px, py);

		setColColor(0, 255, 0);
		addAniFrame(sprite, drop);


	}

	//idle �̹���
	for (int i = 0; i < 4; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (42+2), 0, 42, 49, &sprite);

		//���� �浹ü - 0��			
		addSpriteCollider(&sprite, new AABB(0,0,37,48,0), px, py);

		//�÷��̾� Ž�� �浹ü - 1��			
		addSpriteCollider(&sprite, new AABB(0-100, -30, 37+200, 48+60, 1), px, py);

		addAniFrame(sprite, idle);
	}

	//attack �̹���
	for (int i = 0; i < 5; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (56 + 2), 51, 56, 48, &sprite);
		sprite.ax = 20;


		//���� �浹ü			
		addSpriteCollider(&sprite, new AABB(-20,0,46,49, 0), px, py);

		//�÷��̾� Ž�� �浹ü - 1��			
		addSpriteCollider(&sprite, new AABB(-20-110, 0-30, 46+220, 49+60, 1), px, py);

		addAniFrame(sprite, attack);
	}

	//hit �̹���
	int hitCol[2][4] = { {1, 3, 40, 48}, {0,0,36,52} };

	for (int i = 0; i < 1; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (41 + 2), 218, 41,56, &sprite);

		/*if (i == 0)
			addSpriteCollider(&sprite, new AABB(1, 3, 40, 48, 0), px, py);
		if (i == 1)
			addSpriteCollider(&sprite, new AABB(0,0,36,52, 0), px, py);*/
		addSpriteCollider(&sprite, new AABB(hitCol[i][0], hitCol[i][1], hitCol[i][2], hitCol[i][3], 0), px, py);
		addAniFrame(sprite, hit);
	}

	//death �̹���
	for (int i = 0; i < 5; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (59 + 2), 318, 59, 56, &sprite);

		addAniFrame(sprite, death);
	}

	changeAniState(drop);//�ʱ� �ִϸ��̼� ���� �����ϱ�
	//play(idle);


	//hp, hp�� �ʱ�ȭ
	hp = 100;
	hpBar = new HUDBar(px - 11, py - 10);
	addChildObject(hpBar, 2);

	dropSpeed = 200; //���� ����ӵ�
	groundY = 160;		//�ٴ� ��ǥ �ʱ�ȭ
}

void Ninja::update()
{
	//aniTest();
	//animation�� drop�����϶�
	if(state==drop) aniDrop();
}

void Ninja::aniDrop()
{
	float dist = dropSpeed * getDelteTime();
	
	
	if (py>= groundY)//�ٴڿ� �����ߴ��� üũ
	{
		changeAniState(idle);
	}
	else
	{
		translate(0, dist);
	}
}

void Ninja::OnAnimationEvent(int aniId, int aniFrame)
{	//���� �� �߻� ����
	if (aniId == attack && aniFrame == 3)
	{
		addGameObject(new Scythe(px - 10, py), 1);
	}
	if (aniId == hit && aniFrame == 0)
	{
		setFrameDelay(0.1);
		changeAniState(idle);
	}
	if (aniId == death && aniFrame == 0)
	{
		delChildObject(this);//���� �����
		delGameObject(this);
	}
}

void Ninja::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{

	//�÷��̾� ���� ����
	if (state != death)
	{

		if (OtherObj->GetName() == "������" && myAABB->getId() == 1)
		{
			changeAniState(attack);
		}		

		if (OtherObj->GetName() == "knife" && myAABB->getId() == 0)
		{
			hp = hp - 50;
			hpBar->setValue((float)hp / 100.0f); //ü�¹� ǥ��

			if (hp <= 0)//ü���� �� ����
			{
				changeAniState(death);
			}
			else
			{
				setFrameDelay(0.3);
				changeAniState(hit);
			}

			
			

		

		}

		

		
	}


}

void Ninja::onTriggerExit(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	//�ִϸ��̼��� death�� �ƴ� ��쿡�� idle�� ����
	if (state == attack)
	{
		if (OtherObj->GetName() == "������" && otherAABB->getId() == 1 && myAABB->getId() == 1)
		{//1�� �浹ü�� �÷��̾ ������ idle�� ���ư���.

			changeAniState(idle);
		}
	}
}


void Ninja::changeAniState(State s)
{
	state = s;
	play(state);
}




void Ninja::aniTest()
{
	if (getKey('0') == true)
	{
		play(drop);//0�� �����Ӻ��� ��
	}	
	
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
		play(hit);
	}

	if (getKey('4') == true)
	{
		play(death);
	}
}
