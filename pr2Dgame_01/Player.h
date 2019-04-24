#pragma once
#include "Animation.h"
#include "HUDBar.h"
//애니메이션 상태 enum
enum State { idle = 0, walk, run, jump, attack, hit,airAttack,death };
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
	
	//점프 이동속도
	float jumpMoveSpeed;//점프로 앞으로 이동하는 속도
	float jumpUpSpeed;//점프 위로 올라가는 속도
	float jumpAcc;//중력 가속도

	//점프 시작 y좌표
	float jumpStartY;

	//히트 애니메이션 시간
	float hitDelay;

	//플레이어 hp - 이후에 게임 매니저에서 관리
	int hp;
	HUDBar *hpBar;//체력바


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
	void aniAirAttack();
	void aniHit();
	void aniDeath();

	//애니메 전환이벤트 오버라이딩
	void OnAnimationEvent(int aniId, int aniFrame);

	//충돌 이벤트 오버라이딩
	void onTriggerEnter(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//처음 충돌
	void onTriggerStay(AABB* myAABB, GameObject *OtherObj, AABB* otherAABB);//반복

	//피해 이벤트 메소드 오버라이딩
	//void DoDamage(GameObject *fromObj, GameObject *toObj, AABB* fromAABB, int damage);
	//
	void aniTest();
};

