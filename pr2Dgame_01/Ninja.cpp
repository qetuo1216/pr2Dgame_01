#include "stdafx.h"
#include "Ninja.h"
#include "bmp.h"
#include "Input.h"

Ninja::Ninja(float px, float py):Animation("닌자", 1, true, px, py)
{
}


Ninja::~Ninja()
{
}

void Ninja::init()
{
	//drop 이미지
	for(int i = 0; i < 2; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0+i*(56+2),159,56,57, &sprite);
		sprite.ax = 10;
		sprite.ay = 10;
		//탐지 충돌체			
		addSpriteCollider(&sprite, new AABB(-5,-5,45,49,0), px, py);

		setColColor(0, 255, 0);
		addAniFrame(sprite, drop);


	}

	//idle 이미지
	for (int i = 0; i < 4; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (42+2), 0, 42, 49, &sprite);

		//탐지 충돌체			
		addSpriteCollider(&sprite, new AABB(0,0,37,48,0), px, py);
		
		addAniFrame(sprite, idle);
	}

	//attack 이미지
	for (int i = 0; i < 5; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (56 + 2), 51, 56, 48, &sprite);
		sprite.ax = 20;


		//탐지 충돌체			
		addSpriteCollider(&sprite, new AABB(-20,0,46,49, 0), px, py);

		addAniFrame(sprite, attack);
	}

	//hit 이미지
	int hitCol[2][4] = { {1, 3, 40, 48}, {0,0,36,52} };

	for (int i = 0; i < 2; i++)
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

	//death 이미지
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
		play(drop);//0번 프레임부터 들어감
	}	
	
	if (getKey('1') == true)
	{
		play(idle);//0번 프레임부터 들어감
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
