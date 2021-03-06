#include "stdafx.h"
#include "Scene.h"

#include "gameObjectPool.h"//싱글톤 테스트
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
	gameObjectPool::instance()->clear();
}

void Scene::update()
{
	gameObjectPool * pool = gameObjectPool::instance();

	pool->update();
}

void Scene::checkCollision()
{
	gameObjectPool * pool = gameObjectPool::instance();

	//게임 객체 충돌검사하기
	pool->checkCollision();
}

void Scene::removeDeadObjs()
{
	gameObjectPool * pool = gameObjectPool::instance();

	//삭제표시된 게임 오브젝트 객체 제거하기
	pool->removeDeadObjs();
}

void Scene::draw()
{
	gameObjectPool * pool = gameObjectPool::instance();

	//게임 오브젝트 드로우 하기
	pool->draw();
}

void Scene::debugDraw()
{
	gameObjectPool * pool = gameObjectPool::instance();

	//게임 객체 debugDrow하기
	pool->debugDraw();
}

void Scene::addGameObject(GameObject * o, int order)
{
/*
	gameObjectPool * pool = gameObjectPool::instance();
	pool->addGameObject(o, order);*/

	gameObjectPool::instance()->addGameObject(o, order);
}
