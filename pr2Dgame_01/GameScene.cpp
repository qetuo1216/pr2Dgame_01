#include "stdafx.h"
#include "GameScene.h"

#include "Player.h"
#include "Barrel.h"
#include "gameObjectPool.h"//싱글톤 테스트
#include "BackGround.h"

GameScene::GameScene() //: Scene() //기본생성자라서 생략이 가능하다.
{
}


GameScene::~GameScene()
{
}

void GameScene::init()
{
	gameObjectPool * pool = gameObjectPool::instance();//객체생성없이 클래스 단위로 생성
	//new gameObjectPool();//이렇게 여러개 객체 생성 예방
	pool->addGameObject(new Player(100, 140), 1);
	//pool->addGameObject(new BackGround(0, 0), 0);
	printf("\n게임씬 초기화\n");
}
