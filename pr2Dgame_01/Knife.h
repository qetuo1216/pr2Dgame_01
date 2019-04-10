#pragma once
#include "Animation.h"
class Knife:public Animation
{
private:
	//이동 속도
	float speed;

	//수리검 사정거리
	float maxDist;	//최대 사정거리
	float moveDist;	//이동거리
public:
	Knife(float px,float py);
	~Knife();
	
	//init 오버라이딩
	void init();
	void update();

	//충돌 이벤트 오버라이딩
	void onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB);
};

