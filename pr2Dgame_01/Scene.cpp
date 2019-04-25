#include "stdafx.h"
#include "Scene.h"

#include "gameObjectPool.h"//�̱��� �׽�Ʈ
Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::init()
{
	
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
