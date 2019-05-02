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

	int hp;//닌자 체력 
	HUDBar * hpBar;//체력바 // 포인터로 해야 점수 조정 가능 

	float dieDelay;//die애니메이션 지속 시간
	
	float dropSpeed;
	float groundY;

	//닌자가 공격중인지를 판단하는 변수
	bool isAttack;

public:
	Ninja(float px,float py);
	~Ninja();

	void init();
	void update();

	void aniDrop();
	void aniTest();

	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//돌입
	void onTriggerExit(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//이탈
		
	void OnAnimationEvent(int aniId, int aniFrame);//애니메이션 장면 전환 이벤트

	void changeAniState(State s); //애니메이션 상태 전환 메소드
};

