#pragma once
#include "Animation.h"
#include"HUDBar.h"
class Wolf : public Animation
{
private:
	enum State
	{
		attack, run, hit, death
	};
	State state;

	int hp;//닌자 체력 
	HUDBar * hpBar;//체력바 // 포인터로 해야 점수 조정 가능 
public:
	Wolf(float px,float py);
	~Wolf();

	void init();
	void update(); 

	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//돌입
	void onTriggerExit(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//이탈

	void OnAnimationEvent(int aniId, int aniFrame);//애니메이션 장면 전환 이벤트

	void changeAniState(State s); //애니메이션 상태 전환 메소드

};

