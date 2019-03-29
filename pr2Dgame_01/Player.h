#pragma once
#include "Animation.h"
//애니메이션 상태 enum
enum State { idle = 0, walk, run, jump, attack, hit };
class Player : public Animation
{
private:
public:
	Player(float px,float py);
	~Player();
	void init();
};

