#pragma once
#include "GameObject.h"
class TestObjA : public GameObject
{
public:
	TestObjA(float px,float py);
	virtual ~TestObjA();

	void init();
};

