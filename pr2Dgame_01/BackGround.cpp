#include "stdafx.h"
#include "BackGround.h"
#include "timer.h"

BackGround::BackGround(float px, float py):SpliteObject("배경",0,true,px,py)//보통 0은 아군,1번은 적,2는 배경으로
{
}

BackGround::~BackGround()
{
}

void BackGround::init()
{
	//배경 이미지 로드하기
	readBMPRect("asset/배경.bmp", 0, 0, 4303, 224, &splite);

	//플레이어 이동을 막는 충돌체 추가.
	addCollider(new AABB(0, 140, 500, 25, 0));//위로 이동 방지 충돌체
	addCollider(new AABB(0, 220, 500, 25, 1));//위로 이동 방지 충돌체
	addCollider(new AABB(208, 160, 35, 15, 0));//위로 이동 방지 충돌체

	//스크롤 속도 초기화
	speed = 100;//초당 100px로 이동
}

void BackGround::update()
{
	//스크롤 이동
	float d = speed * getDelteTime();
	//translate(-d, 0);//잠시 막아놓음
	//px = px - d;
}

void BackGround::onTriggerStay(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	if (OtherObj->GetName() == "나루토"&&otherAABB->getId() == 0 && myAABB->getId() == 0)
	{
		//printf("충돌");
		OtherObj->translate(0, 1);
	}

	if (OtherObj->GetName() == "나루토"&&otherAABB->getId() == 0 && myAABB->getId() == 1)
	{
		OtherObj->translate(0, -1);
	}
}