#pragma once
#include "Animation.h"
class Scythe : public Animation
{
private:
	//이동 속도
	float speed;

	//낫의 이동
	float maxDist;	//최대 사정거리
	float moveDist;	//이동거리 측정
	
	//게임 객체 라이프 타임 적용하기
	float lifeTime;

public:
	Scythe(float px,float py);
	~Scythe();

	void init();
	void update();

	void onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB);
};

