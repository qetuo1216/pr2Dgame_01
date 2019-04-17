#pragma once
#include "SpliteObject.h"
class BackGround : public SpliteObject//SpliteObject를 상속
{
private:
	//배경 스크롤 속도
	float speed;
	bool scroll; //true는 스크롤 진행중, false는 스크롤 끝남
public:
	//생성자&소멸자
	BackGround(float px, float py);
	~BackGround();

	//init,update 오버라이딩
	void init();
	void update();//이동속도 계산하여 이동시킴
	void onTriggerStay(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//처음 충돌
};

