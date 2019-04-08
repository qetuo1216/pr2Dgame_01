#include "stdafx.h"
#include "TestObjA.h"

TestObjA::TestObjA(float px, float py) :GameObject("테스트A", 0, 1, px, py)
{
}

TestObjA::~TestObjA()
{
}

void TestObjA::init()
{
	//충돌체 추가하기
	col.push_back(new AABB(0, 0, 100, 100));
}
