#pragma once
#include "SpliteObject.h"
class BackGround : public SpliteObject//SpliteObject�� ���
{
private:
	//��� ��ũ�� �ӵ�
	float speed;
	bool scroll; //true�� ��ũ�� ������, false�� ��ũ�� ����
public:
	//������&�Ҹ���
	BackGround(float px, float py);
	~BackGround();

	//init,update �������̵�
	void init();
	void update();//�̵��ӵ� ����Ͽ� �̵���Ŵ
	void onTriggerStay(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//ó�� �浹
};

