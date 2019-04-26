#pragma once
#include "Animation.h"
#include "HUDBar.h"
class Ninja :public Animation
{
private:
	//애니메이션 상태
	enum State
	{
		drop = 0, idle, attack, hit, death
	};

	//애니메이션 상태 변수
	State state;
	int hp;//트랩 체력
	HUDBar * hpBar;//체력바 // 포인터로 해야 점수 조정 가능

	float dieDelay;//die애니메이션 지속 시간
public:
	Ninja(float px,float py);
	~Ninja();

	void init();
	void update();
	void aniTest();
};

