#include "stdafx.h"
#include "TestObjB.h"


TestObjB::TestObjB(float px, float py):GameObject("테스트B",0,true,px,py)
{
}

TestObjB::~TestObjB()
{
}

void TestObjB::init()
{
	addCollider(new AABB(0 , 0, 100, 100,0));
	addCollider(new AABB(200 , 0, 50,50,1));
	//이동속도 초기화
	setColColor(0, 0, 255);
}

void TestObjB::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
}
