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
	//����ź�� ��ǥ�� px,py�϶� ���� ��ǥ�� player->getPx(),player->getPx()
	//�� ������ ���� ��ǥ�� translate((px - player->getPx()),py - player->getPx()))�� �ٷ� �����Ѵ�.
	//�׷��� ���̸�ŭ �������ϴµ� = ��(x-a)^2+(y-)

	gameObjectPool * pool = gameObjectPool::instance();

	//�÷��̾� ã��
	GameObject * player = pool->find("������");

	if (player != NULL)//������ ��ü�� ã�� ���
	{
		//�̵� ��ǥ ��ġ(target)
		float tx = player->getPx();
		float ty = player->getPy();

		//���� ���� ��ġ(start)
		float sx = px;
		float sy = py;

		//������ �÷��̾�� �̵��ϴ� ���� �� ���� ó��
		float vx = tx - sx;
		float vy = ty - sy;

		//translate(vx, vy);	//���̷�Ʈ�� �̵� = �ǹ̾���

		//������ ���� ���ϱ� = ���̷� ������.
		float len = sqrt(vx*vx + vy*vy);
		float nx = vx / len;
		float ny = vy / len;

		//�ӷ¿� ���� �̵��Ÿ� ����
		float dist = speed * getDelteTime();
		float dx = nx * dist;
		float dy = ny * dist;

		translate(dx, dy);
	}
	else//�÷��̾� ��ü�� ã�� ���� ���
	{
		float dist = speed * getDelteTime();
		translate(-dist, 0);
	}
	


	//�׳� �� ������
	//float d = speed * getDelteTime();
	//translate(-d, 0);
}
