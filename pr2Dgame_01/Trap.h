#pragma once
#include "Animation.h"
class Trap :public Animation
{
private:
	//�ִϸ��̼� ����
	enum State
	{idle=0,attack,death,die};

	//�ִϸ��̼� ���� ����
	State state;
public:
	Trap(float px,float py);
	~Trap();

	void init();
	void update();
	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);

	void changeAniState(State s);
};

