#include "stdafx.h"
#include "FrameWork.h"

#include "graphic.h"
#include "timer.h"
#include "Input.h"//윈도우 메세지 키업&다운 으로 변경이 가능

#include "GameScene.h"
#include "TitleScene.h"
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

	//씬 만들기
	//scene = new GameScene();
	scene = new TitleScene();
	scene->init();
}

void FrameWork::run()
{


	//업데이트하기
	clear(255, 0, 0);	updateTimer();
	updateInput();
	
	//씬 업데이트 하기
	scene->update();

	
	scene->checkCollision();//충돌검사
	scene->removeDeadObjs();//게임 오브젝트 제거
	scene->draw();			//게임 오브젝트 출력
	scene->debugDraw();		//디버그 출력

	//렌더링하기
	render();
}

void FrameWork::LoadScene(Scene * nextScene)
{
	//1/기존 씬 unload하기
	scene->exit();

	//2/기존 씬 객체 제거하기
	delete scene;

	//3/씬 교체하기
	scene = nextScene;

	//4/새로운 씬 초기화
	scene->init();

}

void FrameWork::exit()
{
	scene->exit();
	//종료하기
	exitGraphic();
}

