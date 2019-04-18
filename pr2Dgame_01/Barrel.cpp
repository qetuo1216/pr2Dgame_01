#include "stdafx.h"
#include "Barrel.h"


Barrel::Barrel(float px, float py) : SpliteObject("베럴",2,true,px,py)
{
}

Barrel::~Barrel()
{
}

void Barrel::init()
{
	readBmp("asset/베럴.bmp", &sprite);

	//충돌체 추가하기
	addCollider(new AABB(0, 0, 15, 40, 0));//왼쪽
	addCollider(new AABB(18, 0, 15, 40, 1));//오른쪽
}

void Barrel::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{


	if (OtherObj->GetName() == "나루토"&&otherAABB->getId()==0&& myAABB->getId() == 0)
	{
		translate(10, 0);
	}

	if (OtherObj->GetName() == "나루토"&&otherAABB->getId() == 0 && myAABB->getId() == 1)
	{
		translate(-10, 0);
	}

	
}
