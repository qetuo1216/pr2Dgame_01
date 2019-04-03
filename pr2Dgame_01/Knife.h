#pragma once
#include "Animation.h"
class Knife:public Animation
{
private:
	//이동 속도
	float speed;
public:
	Knife(float px,float py);
	~Knife();
	
	//init 오버라이딩
	void init();
	void update();
};

