#pragma once
#include "Animation.h"
#include "HUDBar.h"
class Trap :public Animation
{
private:
	//애니메이션 상태
	enum State
	{idle=0,attack,death,die};

	//애니메이션 상태 변수
	State state;
	int hp;//트랩 체력
	HUDBar * hpBar;//체력바 // 포인터로 해야 점수 조정 가능

	float dieDelay;//die애니메이션 지속 시간
public:
	Trap(float px,float py);
	~Trap();

	void init();
	void update();
	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//돌입
	void onTriggerExit(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//이탈
	void changeAniState(State s);
	//피해 이벤트 메소드 오버라이딩
	//void DoDamage(GameObject *fromObj, GameObject *toObj, AABB* fromAABB, int damage);

	//애니메이션 장면 전환 이벤트
	void OnAnimationEvent(int aniId, int aniFrame);
};

