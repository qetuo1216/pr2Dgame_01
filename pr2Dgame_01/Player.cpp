#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "timer.h"
#include "gameObjectPool.h"
#include "Knife.h"
Player::Player(float px, float py):Animation("������",0,true,px,py)
{
}


Player::~Player()
{
}


void Player::update()
{	
	//�÷��̾� �ִϸ��̼� ������Ʈ �ӽ�
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
	//printf("�ִ� %d, �ִ� ������ %d\n", aniId, aniFrame);
	if (aniId == attack&&aniFrame==0)
	{
		//������ ��ô(�̱��� Ȱ��=�ϳ��ǰ�ü�� ���������� ���)
		/*gameObjectPool * pool = gameObjectPool::instance();
		pool->addGameObject(new Knife(px+10, py+10));*/
		addGameObject(new Knife(px + 10, py + 10),1);
		//���� �ִϸ� ����
		state = idle;
		play(state);
	}
	else if(aniId==death&&aniFrame==0)
	{
		//�÷��̾� ����
		delGameObject(this);

		//�÷��̾� ������(�׽�Ʈ)
		addGameObject(new Player(px, py), 2);
	}

}


//void Player::DoDamage(GameObject * fromObj, GameObject * toObj, AABB * fromAABB, int damage)
//{
//	printf("�����䰡 %d��ŭ ���ظ� ����\n", damage);
//	//hit�ִϸ��̼����� ����
//	state = hit;
//	play(state);
//}



void Player::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	//Ʈ������ ���ظ� ����
	if (OtherObj->GetName() == "Ʈ��"&&otherAABB->getId() == 1 && myAABB->getId() == 1)
	{
		//hp����
		hp = hp - 50;
		hpBar->setValue((float)hp / 100.0f);
		//printf("�÷��̾� hp : %d",hp);

		//��Ʈ �ִϸ��̼����� �̵�
		hitDelay = 0.5f;

		translate(-30, 0);
		hpBar->translate(-30, 0);//ü�¹ٸ� �̵���Ŵ


		state = hit;
		play(state);

	}
	//if (OtherObj->GetName() == "��"&& otherAABB->getId() == 1 && myAABB->getId() == 1)
	//{
	//	//hp����
	//	hp = hp - 50;

	//	//��Ʈ �ִϸ��̼����� �̵�
	//	hitDelay = 0.5f;

	//	translate(-30, 0);
	//	if (state != hit)
	//	{
	//		hpBar->translate(-30, 0);//ü�¹ٸ� �̵���Ŵ
	//	}

	//	hpBar->setValue((float)hp / 100.0f);
	//	//printf("�÷��̾� hp : %d",hp);

	//	state = hit;
	//	play(state);
	//}
}

void Player::onTriggerStay(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
}


