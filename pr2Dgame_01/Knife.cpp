#include "stdafx.h"
#include "Knife.h"
#include "timer.h"
#include "gameObjectPool.h"
Knife::Knife(float px, float py):Animation("knife",1,true,px,py)
{
}


Knife::~Knife()
{
}

void Knife::init()
{
	//애니메이션 로드
	Sprite sprite;
	for (int i = 0; i < 16; i++)
	{
		readBMPRect("asset/수리검.bmp", i * (40 + 2), 1104, 40, 16, &sprite);//크기가 42*54, 우측상단이 2.12
		addAniFrame(sprite, 0);//0번 배열에 집어넣음
	}
	//이동속도 초기화
	speed = 200;
	//수리검 사정거리
	maxDist = 200;
	//
	moveDist = 0;
}

void Knife::update()
{
	float dist = speed*getDelteTime();
	translate(dist, 0);

	//이동거리 구하기
	moveDist = moveDist + dist;
	if (moveDist > maxDist)
	{
		//수리검 제거
		gameObjectPool * pool = gameObjectPool::instance();
		pool->delGameObject(this);
	}
}
