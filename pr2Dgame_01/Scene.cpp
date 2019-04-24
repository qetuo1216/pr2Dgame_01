#include "stdafx.h"
#include "Scene.h"
#include "BackGround.h"
#include "Player.h"
#include "Barrel.h"
#include "gameObjectPool.h"//�̱��� �׽�Ʈ
Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::init()
{
	gameObjectPool * pool = gameObjectPool::instance();//��ü�������� Ŭ���� ������ ����
	//new gameObjectPool();//�̷��� ������ ��ü ���� ����
	pool->addGameObject(new Player(100, 140), 1);
	pool->addGameObject(new BackGround(0, 0), 0);
}

void Scene::exit()
{
}

void Scene::update()
{
	gameObjectPool * pool = gameObjectPool::instance();

	pool->update();
}

void Scene::checkCollision()
{
	gameObjectPool * pool = gameObjectPool::instance();

	//���� ��ü �浹�˻��ϱ�
	pool->checkCollision();
}

void Scene::removeDeadObjs()
{
	gameObjectPool * pool = gameObjectPool::instance();

	//����ǥ�õ� ���� ������Ʈ ��ü �����ϱ�
	pool->removeDeadObjs();
}

void Scene::draw()
{
	gameObjectPool * pool = gameObjectPool::instance();

	//���� ������Ʈ ��ο� �ϱ�
	pool->draw();
}

void Scene::debugDraw()
{
	gameObjectPool * pool = gameObjectPool::instance();

	//���� ��ü debugDrow�ϱ�
	pool->debugDraw();
}
