#include "stdafx.h"
#include "Knife.h"
#include "timer.h"
#include "gameObjectPool.h"
Knife::Knife(float px, float py):Animation("knife",1,true,px,py)
{
}


Knife::~Knife()
{
}

void Knife::init()
{
	//�ִϸ��̼� �ε�
	Sprite sprite;
	for (int i = 0; i < 16; i++)
	{
		readBMPRect("asset/������.bmp", i * (40 + 2), 1104, 40, 16, &sprite);//ũ�Ⱑ 42*54, ��������� 2.12
		addAniFrame(sprite, 0);//0�� �迭�� �������
	}
	//�̵��ӵ� �ʱ�ȭ
	speed = 200;
	//������ �����Ÿ�
	maxDist = 200;
	//
	moveDist = 0;
}

void Knife::update()
{
	float dist = speed*getDelteTime();
	translate(dist, 0);

	//�̵��Ÿ� ���ϱ�
	moveDist = moveDist + dist;
	if (moveDist > maxDist)
	{
		//������ ����
		gameObjectPool * pool = gameObjectPool::instance();
		pool->delGameObject(this);
	}
}
