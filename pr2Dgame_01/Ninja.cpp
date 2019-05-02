#include "stdafx.h"
#include "Ninja.h"
#include "bmp.h"
#include "Input.h"
#include "Scythe.h"
#include "HUDBar.h"
#include "timer.h"
Ninja::Ninja(float px, float py):Animation("닌자", 1, true, px, py)
{
}


Ninja::~Ninja()
{
}

void Ninja::init()
{
	//drop 이미지
	for(int i = 0; i < 2; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0+i*(56+2),159,56,57, &sprite);
		sprite.ax = 10;
		sprite.ay = 10;
		//몸통 충돌체 - 0번			
		addSpriteCollider(&sprite, new AABB(-5,-5,45,49,0), px, py);

		//플레이어 탐지 충돌체 - 1번			
		addSpriteCollider(&sprite, new AABB(-5, -5, 45, 49, 1), px, py);

		setColColor(0, 255, 0);
		addAniFrame(sprite, drop);


	}

	//idle 이미지
	for (int i = 0; i < 4; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (42+2), 0, 42, 49, &sprite);

		//몸통 충돌체 - 0번			
		addSpriteCollider(&sprite, new AABB(0,0,37,48,0), px, py);

		//플레이어 탐지 충돌체 - 1번			
		addSpriteCollider(&sprite, new AABB(0-100, -30, 37+200, 48+60, 1), px, py);

		addAniFrame(sprite, idle);
	}

	//attack 이미지
	for (int i = 0; i < 5; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (56 + 2), 51, 56, 48, &sprite);
		sprite.ax = 20;


		//몸통 충돌체			
		addSpriteCollider(&sprite, new AABB(-20,0,46,49, 0), px, py);

		//플레이어 탐지 충돌체 - 1번			
		addSpriteCollider(&sprite, new AABB(-20-110, 0-30, 46+220, 49+60, 1), px, py);

		addAniFrame(sprite, attack);
	}

	//hit 이미지
	int hitCol[2][4] = { {1, 3, 40, 48}, {0,0,36,52} };

	for (int i = 0; i < 1; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (41 + 2), 218, 41,56, &sprite);

		/*if (i == 0)
			addSpriteCollider(&sprite, new AABB(1, 3, 40, 48, 0), px, py);
		if (i == 1)
			addSpriteCollider(&sprite, new AABB(0,0,36,52, 0), px, py);*/
		addSpriteCollider(&sprite, new AABB(hitCol[i][0], hitCol[i][1], hitCol[i][2], hitCol[i][3], 0), px, py);
		addAniFrame(sprite, hit);
	}

	//death 이미지
	for (int i = 0; i < 5; i++)
	{
		Sprite sprite;

		readBMPRect("asset/monster/Ninja.bmp", 0 + i * (59 + 2), 318, 59, 56, &sprite);

		addAniFrame(sprite, death);
	}

	changeAniState(drop);//초기 애니메이션 상태 지정하기
	//play(idle);


	//hp, hp바 초기화
	hp = 100;
	hpBar = new HUDBar(px - 11, py - 10);
	addChildObject(hpBar, 2);

	dropSpeed = 200; //닌자 드랍속도
	groundY = 160;		//바닥 좌표 초기화
}

void Ninja::update()
{
	//aniTest();
	//animation이 drop상태일때
	if(state==drop) aniDrop();
}

void Ninja::aniDrop()
{
	float dist = dropSpeed * getDelteTime();
	
	
	if (py>= groundY)//바닥에 도착했는지 체크
	{
		changeAniState(idle);
	}
	else
	{
		translate(0, dist);
	}
}

void Ninja::OnAnimationEvent(int aniId, int aniFrame)
{	//닌자 낫 발사 시점
	if (aniId == attack && aniFrame == 3)
	{
		addGameObject(new Scythe(px - 10, py), 1);
	}
	if (aniId == hit && aniFrame == 0)
	{
		setFrameDelay(0.1);
		changeAniState(idle);
	}
	if (aniId == death && aniFrame == 0)
	{
		delChildObject(this);//닌자 지우기
		delGameObject(this);
	}
}

void Ninja::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{

	//플레이어 접근 감지
	if (state != death)
	{

		if (OtherObj->GetName() == "나루토" && myAABB->getId() == 1)
		{
			changeAniState(attack);
		}		

		if (OtherObj->GetName() == "knife" && myAABB->getId() == 0)
		{
			hp = hp - 50;
			hpBar->setValue((float)hp / 100.0f); //체력바 표시

			if (hp <= 0)//체력이 다 닳음
			{
				changeAniState(death);
			}
			else
			{
				setFrameDelay(0.3);
				changeAniState(hit);
			}

			
			

		

		}

		

		
	}


}

void Ninja::onTriggerExit(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
	//애니메이션이 death가 아닌 경우에만 idle로 변경
	if (state == attack)
	{
		if (OtherObj->GetName() == "나루토" && otherAABB->getId() == 1 && myAABB->getId() == 1)
		{//1번 충돌체에 플레이어가 나가면 idle로 돌아간다.

			changeAniState(idle);
		}
	}
}


void Ninja::changeAniState(State s)
{
	state = s;
	play(state);
}




void Ninja::aniTest()
{
	if (getKey('0') == true)
	{
		play(drop);//0번 프레임부터 들어감
	}	
	
	if (getKey('1') == true)
	{
		play(idle);//0번 프레임부터 들어감
	}

	if (getKey('2') == true)
	{
		play(attack);
	}

	if (getKey('3') == true)
	{
		play(hit);
	}

	if (getKey('4') == true)
	{
		play(death);
	}
}
