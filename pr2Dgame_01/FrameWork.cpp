#include "stdafx.h"
#include "FrameWork.h"

#include "graphic.h"
#include "timer.h"
#include "Input.h"//윈도우 메세지 키업&다운 으로 변경이 가능

//static 포인터 만들기
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
		frameWork = new FrameWork();//같은 클래스 안의 private는 접근 가능
	}

	return frameWork;
}

void FrameWork::init(HWND hWnd, int width, int hight)
{
	//초기화 하기
	initGraphic(hWnd, 0, 0, width, hight);
	initTimer();//시간 초기화
	initInput();
}

void FrameWork::run()
{


	//업데이트하기
	clear(255, 0, 0);
	updateTimer();
	updateInput();
	
	//렌더링하기
	render();
}

void FrameWork::exit()
{
	//종료하기
	exitGraphic();
}
