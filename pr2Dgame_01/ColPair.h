#pragma once
#include "GameObject.h"
class ColPair
{
private:
	//충돌쌍 정보 저장 포인터
	GameObject *objI, *objJ;//충돌객체 포인터
	AABB		*aabbI, *aabbJ;//충돌한 aabb포인터
public:
	ColPair(GameObject *objI, GameObject *objJ, AABB *aabbI, AABB *aabbJ);
	virtual ~ColPair();
};

