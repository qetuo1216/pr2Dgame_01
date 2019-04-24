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

	this->alive = true;	//생성자에서 객체가 살아있음으로 초기화
	this->parentObj = NULL;//부모 오브젝트가 없음

	this->px = px;
	this->py = py;

	//충돌체 기본 색상 지정
	colR = 255;
	colG = 0;
	colB = 0;

	//아이디 할당하기
	id = ID++;//객체가 생성될 때 마다 증가한다.
}


GameObject::~GameObject()//new를 생성하면 delete를 하기위해 사용
{
	//게임 오브젝트에 추가된 AABB제거하기
	for (int i = 0; i < col.size(); i++)
	{
		delete col[i];
	}
	//stl vector 한꺼번에 지우기
	col.clear();

	//자식 게임 오브젝트 삭제하기
	for (int i = 0; i < child.size(); i++)
	{
		delChildObject(child[i]);
	}
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

void GameObject::debugDraw()
{
	//게임오브젝트 충돌체 그리기
	for (int i = 0; i < col.size(); i++)
	{
		col[i]->debugDraw(colR,colG,colB);
	}
}


int GameObject::getId()
{
	return id;
}

int GameObject::getTag()
{
	return tag;
}

bool GameObject::getState()
{
	return state;
}

void GameObject::setState(bool state)
{
	this->state = state;
}

bool GameObject::getAlive()
{
	return alive;
}

void GameObject::setAlive(bool alive)
{
	this->alive = alive;
}

std::string GameObject::GetName()
{
	return name;
}

std::vector<AABB*> GameObject::getCollider()
{
	return col;
}

void GameObject::translate(float dx, float dy)
{
	px = px + dx;
	py = py + dy;

	//충돌체 이동시키기
	for (int i = 0; i < col.size(); i++)
	{
		col[i]->translate(dx, dy);
	}
	//자식 게임오브젝트 이동시키기
	for (int i = 0; i < child.size(); i++)
	{
		child[i]->translate(dx, dy);
	}
}

void GameObject::addGameObject(GameObject * o,int order)
{
	//1//게임 오브젝트 풀 객체 가져오기
	gameObjectPool * pool = gameObjectPool::instance();

	//2//풀에 객체 추가하기
	pool->addGameObject(o,order);
}

void GameObject::addChildObject(GameObject * o, int order)
{
	//자식의 목록에 추가
	child.push_back(o);

	//부모를 기억시킴
	o->parentObj = this;

	//1//게임 오브젝트 풀 객체 가져오기
	gameObjectPool * pool = gameObjectPool::instance();

	//2//풀에 객체 추가하기
	pool->addGameObject(o, order);
}


void GameObject::delGameObject(GameObject * o)
{
	//1//게임 오브젝트 풀 객체 가져오기
	gameObjectPool * pool = gameObjectPool::instance();

	//2//풀에 객체 삭제하기
	pool->delGameObject(o);//코드가 복잡해지면 문제가 생긴다.
}

void GameObject::delChildObject(GameObject * o)
{
	//1//자식목록에서 제거하기
	for (int i = 0; i < child.size(); i++)
	{
		if (child[i]->getId() == o->getId())//아이디를 검사해서
		{
			//child목록에서 제거
			child.erase(child.begin() + i);
			break;
		}
	}

	//2//게임 오브젝트 풀 객체 가져오기
	gameObjectPool * pool = gameObjectPool::instance();

	//3//풀에 객체 삭제하기
	pool->delGameObject(o);//코드가 복잡해지면 문제가 생긴다.
}

void GameObject::addCollider(AABB * aabb)
{
	//게임오브젝트 좌표 적용하기
	aabb->translate(px, py);

	//충돌체 추가하기 
	col.push_back(aabb);

}

void GameObject::setColColor(unsigned char r, unsigned char g, unsigned char b)
{
	colR = r;
	colG = g;
	colB = b;
}

void GameObject::onTriggerEnter(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
}

void GameObject::onTriggerStay(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
}

void GameObject::onTriggerExit(AABB * myAABB, GameObject * OtherObj, AABB * otherAABB)
{
}

void GameObject::DoDamage(GameObject * fromObj, GameObject * toObj, AABB * fromAABB, int damage)
{
}
