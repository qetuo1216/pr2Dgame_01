#include "stdafx.h"
#include "Scythe.h"
#include "bmp.h"
#include "timer.h"
#include "gameObjectPool.h"

Scythe::Scythe(float px, float py) : Animation("��", 1, true, px, py)
{
}

Scythe::~Scythe()
{
}

void Scythe::init()
{
	//�ִϸ��̼� �ε�
	for (int i = 0; i < 4; i++)
	{
		Sprite sprite;
		readBMPRect("asset/monster/Ninja.bmp",0+i*(40+2),418,40,40,&sprite);

		addSpriteCollider(&sprite, new AABB(0, 0, 30, 30, 1), px, py);
		addAniFrame(sprite, 0);
	}

	//�̵��ӵ� �ʱ�ȭ
	speed = 200;
}

void Scythe::update()
{
	//�� �ڱ���ǥ ��������
	float x = px, y = py;

	gameObjectPool * pool = gameObjectPool::instance();

	GameObject * player = pool->find("������");

	float d = speed * getDelteTime();

	if (player != NULL)//������ ��ü ã��
	{
		translate(player->getPx(), player->getPy());

	}

	//�÷��̾� ��ǥ 
	//float d = speed * getDelteTime();
	//translate(-d, 0);
}
