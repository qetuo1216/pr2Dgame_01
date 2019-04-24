#include "stdafx.h"
#include "FrameWork.h"

#include "graphic.h"
#include "BackGround.h"
#include "timer.h"
#include "Player.h"
#include "Input.h"//윈도우 메세지 키업&다운 으로 변경이 가능
#include "Knife.h"
#include "gameObjectPool.h"//싱글톤 테스트
//#include "TestObjA.h"
//#include "TestObjB.h"
#include "Barrel.h"

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
	gameObjectPool * pool = gameObjectPool::instance();//객체생성없이 클래스 단위로 생성
	//new gameObjectPool();//이렇게 여러개 객체 생성 예방

	//초기화 하기
	initGraphic(hWnd, 0, 0, width, hight);
	initTimer();//시간 초기화
	initInput();
	//게임 객체 생성 및 초기화 하기
	/*GameObject *obj[3] = { new BackGround(0, 0),
							new Player(100,140),
							new Knife(200,200)};*/
	pool->addGameObject(new Player(100, 140), 1);
	pool->addGameObject(new BackGround(0, 0), 0);
}

void FrameWork::run()
{
	gameObjectPool * pool = gameObjectPool::instance();

	//업데이트하기
	clear(255, 0, 0);
	updateTimer();
	updateInput();
	//게임 겍체 업데이트 하기
	/*
	for (int i = 0; i < 3; i++)
	{
		obj[i]->update();
	}
	*/
	pool->update();

	//게임 객체 충돌검사하기
	pool->checkCollision();

	//삭제표시된 게임 오브젝트 객체 제거하기
	pool->removeDeadObjs();

	//게임 오브젝트 드로우 하기
	/*
	for (int i = 0; i < 3; i++)
	{
		obj[i]->draw();
	}
	*/
	pool->draw();

	//게임 객체 debugDrow하기
	pool->debugDraw();

	//렌더링하기
	render();
}

void FrameWork::exit()
{
	//종료하기
	exitGraphic();
}
