#include "stdafx.h"
#include "FrameWork.h"

#include "graphic.h"
#include "BackGround.h"
#include "timer.h"
#include "Player.h"
#include "Input.h"//������ �޼��� Ű��&�ٿ� ���� ������ ����
#include "Knife.h"
#include "gameObjectPool.h"//�̱��� �׽�Ʈ
//#include "TestObjA.h"
//#include "TestObjB.h"
#include "Barrel.h"

//static ������ �����
FrameWork * FrameWork::frameWork = NULL;

FrameWork::FrameWork()
{

}

FrameWork::~FrameWork()
{
}

FrameWork * FrameWork::instance()
{
	if (frameWork == NULL)
	{
		frameWork = new FrameWork();//���� Ŭ���� ���� private�� ���� ����
	}

	return frameWork;
}

void FrameWork::init(HWND hWnd, int width, int hight)
{
	gameObjectPool * pool = gameObjectPool::instance();//��ü�������� Ŭ���� ������ ����
	//new gameObjectPool();//�̷��� ������ ��ü ���� ����

	//�ʱ�ȭ �ϱ�
	initGraphic(hWnd, 0, 0, width, hight);
	initTimer();//�ð� �ʱ�ȭ
	initInput();
	//���� ��ü ���� �� �ʱ�ȭ �ϱ�
	/*GameObject *obj[3] = { new BackGround(0, 0),
							new Player(100,140),
							new Knife(200,200)};*/
	pool->addGameObject(new Player(100, 140), 1);
	pool->addGameObject(new BackGround(0, 0), 0);
}

void FrameWork::run()
{
	gameObjectPool * pool = gameObjectPool::instance();

	//������Ʈ�ϱ�
	clear(255, 0, 0);
	updateTimer();
	updateInput();
	//���� ��ü ������Ʈ �ϱ�
	/*
	for (int i = 0; i < 3; i++)
	{
		obj[i]->update();
	}
	*/
	pool->update();

	//���� ��ü �浹�˻��ϱ�
	pool->checkCollision();

	//����ǥ�õ� ���� ������Ʈ ��ü �����ϱ�
	pool->removeDeadObjs();

	//���� ������Ʈ ��ο� �ϱ�
	/*
	for (int i = 0; i < 3; i++)
	{
		obj[i]->draw();
	}
	*/
	pool->draw();

	//���� ��ü debugDrow�ϱ�
	pool->debugDraw();

	//�������ϱ�
	render();
}

void FrameWork::exit()
{
	//�����ϱ�
	exitGraphic();
}
