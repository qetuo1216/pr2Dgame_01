#include "stdafx.h"
#include "Scene.h"
#include "BackGround.h"
#include "Player.h"
#include "Barrel.h"
#include "gameObjectPool.h"//싱글톤 테스트
Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::init()
{
	gameObjectPool * pool = gameObjectPool::instance();//객체생성없이 클래스 단위로 생성
	//new gameObjectPool();//이렇게 여러개 객체 생성 예방
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
