#include "stdafx.h"
#include "Trap.h"


Trap::Trap(float px, float py) : Animation("트랩",1,true,px,py)
{
}


Trap::~Trap()
{
}

void Trap::init()
{
	Sprite sprite;
	readBmp("asset/트랩1.bmp", &sprite);
	addAniFrame(sprite, 0);
	readBmp("asset/트랩2.bmp", &sprite);
	//충돌체 추가
	addSpriteCollider(&sprite, new AABB(0, 0, 31, 31, 0), px, py);
	addAniFrame(sprite, 0);

	//애니메이션 속도 조절하기
	setFrameDelay(1.0f);
}

void Trap::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	if (OtherObj->GetName() == "나루토"&&OtherObj->getId()==0)
	{
		printf("플레이어가 함정에 걸림\n");
		
	}
}
