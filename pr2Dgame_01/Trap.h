#pragma once
#include "Animation.h"
class Trap :public Animation
{
private:
	//애니메이션 상태
	enum State
	{idle=0,attack,death,die};

	//애니메이션 상태 변수
	State state;
public:
	Trap(float px,float py);
	~Trap();

	void init();
	void update();
	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//돌입
	void onTriggerExit(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//이탈
	void changeAniState(State s);
};

