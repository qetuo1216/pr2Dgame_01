#include "stdafx.h"
#include "Ninja.h"
#include "bmp.h"
#include "Input.h"

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
		//Ž�� �浹ü			
		addSpriteCollider(&sprite, new AABB(-5,-5,45,49,2), px, py);

		setColColor(0, 255, 0);
		addAniFrame(sprite, drop);


	}

	//idle �̹���
	for (int i = 0; i < 4; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (42+2), 0, 42, 49, &sprite);
		
		addAniFrame(sprite, idle);
	}

	//attack �̹���
	for (int i = 0; i < 5; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (56 + 2), 51, 56, 48, &sprite);
		sprite.ax = 20;
		addAniFrame(sprite, attack);
	}

	//hit �̹���
	for (int i = 0; i < 2; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (41 + 2), 218, 41,56, &sprite);

		addAniFrame(sprite, hit);
	}

	//death �̹���
	for (int i = 0; i < 5; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (59 + 2), 318, 59, 56, &sprite);

		addAniFrame(sprite, death);
	}

	play(hit);
}

void Ninja::update()
{
	aniTest();
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
