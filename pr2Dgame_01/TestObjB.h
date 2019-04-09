#pragma once
#include "GameObject.h"

class TestObjB : public GameObject
{
private:

public:
	TestObjB(float px,float py);
	~TestObjB();

	void init();//테스트 충돌 추가하기
};

