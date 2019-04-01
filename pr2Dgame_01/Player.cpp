#include "stdafx.h"
#include "Player.h"


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

	//1�� �ȱ�
	for (size_t i = 0; i < 6; i++)
	{
		readBMPRect("asset/naruto.bmp", 2 + i * (36 + 2), 80, 36, 56, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12
		addAniFrame(sprite, walk);//1�� �迭�� �������
	}
	//�ִϸ� �ӵ� �����ϱ�
	setFrameDelay(0.15);
}
