#include "stdafx.h"
#include "TestObjA.h"
#include "timer.h"
#include "Input.h"
TestObjA::TestObjA(float px, float py) :GameObject("테스트A", 0, 1, px, py)
{
}

TestObjA::~TestObjA()
{
}

void TestObjA::init()
{
	//충돌체 추가하기
	//col.push_back(new AABB(0+px, 0+py, 100, 100));//게임오브젝트를 기준으로
	addCollider(new AABB(0 + px, 0 + py, 100, 100));
	//이동속도 초기화
	speed = 100;
}

void TestObjA::update()
{
	float dist = speed * getDelteTime();

	if (getKey(VK_RIGHT) == true)
	{
		translate(dist, 0);
		//printf("오른쪽으로 이동");
	}
}
