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

};

