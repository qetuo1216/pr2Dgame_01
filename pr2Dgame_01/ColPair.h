#pragma once
#include "GameObject.h"
class ColPair
{
private:
	//�浹�� ���� ���� ������
	GameObject *objI, *objJ;//�浹��ü ������
	AABB		*aabbI, *aabbJ;//�浹�� aabb������

	//�浹���� ���� ����(�浹��,���)
	bool collided;//true-�浹 ���, false - �浹 ��
public:
	ColPair(GameObject *objI, GameObject *objJ, AABB *aabbI, AABB *aabbJ);
	virtual ~ColPair();

	//���� �浹������ �˻��ϴ� �Լ�
	bool equal(GameObject *objI, GameObject *objJ, AABB *aabbI, AABB *aabbJ);

	//getter
	GameObject * getObjI();
	GameObject * getObjJ();

	//�浹�ֿ� ����� AABB��������
	AABB * getAABBI();
	AABB * getAABBJ();

	//�浹���� ��������getter setter
	bool getCollided();
	void setCollided(bool collided);
};

