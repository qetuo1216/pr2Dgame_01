#include "stdafx.h"
#include "GameScene.h"

#include "Player.h"
#include "Barrel.h"
#include "gameObjectPool.h"//�̱��� �׽�Ʈ
#include "BackGround.h"
#include "Ninja.h"
#include "Wolf.h"
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
	pool->addGameObject(new BackGround(0, 0), 0);
	pool->addGameObject(new Wolf(200, 140), 0);
	
	//���� �ʱ�ȭ
	//pool->addGameObject(new Ninja(350, 140), 1);
	printf("\n���Ӿ� �ʱ�ȭ\n");
}
