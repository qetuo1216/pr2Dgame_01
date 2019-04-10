#pragma once
#include "GameObject.h"

class TestObjB : public GameObject
{
private:
	//hp테스트
	int hp;
public:
	TestObjB(float px,float py);
	~TestObjB();

	void init();//테스트 충돌 추가하기

	//충돌 이벤트 오버라이딩
	void onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB);
};

