#pragma once
#include "GameObject.h"

class TestObjB : public GameObject
{
private:
	//hp�׽�Ʈ
	int hp;
public:
	TestObjB(float px,float py);
	~TestObjB();

	void init();//�׽�Ʈ �浹 �߰��ϱ�

	//�浹 �̺�Ʈ �������̵�
	void onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB);
};

