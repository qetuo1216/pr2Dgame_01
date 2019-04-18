#include "stdafx.h"
#include "Barrel.h"


Barrel::Barrel(float px, float py) : SpliteObject("����",2,true,px,py)
{
}

Barrel::~Barrel()
{
}

void Barrel::init()
{
	readBmp("asset/����.bmp", &sprite);

	//�浹ü �߰��ϱ�
	addCollider(new AABB(0, 0, 15, 40, 0));//����
	addCollider(new AABB(18, 0, 15, 40, 1));//������
}

void Barrel::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{


	if (OtherObj->GetName() == "������"&&otherAABB->getId()==0&& myAABB->getId() == 0)
	{
		translate(10, 0);
	}

	if (OtherObj->GetName() == "������"&&otherAABB->getId() == 0 && myAABB->getId() == 1)
	{
		translate(-10, 0);
	}

	
}
