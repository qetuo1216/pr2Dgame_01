#pragma once
#include "SpliteObject.h"

#define MAX_NINJA 3
class BackGround : public SpliteObject//SpliteObject를 상속
{
private:
	//배경 스크롤 속도
	float speed;
	bool scroll; //true는 스크롤 진행중, false는 스크롤 끝남

	//왼쪽 오른쪽 충돌체 포인터
	AABB * leftAABB;
	AABB * rightAABB;

	//닌자 스폰 여부 확인 함수
	bool ninjaSpawn[MAX_NINJA];//false는 안함, true는 했음
public:
	//생성자&소멸자
	BackGround(float px, float py);
	~BackGround();

	//init,update 오버라이딩
	void init();
	void update();//이동속도 계산하여 이동시킴
	void onTriggerStay(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//처음 충돌
	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//처음 충돌
};

