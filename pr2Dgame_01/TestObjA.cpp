#include "stdafx.h"
#include "TestObjA.h"

TestObjA::TestObjA(float px, float py) :GameObject("�׽�ƮA", 0, 1, px, py)
{
}

TestObjA::~TestObjA()
{
}

void TestObjA::init()
{
	//�浹ü �߰��ϱ�
	col.push_back(new AABB(0, 0, 100, 100));
}
