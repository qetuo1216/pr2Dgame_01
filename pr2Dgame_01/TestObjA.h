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
};

