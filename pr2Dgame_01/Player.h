#pragma once
#include "Animation.h"
//애니메이션 상태 enum
enum State { idle = 0, walk, run, jump, attack, hit };
class Player : public Animation
{
private:
	State state;//애니메이션 상태 enum

	//속도
	float walkSpeed;

public:
	Player(float px,float py);
	~Player();

	void init();
	void update();

	//
	void aniTest();
};

