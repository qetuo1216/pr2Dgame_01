#include "stdafx.h"
#include "Scythe.h"
#include "bmp.h"
#include "timer.h"
#include "gameObjectPool.h"

Scythe::Scythe(float px, float py) : Animation("낫", 1, true, px, py)
{
}

Scythe::~Scythe()
{
}

void Scythe::init()
{
	//애니메이션 로드
	for (int i = 0; i < 4; i++)
	{
		Sprite sprite;
		readBMPRect("asset/monster/Ninja.bmp",0+i*(40+2),418,40,40,&sprite);

		addSpriteCollider(&sprite, new AABB(0, 0, 30, 30, 1), px, py);
		addAniFrame(sprite, 0);
	}

	//이동속도 초기화
	speed = 200;
}

void Scythe::update()
{
	//낫 자기좌표 가져오기
	float x = px, y = py;

	gameObjectPool * pool = gameObjectPool::instance();

	GameObject * player = pool->find("나루토");

	float d = speed * getDelteTime();

	if (player != NULL)//나루토 객체 찾음
	{
		translate(player->getPx(), player->getPy());

	}

	//플레이어 좌표 
	//float d = speed * getDelteTime();
	//translate(-d, 0);
}
