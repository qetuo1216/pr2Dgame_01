#pragma once
#include "GameObject.h"
class TestObjA : public GameObject
{
private:
	//������Ʈ �̵� �ӵ�
	float speed;
public:
	TestObjA(float px,float py);
	virtual ~TestObjA();

	void init();
	void update();

	//�浹 �̺�Ʈ �������̵�
	void onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB);
};

