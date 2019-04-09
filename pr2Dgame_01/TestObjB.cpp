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
	addCollider(new AABB(0 + px, 0 + py, 100, 100));
	//이동속도 초기화
	setColColor(0, 0, 255);
}
