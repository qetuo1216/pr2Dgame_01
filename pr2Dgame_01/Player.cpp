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
	readBMPRect("asset/naruto.bmp", 2, 12, 42, 54,&sprite);//ũ�Ⱑ 42*54, ��������� 2.12
	frames.push_back(sprite);//�ִϸ��̼��� frames�� ����
}
