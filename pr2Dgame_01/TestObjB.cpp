#include "stdafx.h"
#include "TestObjB.h"


TestObjB::TestObjB(float px, float py):GameObject("�׽�ƮB",1,true,px,py)
{
}

TestObjB::~TestObjB()
{
}

void TestObjB::init()
{
	addCollider(new AABB(0 , 50, 100, 100,0));
	addCollider(new AABB(200 , 0, 50,50,1));
	//�̵��ӵ� �ʱ�ȭ
	setColColor(0, 0, 255);

	//hp �ʱ�ȭ�ϱ�
	hp = 100;
}

void TestObjB::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	using namespace std;
	if (myAABB->getId()==0&&OtherObj->GetName()=="knife"&&otherAABB->getId()==0)
	{
		hp -= 20;
		cout << "������ �浹" << endl;
		cout << hp << endl;
		if (hp<=0)
		{
			delGameObject(this);
		}
	}
}
