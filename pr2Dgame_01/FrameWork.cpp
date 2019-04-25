#include "stdafx.h"
#include "FrameWork.h"

#include "graphic.h"
#include "timer.h"
#include "Input.h"//������ �޼��� Ű��&�ٿ� ���� ������ ����

#include "GameScene.h"
#include "TitleScene.h"
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
	//�ʱ�ȭ �ϱ�
	initGraphic(hWnd, 0, 0, width, hight);
	initTimer();//�ð� �ʱ�ȭ
	initInput();

	//�� �����
	//scene = new GameScene();
	scene = new TitleScene();
	scene->init();
}

void FrameWork::run()
{


	//������Ʈ�ϱ�
	clear(255, 0, 0);	updateTimer();
	updateInput();
	
	//�� ������Ʈ �ϱ�
	scene->update();

	
	scene->checkCollision();//�浹�˻�
	scene->removeDeadObjs();//���� ������Ʈ ����
	scene->draw();			//���� ������Ʈ ���
	scene->debugDraw();		//����� ���

	//�������ϱ�
	render();
}

void FrameWork::LoadScene(Scene * nextScene)
{
	//1/���� �� unload�ϱ�
	scene->exit();

	//2/���� �� ��ü �����ϱ�
	delete scene;

	//3/�� ��ü�ϱ�
	scene = nextScene;

	//4/���ο� �� �ʱ�ȭ
	scene->init();

}

void FrameWork::exit()
{
	scene->exit();
	//�����ϱ�
	exitGraphic();
}

