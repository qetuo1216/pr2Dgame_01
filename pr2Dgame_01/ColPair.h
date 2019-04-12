#pragma once
#include "GameObject.h"
class ColPair
{
private:
	//충돌쌍 정보 저장 포인터
	GameObject *objI, *objJ;//충돌객체 포인터
	AABB		*aabbI, *aabbJ;//충돌한 aabb포인터

	//충돌쌍의 상태 정보(충돌끝,계속)
	bool collided;//true-충돌 계속, false - 충돌 끝
public:
	ColPair(GameObject *objI, GameObject *objJ, AABB *aabbI, AABB *aabbJ);
	virtual ~ColPair();

	//같은 충돌쌍인지 검사하는 함수
	bool equal(GameObject *objI, GameObject *objJ, AABB *aabbI, AABB *aabbJ);

	//getter
	GameObject * getObjI();
	GameObject * getObjJ();

	//충돌쌍에 저장된 AABB가져오기
	AABB * getAABBI();
	AABB * getAABBJ();

	//충돌쌍의 상태정보getter setter
	bool getCollided();
	void setCollided(bool collided);
};

