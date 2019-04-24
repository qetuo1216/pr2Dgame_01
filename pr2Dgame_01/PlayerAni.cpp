#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "timer.h"

void Player::aniIdle()
{
	//shift�� �ȴ����� 
	if (getKey(VK_LSHIFT) != true)
	{
		if (getKey(VK_LEFT) == true || getKey(VK_RIGHT) == true || getKey(VK_UP) == true || getKey(VK_DOWN) == true)//�̵�Ű ������
		{
			state = walk;
			play(walk);
		}
	}
	else//shift�� ������
	{
		if (getKey(VK_LEFT) == true || getKey(VK_RIGHT) == true || getKey(VK_UP) == true || getKey(VK_DOWN) == true)//�̵�Ű ������
		{
			state = run;	//run ���·�
			play(run);
		}
	}
	if (getKeyDown(VK_SPACE) == true)//�����̽� ������
	{
		state = jump;	//���� ���·�
		play(jump);

		//���� �ӵ� ����
		jumpTimer = 0;	//���� �����ð� �ʱ�ȭ
		jumpMoveSpeed = 0;//���� �̵� �ӵ� �ʱ�ȭ
		jumpStartY = py;//�������� �ʱ�ȭ
	}
	if (getKeyDown('A') == true)//aŰ�� ����
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

	//�̵� Ű�� ���̸� idle��
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
	if (getKeyDown(VK_SPACE) == true && getKey(VK_LEFT) != true)//�����̽� ������
	{
		state = jump;	//���� ���·�
		play(jump);

		//���� �ӵ� ����
		jumpTimer = 0;
		jumpMoveSpeed = 50;
		jumpStartY = py;
	}
	if (getKeyDown('A') == true && getKey(VK_LEFT) != true)//aŰ�� ����
	{
		state = attack;
		play(attack);
	}
}

void Player::aniRun()
{
	float d = runSpeed * getDelteTime();

	if (getKey(VK_LSHIFT) == true)//shift�� ������
	{
		if (getKey(VK_RIGHT) == true)//������ ����
		{
			hFlip = false;
			translate(d, 0);
		}
		if (getKey(VK_LEFT) == true)//���� ����
		{
			hFlip = true;
			translate(-d, 0);
		}
		if (getKey(VK_UP) == true)//������ ����
		{
			//hFlip = false;
			translate(0, -d);
		}
		if (getKey(VK_DOWN) == true)//���� ����
		{
			//hFlip = true;
			translate(0, d);
		}

	}
	else//shift ����
	{
		state = idle;
		play(idle);
	}
	if (getKeyDown(VK_SPACE) == true && getKey(VK_LEFT) != true)//�����̽� ������
	{
		state = jump;	//���� ���·�
		play(jump);

		//���� �ӵ� ����
		jumpTimer = 0;
		jumpMoveSpeed = 100;
		jumpStartY = py;
	}
	if (getKeyDown('A') == true)//aŰ�� ����
	{
		state = attack;
		play(attack);
	}

}

void Player::aniJump()
{

	if (getKeyDown(VK_SPACE) != true)
	{
		//1.���� �ð� ����
		jumpTimer = jumpTimer + getDelteTime();


		//2.���� �̵���Ű��
		float upSpeed = jumpUpSpeed - jumpAcc * jumpTimer;//�߷°��ӵ��� ��� y�� �̵�

		float moveDist = jumpMoveSpeed * getDelteTime();//x�� �̵� �ð�
		float upDist = upSpeed * getDelteTime();//���� �ö󰡱�

		translate(moveDist, -upDist);

		//���� �� ����ġ�� �̵��ߴ��� �˻�
		if (jumpStartY < py)
		{
			//���� ����
			//py = jumpStartY;
			translate(moveDist, py - jumpStartY);
			//�ִϸ��̼� ���� ����
			state = idle;
			play(state);
		}

	}
	//2�� ����
	if (getKeyDown(VK_SPACE) == true)
	{
		jumpTimer = 0;//Ÿ�̸Ӹ� �����ؼ� ���ӵ��� �ʱ�ȣ
	}

	//air���� ��ȯ
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
	//1.���� �ð� ����
	jumpTimer = jumpTimer + getDelteTime();


	//2.���� �̵���Ű��
	float upSpeed = jumpUpSpeed - jumpAcc * jumpTimer;//�߷°��ӵ��� ��� y�� �̵�

	float moveDist = jumpMoveSpeed * getDelteTime();//x�� �̵� �ð�
	float upDist = upSpeed * getDelteTime();//���� �ö󰡱�

	translate(moveDist, -upDist);

	//���� �� ����ġ�� �̵��ߴ��� �˻�
	if (jumpStartY < py)
	{
		//���� ����
		py = jumpStartY;

		//�ִϸ��̼� ���� ����
		state = idle;
		play(state);
	}
}

void Player::aniHit()
{
	//�����ð� ����
	hitDelay = hitDelay - getDelteTime();

	if (hitDelay <= 0)//�����ð� ���
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
	//'1'Ű�� IDLE
	//'2'Ű�� WALK
	if (getKey('1') == true)
	{
		play(idle);//0�� �����Ӻ��� ��
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