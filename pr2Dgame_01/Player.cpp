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
	for (int i = 0; i < 4; i++)
	{

	readBMPRect("asset/naruto.bmp", 2+i*(42+2), 12, 42, 54,&sprite);//ũ�Ⱑ 42*54, ��������� 2.12
	addAniFrame(sprite);
	//frames.push_back(sprite);//�ִϸ��̼��� frames�� ����
	}
	//�ִϸ� �ӵ� �����ϱ�
	setFrameDelay(0.15);
}
