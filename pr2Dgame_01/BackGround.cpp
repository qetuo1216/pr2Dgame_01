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

	//�÷��̾� �̵��� ���� �浹ü �߰�.
	addCollider(new AABB(0, 140, 500, 25, 0));

	//��ũ�� �ӵ� �ʱ�ȭ
	speed = 100;//�ʴ� 100px�� �̵�
}

void BackGround::update()
{
	//��ũ�� �̵�
	float d = speed * getDelteTime();
	//translate(-d, 0);//��� ���Ƴ���
	//px = px - d;
}
