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
	maxDist = 200; //낫의 이동거리	
	moveDist = 0; //이동거리 측정 변수
	//플레이어를 따라가는 거리
	followDist = 100;
	followTime = 0.5f;
	//라이프타임 초기화
	lifeTime = 1.0f;//1초동안 살아있음

}

void Scythe::update()
{
	//유도탄의 좌표가 px,py일때 적의 좌표가 player->getPx(),player->getPx()
	//즉 적으로 가는 좌표는 translate((px - player->getPx()),py - player->getPx()))는 바로 도착한다.
	//그래서 길이만큼 나눠야하는데 = √(x-a)^2+(y-b)^2

	gameObjectPool * pool = gameObjectPool::instance();

	//플레이어 찾기
	GameObject * player = pool->find("나루토");

	if (player != NULL)//나루토 객체를 찾은 경우
	{
		//이동 목표 위치(target)
		float tx = player->getPx();
		float ty = player->getPy();

		//낫의 현재 위치(start)
		float sx = px;
		float sy = py;

		//낫에서 플레이어로 이동하는 벡터 끝 빼기 처음
		float vx = tx - sx;
		float vy = ty - sy;

		//translate(vx, vy);	//다이렉트로 이동 = 의미없음

		//백터의 방향 구하기 = 길이로 나눈다.
		float len = sqrt(vx*vx + vy*vy);
		float nx = vx / len;
		float ny = vy / len;

		//속력에 의한 이동거리 적용
		float dist = speed * getDelteTime();
		float dx, dy;

		//if(moveDist<=followDist)
		if(followTime>=0)
		{
			dx = nx * dist;
			dy = ny * dist;
		}
		else
		{
			dx = -dist;
			dy = 0;
		}
		translate(dx, dy);

		moveDist = moveDist + dist;//이동거리 측정
	}
	else//플레이어 객체를 찾지 못한 경우
	{
		float dist = speed * getDelteTime();
		translate(-dist, 0);
		
		moveDist = moveDist + dist;//이동거리 측정
	}
	followTime -= getDelteTime();
	lifeTime -= getDelteTime();
	//라이프 타임 검사
	if (lifeTime<=0)
	{

		delGameObject(this);
	}

	//최대 이동거리 검사
	/*if (moveDist >= maxDist)
	{
		delGameObject(this);
	}*/
	


	//그냥 낫 날리기
	//float d = speed * getDelteTime();
	//translate(-d, 0);
}

void Scythe::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	if (OtherObj->GetName() == "나루토"||OtherObj->GetName()=="knife")
	{
		delGameObject(this);
	};
}
