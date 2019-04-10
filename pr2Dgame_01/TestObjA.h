#pragma once
#include "GameObject.h"
class TestObjA : public GameObject
{
private:
	//오브젝트 이동 속도
	float speed;
public:
	TestObjA(float px,float py);
	virtual ~TestObjA();

	void init();
	void update();

	//충돌 이벤트 오버라이딩
	void onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB);
};

