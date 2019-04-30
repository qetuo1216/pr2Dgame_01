#pragma once
#include "Animation.h"
class Scythe : public Animation
{
private:
	//이동 속도
	float speed;
public:
	Scythe(float px,float py);
	~Scythe();

	void init();
	void update();

	//낫의 이동
	float maxDist;	//최대 사정거리
	float moveDist;	//이동거리 측정

};

