#pragma once
#include "SpliteObject.h"

#define MAX_NINJA 3
class BackGround : public SpliteObject//SpliteObject�� ���
{
private:
	//��� ��ũ�� �ӵ�
	float speed;
	bool scroll; //true�� ��ũ�� ������, false�� ��ũ�� ����

	//���� ������ �浹ü ������
	AABB * leftAABB;
	AABB * rightAABB;

	//���� ���� ���� Ȯ�� �Լ�
	bool ninjaSpawn[MAX_NINJA];//false�� ����, true�� ����
public:
	//������&�Ҹ���
	BackGround(float px, float py);
	~BackGround();

	//init,update �������̵�
	void init();
	void update();//�̵��ӵ� ����Ͽ� �̵���Ŵ
	void onTriggerStay(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//ó�� �浹
	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//ó�� �浹
};

