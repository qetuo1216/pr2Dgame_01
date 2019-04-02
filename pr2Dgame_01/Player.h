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
	float runSpeed;

	//점프 상태 시간 변수
	float jumpDelay;//점프 유지 시간
	float jumpTimer;//점프 시간 측정 변수

public:
	Player(float px,float py);
	~Player();

	void init();
	void update();

	//애니메 상태 함수
	void aniIdle();
	void aniWalk();
	void aniRun();
	void aniJump();
	void aniAttack();

	//애니메 전환이벤트 오버라이딩
	void OnAnimationEvent(int aniId, int aniFrame);
	//
	void aniTest();
};

