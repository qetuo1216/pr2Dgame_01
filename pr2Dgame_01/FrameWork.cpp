#include "stdafx.h"
#include "FrameWork.h"

#include "graphic.h"
#include "timer.h"
#include "Input.h"//������ �޼��� Ű��&�ٿ� ���� ������ ����

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
}

void FrameWork::run()
{


	//������Ʈ�ϱ�
	clear(255, 0, 0);
	updateTimer();
	updateInput();
	
	//�������ϱ�
	render();
}

void FrameWork::exit()
{
	//�����ϱ�
	exitGraphic();
}
