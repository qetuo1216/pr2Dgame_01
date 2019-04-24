#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "timer.h"

void Player::aniIdle()
{
	//shift가 안눌리고 
	if (getKey(VK_LSHIFT) != true)
	{
		if (getKey(VK_LEFT) == true || getKey(VK_RIGHT) == true || getKey(VK_UP) == true || getKey(VK_DOWN) == true)//이동키 눌리면
		{
			state = walk;
			play(walk);
		}
	}
	else//shift가 눌리고
	{
		if (getKey(VK_LEFT) == true || getKey(VK_RIGHT) == true || getKey(VK_UP) == true || getKey(VK_DOWN) == true)//이동키 눌리면
		{
			state = run;	//run 상태로
			play(run);
		}
	}
	if (getKeyDown(VK_SPACE) == true)//스페이스 눌리면
	{
		state = jump;	//점프 상태로
		play(jump);

		//점프 속도 지정
		jumpTimer = 0;	//점프 측정시간 초기화
		jumpMoveSpeed = 0;//점프 이동 속도 초기화
		jumpStartY = py;//시작지점 초기화
	}
	if (getKeyDown('A') == true)//a키는 공격
	{
		state = attack;
		play(attack);
	}
}

void Player::aniWalk()
{
	float d = walkSpeed * getDelteTime();

	if (getKey(VK_RIGHT) == true)
	{
		hFlip = false;
		translate(d, 0);
	}
	if (getKey(VK_LEFT) == true)
	{
		hFlip = true;
		translate(-d, 0);

	}
	if (getKey(VK_UP) == true)
	{
		translate(0, -d);
	}
	if (getKey(VK_DOWN) == true)
	{
		translate(0, d);
	}

	//이동 키가 놓이면 idle로
	if (getKey(VK_RIGHT) != true && getKey(VK_LEFT) != true && getKey(VK_UP) != true && getKey(VK_DOWN) != true)
	{
		state = idle;
		play(idle);
	}
	if (getKey(VK_LSHIFT))
	{
		if (getKey(VK_RIGHT) == true || getKey(VK_LEFT) == true)
		{
			state = run;
			play(run);
		}
	}
	if (getKeyDown(VK_SPACE) == true && getKey(VK_LEFT) != true)//스페이스 눌리면
	{
		state = jump;	//점프 상태로
		play(jump);

		//점프 속도 지정
		jumpTimer = 0;
		jumpMoveSpeed = 50;
		jumpStartY = py;
	}
	if (getKeyDown('A') == true && getKey(VK_LEFT) != true)//a키는 공격
	{
		state = attack;
		play(attack);
	}
}

void Player::aniRun()
{
	float d = runSpeed * getDelteTime();

	if (getKey(VK_LSHIFT) == true)//shift가 눌리고
	{
		if (getKey(VK_RIGHT) == true)//오른쪽 눌림
		{
			hFlip = false;
			translate(d, 0);
		}
		if (getKey(VK_LEFT) == true)//왼쪽 눌림
		{
			hFlip = true;
			translate(-d, 0);
		}
		if (getKey(VK_UP) == true)//오른쪽 눌림
		{
			//hFlip = false;
			translate(0, -d);
		}
		if (getKey(VK_DOWN) == true)//왼쪽 눌림
		{
			//hFlip = true;
			translate(0, d);
		}

	}
	else//shift 놓임
	{
		state = idle;
		play(idle);
	}
	if (getKeyDown(VK_SPACE) == true && getKey(VK_LEFT) != true)//스페이스 눌리면
	{
		state = jump;	//점프 상태로
		play(jump);

		//점프 속도 지정
		jumpTimer = 0;
		jumpMoveSpeed = 100;
		jumpStartY = py;
	}
	if (getKeyDown('A') == true)//a키는 공격
	{
		state = attack;
		play(attack);
	}

}

void Player::aniJump()
{

	if (getKeyDown(VK_SPACE) != true)
	{
		//1.점프 시간 측정
		jumpTimer = jumpTimer + getDelteTime();


		//2.점프 이동시키기
		float upSpeed = jumpUpSpeed - jumpAcc * jumpTimer;//중력가속도로 계산 y축 이동

		float moveDist = jumpMoveSpeed * getDelteTime();//x축 이동 시간
		float upDist = upSpeed * getDelteTime();//위로 올라가기

		translate(moveDist, -upDist);

		//점프 후 원위치로 이동했는지 검사
		if (jumpStartY < py)
		{
			//점프 종료
			//py = jumpStartY;
			translate(moveDist, py - jumpStartY);
			//애니메이션 상태 종료
			state = idle;
			play(state);
		}

	}
	//2단 점프
	if (getKeyDown(VK_SPACE) == true)
	{
		jumpTimer = 0;//타이머를 리셋해서 가속도를 초기호
	}

	//air점프 전환
	if (getKeyDown('A') == true)
	{
		state = airAttack;
		play(state);
	}

}

void Player::aniAttack()
{

}

void Player::aniAirAttack()
{
	//1.점프 시간 측정
	jumpTimer = jumpTimer + getDelteTime();


	//2.점프 이동시키기
	float upSpeed = jumpUpSpeed - jumpAcc * jumpTimer;//중력가속도로 계산 y축 이동

	float moveDist = jumpMoveSpeed * getDelteTime();//x축 이동 시간
	float upDist = upSpeed * getDelteTime();//위로 올라가기

	translate(moveDist, -upDist);

	//점프 후 원위치로 이동했는지 검사
	if (jumpStartY < py)
	{
		//점프 종료
		py = jumpStartY;

		//애니메이션 상태 종료
		state = idle;
		play(state);
	}
}

void Player::aniHit()
{
	//지연시간 측정
	hitDelay = hitDelay - getDelteTime();

	if (hitDelay <= 0)//지연시간 경과
	{
		hpBar->translate(30, 0);
		if (hp >= 0)
		{
			state = idle;
			play(state);
		}
		else
		{
			state = death;
			play(state);
		}
	}
}

void Player::aniDeath()
{
}

void Player::aniTest()
{
	//'1'키는 IDLE
	//'2'키는 WALK
	if (getKey('1') == true)
	{
		play(idle);//0번 프레임부터 들어감
	}

	if (getKey('2') == true)
	{
		play(walk);
	}

	if (getKey('3') == true)
	{
		play(run);
	}

	if (getKey('4') == true)
	{
		play(jump);
	}

	if (getKey('5') == true)
	{
		play(attack);
	}

	if (getKey('6') == true)
	{
		play(hit);
	}
}