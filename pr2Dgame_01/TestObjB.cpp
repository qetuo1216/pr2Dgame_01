#include "stdafx.h"
#include "TestObjB.h"


TestObjB::TestObjB(float px, float py):GameObject("테스트B",1,true,px,py)
{
}

TestObjB::~TestObjB()
{
}

void TestObjB::init()
{
	addCollider(new AABB(0 , 50, 100, 100,0));
	addCollider(new AABB(200 , 0, 50,50,1));
	//이동속도 초기화
	setColColor(0, 0, 255);

	//hp 초기화하기
	hp = 100;
}

void TestObjB::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	using namespace std;
	if (myAABB->getId()==0&&OtherObj->GetName()=="knife"&&otherAABB->getId()==0)
	{
		hp -= 20;
		cout << "수리검 충돌" << endl;
		cout << hp << endl;
		if (hp<=0)
		{
			delGameObject(this);
		}
	}
}
