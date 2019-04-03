#include "stdafx.h"
#include "Player.h"
#include "Input.h"
#include "timer.h"
Player::Player(float px, float py):Animation("������",0,true,px,py)
{
}


Player::~Player()
{
}

void Player::init()
{
	//�ִϸ��̼� �ε��ϱ�
	Sprite sprite;
	//0�� idle
	for (int i = 0; i < 4; i++)
	{

	readBMPRect("asset/naruto.bmp", 2+i*(42+2), 12, 42, 54,&sprite);//ũ�Ⱑ 42*54, ��������� 2.12
	addAniFrame(sprite,idle);//0�� �迭�� �������
	//frames.push_back(sprite);//�ִϸ��̼��� frames�� ����
	}

	//1�� walk
	for (size_t i = 0; i < 6; i++)
	{
		readBMPRect("asset/naruto.bmp", 2 + i * (36 + 2), 80, 36, 56, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12
		addAniFrame(sprite, walk);//1�� �迭�� �������
	}

	//2�� run
	for (size_t i = 0; i < 6; i++)
	{
		readBMPRect("asset/naruto.bmp", 2 + i * (68 + 2), 150, 68, 45, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12

		//��Ŀ����Ʈ �����ϱ�
		sprite.ax = 10;//+���̹����� �������� �̵�,-�� ������
		sprite.ay = -10;//+���̹����� ������ �̵�,-�� �Ʒ���

		addAniFrame(sprite, run);//2�� �迭�� �������
	}

	//3�� jump
	for (size_t i = 0; i < 2; i++)
	{
		readBMPRect("asset/naruto.bmp", 2 + i * (50 + 2), 332, 50, 51, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12

		//��Ŀ����Ʈ �����ϱ�
		sprite.ay = 20;//+���̹����� ������ �̵�,-�� �Ʒ���
		addAniFrame(sprite, jump);//3�� �迭�� �������
	}

	//4�� attack
	for (size_t i = 0; i < 3; i++)
	{
		readBMPRect("asset/naruto.bmp", 2 + i * (58 + 2), 584, 58, 48, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12


		//��Ŀ����Ʈ �����ϱ�
		sprite.ay = -5;//+���̹����� ������ �̵�,-�� �Ʒ���

		addAniFrame(sprite, attack);//4�� �迭�� �������
	}

	//5�� hit
	readBMPRect("asset/naruto.bmp", 2, 977, 42, 40, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12
	sprite.ax = 10;//+���̹����� �������� �̵�,-�� ������
	addAniFrame(sprite, hit);//5�� �迭�� �������

	//�ִϸ� �ӵ� �����ϱ�
	setFrameDelay(0.15);

	//�ʱ� �ִϸ� �����ϱ�
	state = idle;
	play(idle);
	
	//�̵� �ӵ� ����
	walkSpeed = 50;
	runSpeed = 100;

	//���� �ð� ���� �ʱ�ȭ
	jumpDelay = 0.5;
	jumpTimer = 0;
	
	//���� �ӵ�
	jumpMoveSpeed = 100;
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
}

void Player::aniIdle()
{
	//shift�� �ȴ����� 
	if (getKey(VK_LSHIFT) != true)
	{
		if (getKey(VK_LEFT) == true || getKey(VK_RIGHT) == true)//�̵�Ű ������
		{
			state = walk;
			play(walk);
		}
	}
	else//shift�� ������
	{
		if (getKey(VK_LEFT) == true || getKey(VK_RIGHT) == true)//�̵�Ű ������
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
		jumpMoveSpeed = 0;
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
		translate(d, 0);
	}
	if (getKey(VK_LEFT) == true)
	{
		translate(-d, 0);
	}
	//�̵� Ű�� ���̸� idle��
	if (getKey(VK_RIGHT) != true && getKey(VK_LEFT) != true)
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
	if (getKeyDown(VK_SPACE) == true&& getKey(VK_LEFT) != true)//�����̽� ������
	{
		state = jump;	//���� ���·�
		play(jump);

		//���� �ӵ� ����
		jumpMoveSpeed = 50;
	}
	if (getKeyDown('A') == true)//aŰ�� ����
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
			translate(d, 0);
		}
		if (getKey(VK_LEFT) == true)//���� ����
		{
			translate(-d, 0);
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
		jumpMoveSpeed = 100;
	}		

}

void Player::aniJump()
{

	if (getKeyDown(VK_SPACE) != true)
	{
		//1.���� �ð� ����
		jumpTimer = jumpTimer + getDelteTime();

		if (jumpTimer >= jumpDelay)
		{
			state = idle;
			play(idle);

			jumpTimer = 0;//���� ���� �ð� �ʱ�ȭ
		}
		//2.���� �̵���Ű��
		float moveDist = jumpMoveSpeed * getDelteTime();

		//if(getKey(VK_RIGHT) == true)
		translate(moveDist, 0);
	}
}

void Player::aniAttack()
{
	
}

void Player::OnAnimationEvent(int aniId, int aniFrame)
{
	printf("�ִ� %d, �ִ� ������ %d\n", aniId, aniFrame);
	if (aniId == attack&&aniFrame==0)
	{
		//���� �ִϸ� ����
		state = idle;
		play(state);
	}
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
