#include "stdafx.h"
#include "GameScene.h"

#include "Player.h"
#include "Barrel.h"
#include "gameObjectPool.h"//�̱��� �׽�Ʈ
#include "BackGround.h"

GameScene::GameScene() //: Scene() //�⺻�����ڶ� ������ �����ϴ�.
{
}


GameScene::~GameScene()
{
}

void GameScene::init()
{
	gameObjectPool * pool = gameObjectPool::instance();//��ü�������� Ŭ���� ������ ����
	//new gameObjectPool();//�̷��� ������ ��ü ���� ����
	pool->addGameObject(new Player(100, 140), 1);
	//pool->addGameObject(new BackGround(0, 0), 0);
	printf("\n���Ӿ� �ʱ�ȭ\n");
}
