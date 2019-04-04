#include "stdafx.h"
#include "GameObject.h"
#include "gameObjectPool.h"
//아이디 static 변수 초기화
int GameObject::ID = 0;//객체 생성시마다 증가시킴

GameObject::GameObject(std::string name, int tag, bool state, float px, float py)
{
	this->name = name;//string을 사용하면 복사안하고 바로 넣을 수 있다.
	this->tag = tag;
	this->state = state;

	this->px = px;
	this->py = py;

	//아이디 할당하기
	id = ID++;//객체가 생성될 때 마다 증가한다.
}


GameObject::~GameObject()//new를 생성하면 delete를 하기위해 사용
{
}

void GameObject::init()
{
}

void GameObject::update()
{
}

void GameObject::draw()
{
}

int GameObject::getId()
{
	return id;
}

bool GameObject::getState()
{
	return state;
}

void GameObject::setState(bool state)
{
	this->state = state;
}

void GameObject::translate(float dx, float dy)
{
	px = px + dx;
	py = py + dy;
}

void GameObject::addGameObject(GameObject * o,int order)
{
	//1//게임 오브젝트 풀 객체 가져오기
	gameObjectPool * pool = gameObjectPool::instance();

	//2//풀에 객체 추가하기
	pool->addGameObject(o,order);
}

void GameObject::delGameObject(GameObject * o)
{
	//1//게임 오브젝트 풀 객체 가져오기
	gameObjectPool * pool = gameObjectPool::instance();

	//2//풀에 객체 삭제하기
	pool->delGameObject(o);//코드가 복잡해지면 문제가 생긴다.
}
