#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "timer.h"
#include "gameObjectPool.h"
#include "Knife.h"
Player::Player(float px, float py):Animation("나루토",0,true,px,py)
{
}


Player::~Player()
{
}


void Player::update()
{	
	//플레이어 애니메이션 스테이트 머신
	if (state == idle)
	{
		aniIdle();
	}
	else if (state == walk)
	{
		aniWalk();
		
	}
	else if (state == run)
	{
		aniRun();
		
	}
	else if (state == jump)
	{
		aniJump();
	}
	else if (state == attack)
	{
		aniAttack();
	}
	else if (state == airAttack)
	{
		aniAirAttack();
	}
	else if (state == hit)
	{
		aniHit();
	}
	else if (state == death)
	{
		aniDeath();
	}
}



void Player::OnAnimationEvent(int aniId, int aniFrame)
{
	//printf("애니 %d, 애니 프레임 %d\n", aniId, aniFrame);
	if (aniId == attack&&aniFrame==0)
	{
		//수리검 투척(싱글톤 활용=하나의객체를 여러곳에서 사용)
		/*gameObjectPool * pool = gameObjectPool::instance();
		pool->addGameObject(new Knife(px+10, py+10));*/
		addGameObject(new Knife(px + 10, py + 10),1);
		//공격 애니메 종료
		state = idle;
		play(state);
	}
	else if(aniId==death&&aniFrame==0)
	{
		//플레이어 제거
		delGameObject(this);

		//플레이어 리스폰(테스트)
		addGameObject(new Player(px, py), 2);
	}

}


//void Player::DoDamage(GameObject * fromObj, GameObject * toObj, AABB * fromAABB, int damage)
//{
//	printf("나루토가 %d만큼 피해를 입음\n", damage);
//	//hit애니메이션으로 변경
//	state = hit;
//	play(state);
//}



void Player::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	//트랩에서 피해를 입음
	if (OtherObj->GetName() == "트랩"&&otherAABB->getId() == 1 && myAABB->getId() == 1)
	{
		//hp감소
		hp = hp - 50;
		hpBar->setValue((float)hp / 100.0f);
		//printf("플레이어 hp : %d",hp);

		//히트 애니메이션으로 이동
		hitDelay = 0.5f;

		translate(-30, 0);
		hpBar->translate(-30, 0);//체력바를 이동시킴


		state = hit;
		play(state);

	}
	//if (OtherObj->GetName() == "낫"&& otherAABB->getId() == 1 && myAABB->getId() == 1)
	//{
	//	//hp감소
	//	hp = hp - 50;

	//	//히트 애니메이션으로 이동
	//	hitDelay = 0.5f;

	//	translate(-30, 0);
	//	if (state != hit)
	//	{
	//		hpBar->translate(-30, 0);//체력바를 이동시킴
	//	}

	//	hpBar->setValue((float)hp / 100.0f);
	//	//printf("플레이어 hp : %d",hp);

	//	state = hit;
	//	play(state);
	//}
}

void Player::onTriggerStay(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
}


