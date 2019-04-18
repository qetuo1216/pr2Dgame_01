#pragma once
#include "Animation.h"
class Trap :public Animation
{
private:

public:
	Trap(float px,float py);
	~Trap();

	void init();
	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);
};

