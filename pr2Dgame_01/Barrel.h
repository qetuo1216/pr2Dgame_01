#pragma once
#include "SpliteObject.h"
class Barrel : public SpliteObject
{
private:

public:
	Barrel(float px,float py);
	~Barrel();

	void init();
	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);
};

