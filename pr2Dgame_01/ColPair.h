#pragma once
#include "GameObject.h"
class ColPair
{
private:
	//�浹�� ���� ���� ������
	GameObject *objI, *objJ;//�浹��ü ������
	AABB		*aabbI, *aabbJ;//�浹�� aabb������
public:
	ColPair(GameObject *objI, GameObject *objJ, AABB *aabbI, AABB *aabbJ);
	virtual ~ColPair();
};

