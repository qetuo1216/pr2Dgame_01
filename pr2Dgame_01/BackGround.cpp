#include "stdafx.h"
#include "BackGround.h"
#include "timer.h"

BackGround::BackGround(float px, float py):SpliteObject("���",0,true,px,py)//���� 0�� �Ʊ�,1���� ��,2�� �������
{
}

BackGround::~BackGround()
{
}

void BackGround::init()
{
	//��� �̹��� �ε��ϱ�
	readBMPRect("asset/���.bmp", 0, 0, 4303, 224, &splite);

	//��ũ�� �ӵ� �ʱ�ȭ
	speed = 100;//�ʴ� 100px�� �̵�
}

void BackGround::update()
{
	//��ũ�� �̵�
	float d = speed * getDelteTime();
	px = px - d;
}
